/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/PDataTFPDU.h"

#include <cstdint>
#include <numeric>
#include <vector>

#include "dcmtkpp/endian.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/ProtocolDataUnit.h"

namespace dcmtkpp
{

bool
PDataTFPDU::PresentationDataValue
::operator==(PresentationDataValue const & other) const
{
    return (
        this->is_command == other.is_command &&
        this->is_last_fragment == other.is_last_fragment &&
        this->fragment == other.fragment);
}

bool
PDataTFPDU::PresentationDataValue
::operator!=(PresentationDataValue const & other) const
{
    return !(*this == other);
}

bool
PDataTFPDU::PresentationDataValueItem
::operator==(PresentationDataValueItem const & other) const
{
    return (
        this->presentation_context_id == other.presentation_context_id &&
        this->pdv == other.pdv);
}

bool
PDataTFPDU::PresentationDataValueItem
::operator!=(PresentationDataValueItem const & other) const
{
    return !(*this == other);
}

PDataTFPDU
::PDataTFPDU(std::vector<PresentationDataValueItem> const & pdv_items)
: ProtocolDataUnit(P_DATA_TF)
{
    this->set_pdv_items(pdv_items);
}

PDataTFPDU
::PDataTFPDU(Data const & data)
: ProtocolDataUnit(P_DATA_TF)
{
    if(data.size() < 6)
    {
        throw Exception("Invalid data");
    }

    if(data[0] != this->get_pdu_type())
    {
        throw Exception("Not an P-DATA-TF PDU");
    }

    uint32_t const items_length = be32toh(
        *reinterpret_cast<uint32_t const *>(&data[2]));

    uint32_t read=0;
    while(read != items_length)
    {
        if(data.size() < 6+read+4)
        {
            throw Exception("Invalid data");
        }
        uint32_t const item_length = be32toh(
            *reinterpret_cast<uint32_t const *>(&data[6+read]));
        read += 4;
        if(data.size() < 6+read+item_length)
        {
            throw Exception("Invalid data");
        }

        uint8_t const presentation_context_id = data[6+read];
        read += 1;

        uint8_t const message_control_header = data[6+read];
        read += 1;
        bool const is_command = (message_control_header%2==1);
        bool const is_last_fragment = ((message_control_header>>1)%2==1);

        int const fragment_size = item_length-2;
        Data const fragment(
            data.begin()+6+read, data.begin()+6+read+fragment_size);
        read += fragment_size;

        this->_pdv_items.push_back({
            presentation_context_id,
            { is_command, is_last_fragment, fragment}
        });
    }
}

PDataTFPDU
::~PDataTFPDU()
{
    // Nothing to do.
}

std::vector<PDataTFPDU::PresentationDataValueItem> const &
PDataTFPDU
::get_pdv_items() const
{
    return this->_pdv_items;
}

void
PDataTFPDU
::set_pdv_items(std::vector<PresentationDataValueItem> const &pdv_items)
{
    for(auto const & item: pdv_items)
    {
        if(item.presentation_context_id%2 == 0)
        {
            // PS 3.8, 9.3.5.1
            throw Exception("Presentation context ID must be odd");
        }
    }

    this->_pdv_items = pdv_items;
}

ProtocolDataUnit::Data
PDataTFPDU
::as_binary() const
{
    auto const fragments_length = std::accumulate(
        this->_pdv_items.begin(), this->_pdv_items.end(), 0,
        [](int partial, PresentationDataValueItem const & item) {
            return partial+item.pdv.fragment.size(); });

    // For each item: size, presentation context id, message control header,
    // and fragment.
    auto const pdu_length = this->_pdv_items.size()*(4+1+1)+fragments_length;
    Data data(6+pdu_length);

    data[0] = this->get_pdu_type();
    data[1] = 0;
    *reinterpret_cast<uint32_t*>(&data[2]) = htobe32(pdu_length);

    uint32_t written=0;
    for(auto const & item: this->_pdv_items)
    {
        auto const item_length = 2+item.pdv.fragment.size();
        *reinterpret_cast<uint32_t*>(&data[6+written]) = htobe32(item_length);
        written += 4;

        data[6+written] = item.presentation_context_id;
        written += 1;

        uint8_t message_control_header = 0;
        if(item.pdv.is_command)
        {
            message_control_header += 1;
        }
        if(item.pdv.is_last_fragment)
        {
            message_control_header += 2;
        }
        data[6+written] = message_control_header;
        written += 1;

        std::copy(
            item.pdv.fragment.begin(), item.pdv.fragment.end(),
            data.begin()+6+written);
        written += item.pdv.fragment.size();
    }

    return data;
}

}
