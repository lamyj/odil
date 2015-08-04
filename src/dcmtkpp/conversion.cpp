/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/conversion.h"

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Element.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/Tag.h"
#include "dcmtkpp/VR.h"

namespace dcmtkpp
{

DcmEVR convert(VR vr)
{
    if(vr == VR::AE) { return EVR_AE; }
    else if(vr == VR::AS) { return EVR_AS; }
    else if(vr == VR::AT) { return EVR_AT; }
    else if(vr == VR::CS) { return EVR_CS; }
    else if(vr == VR::DA) { return EVR_DA; }
    else if(vr == VR::DS) { return EVR_DS; }
    else if(vr == VR::DT) { return EVR_DT; }
    else if(vr == VR::FL) { return EVR_FL; }
    else if(vr == VR::FD) { return EVR_FD; }
    else if(vr == VR::IS) { return EVR_IS; }
    else if(vr == VR::LO) { return EVR_LO; }
    else if(vr == VR::LT) { return EVR_LT; }
    else if(vr == VR::OB) { return EVR_OB; }
    else if(vr == VR::OF) { return EVR_OF; }
    else if(vr == VR::OW) { return EVR_OW; }
    else if(vr == VR::PN) { return EVR_PN; }
    else if(vr == VR::SH) { return EVR_SH; }
    else if(vr == VR::SL) { return EVR_SL; }
    else if(vr == VR::SQ) { return EVR_SQ; }
    else if(vr == VR::SS) { return EVR_SS; }
    else if(vr == VR::ST) { return EVR_ST; }
    else if(vr == VR::TM) { return EVR_TM; }
    else if(vr == VR::UI) { return EVR_UI; }
    else if(vr == VR::UL) { return EVR_UL; }
    else if(vr == VR::UN) { return EVR_UN; }
    else if(vr == VR::US) { return EVR_US; }
    else if(vr == VR::UT) { return EVR_UT; }
    else
    {
        throw Exception("Unknown VR: "+as_string(vr));
    }
}

VR convert(DcmEVR evr)
{
    if(evr == EVR_AE) { return VR::AE; }
    else if(evr == EVR_AS) { return VR::AS; }
    else if(evr == EVR_AT) { return VR::AT; }
    else if(evr == EVR_CS) { return VR::CS; }
    else if(evr == EVR_DA) { return VR::DA; }
    else if(evr == EVR_DS) { return VR::DS; }
    else if(evr == EVR_DT) { return VR::DT; }
    else if(evr == EVR_FL) { return VR::FL; }
    else if(evr == EVR_FD) { return VR::FD; }
    else if(evr == EVR_IS) { return VR::IS; }
    else if(evr == EVR_LO) { return VR::LO; }
    else if(evr == EVR_LT) { return VR::LT; }
    else if(evr == EVR_OB) { return VR::OB; }
    else if(evr == EVR_OF) { return VR::OF; }
    else if(evr == EVR_OW) { return VR::OW; }
    else if(evr == EVR_PN) { return VR::PN; }
    else if(evr == EVR_SH) { return VR::SH; }
    else if(evr == EVR_SL) { return VR::SL; }
    else if(evr == EVR_SQ) { return VR::SQ; }
    else if(evr == EVR_SS) { return VR::SS; }
    else if(evr == EVR_ST) { return VR::ST; }
    else if(evr == EVR_TM) { return VR::TM; }
    else if(evr == EVR_UI) { return VR::UI; }
    else if(evr == EVR_UL) { return VR::UL; }
    else if(evr == EVR_UN) { return VR::UN; }
    else if(evr == EVR_US) { return VR::US; }
    else if(evr == EVR_UT) { return VR::UT; }
    else
    {
        throw Exception("Unknown VR: "+std::string(DcmVR(evr).getVRName()));
    }
}

DcmTagKey convert(Tag const & tag)
{
    return DcmTagKey(tag.group, tag.element);
}

Tag convert(DcmTagKey const & tag)
{
    return Tag(tag.getGroup(), tag.getElement());
}

DcmElement * convert(const Tag & tag, Element const & source)
{
    DcmTag const destination_tag(convert(tag), convert(source.vr));

    DcmElement * destination = NULL;
    if(source.vr == VR::AE)
    {
        destination = new DcmApplicationEntity(destination_tag);
        if(!source.empty())
        {
            convert<Value::Strings>(source, destination, &Element::as_string);
        }
    }
    else if (source.vr == VR::AS)
    {
        destination = new DcmAgeString(destination_tag);
        if(!source.empty())
        {
            convert<Value::Strings>(source, destination, &Element::as_string);
        }
    }
    else if(source.vr == VR::AT)
    {
        destination = new DcmAttributeTag(destination_tag);
        if(!source.empty())
        {
            for(unsigned int i=0; i<source.as_string().size(); ++i)
            {
                Tag const source_tag(source.as_string()[i]);
                DcmTagKey const destination_tag = convert(source_tag);
                destination->putTagVal(destination_tag, i);
            }
        }
    }
    else if (source.vr == VR::CS)
    {
        destination = new DcmCodeString(destination_tag);
        if(!source.empty())
        {
            convert<Value::Strings>(source, destination, &Element::as_string);
        }
    }
    else if (source.vr == VR::DA)
    {
        destination = new DcmDate(destination_tag);
        if(!source.empty())
        {
            convert<Value::Strings>(source, destination, &Element::as_string);
        }
    }
    else if (source.vr == VR::DS)
    {
        destination = new DcmDecimalString(destination_tag);
        if(!source.empty())
        {
            convert<Value::Reals>(source, destination, &Element::as_real);
        }
    }
    else if (source.vr == VR::DT)
    {
        destination = new DcmDateTime(destination_tag);
        if(!source.empty())
        {
            convert<Value::Strings>(source, destination, &Element::as_string);
        }
    }
    else if (source.vr == VR::FD)
    {
        destination = new DcmFloatingPointDouble(destination_tag);
        if(!source.empty())
        {
            convert<Value::Reals, Float64>(source, destination, &Element::as_real);
        }
    }
    else if (source.vr == VR::FL)
    {
        destination = new DcmFloatingPointSingle(destination_tag);
        if(!source.empty())
        {
            convert<Value::Reals, Float32>(source, destination, &Element::as_real);
        }
    }
    else if (source.vr == VR::IS)
    {
        destination = new DcmIntegerString(destination_tag);
        if(!source.empty())
        {
            convert<Value::Integers>(source, destination, &Element::as_int);
        }
    }
    else if (source.vr == VR::LO)
    {
        destination = new DcmLongString(destination_tag);
        if(!source.empty())
        {
            convert<Value::Strings>(source, destination, &Element::as_string);
        }
    }
    else if (source.vr == VR::LT)
    {
        destination = new DcmLongText(destination_tag);
        if(!source.empty())
        {
            convert<Value::Strings>(source, destination, &Element::as_string);
        }
    }
    else if (source.vr == VR::OB || source.vr == VR::OW)
    {
        destination = new DcmOtherByteOtherWord(destination_tag);
        if(!source.empty())
        {
            convert(source, static_cast<DcmOtherByteOtherWord*>(destination));
        }
    }
    // OF
    else if (source.vr == VR::PN)
    {
        destination = new DcmPersonName(destination_tag);
        if(!source.empty())
        {
            convert<Value::Strings>(source, destination, &Element::as_string);
        }
    }
    else if (source.vr == VR::SH)
    {
        destination = new DcmShortString(destination_tag);
        if(!source.empty())
        {
            convert<Value::Strings>(source, destination, &Element::as_string);
        }
    }
    else if (source.vr == VR::SL)
    {
        destination = new DcmSignedLong(destination_tag);
        if(!source.empty())
        {
            convert<Value::Integers, Sint32>(source, destination, &Element::as_int);
        }
    }
    else if(source.vr == VR::SQ)
    {
        DcmSequenceOfItems * sequence = new DcmSequenceOfItems(destination_tag);
        if(!source.empty())
        {
            for(auto const & source_item: source.as_data_set())
            {
                DcmItem * destination_item = convert(source_item);
                sequence->append(destination_item);
            }
        }
        destination = sequence;
    }
    else if (source.vr == VR::SS)
    {
        destination = new DcmSignedShort(destination_tag);
        if(!source.empty())
        {
            convert<Value::Integers, Sint16>(source, destination, &Element::as_int);
        }
    }
    else if (source.vr == VR::ST)
    {
        destination = new DcmShortText(destination_tag);
        if(!source.empty())
        {
            convert<Value::Strings>(source, destination, &Element::as_string);
        }
    }
    else if (source.vr == VR::TM)
    {
        destination = new DcmTime(destination_tag);
        if(!source.empty())
        {
            convert<Value::Strings>(source, destination, &Element::as_string);
        }
    }
    else if (source.vr == VR::UI)
    {
        destination = new DcmUniqueIdentifier(destination_tag);
        if(!source.empty())
        {
            convert<Value::Strings>(source, destination, &Element::as_string);
        }
    }
    else if (source.vr == VR::UL)
    {
        destination = new DcmUnsignedLong(destination_tag);
        if(!source.empty())
        {
            convert<Value::Integers, Uint32>(source, destination, &Element::as_int);
        }
    }
    // UN
    else if (source.vr == VR::US)
    {
        destination = new DcmUnsignedShort(destination_tag);
        if(!source.empty())
        {
            convert<Value::Integers, Uint16>(source, destination, &Element::as_int);
        }
    }
    else if (source.vr == VR::UT)
    {
        destination = new DcmUnlimitedText(destination_tag);
        if(!source.empty())
        {
            convert<Value::Strings>(source, destination, &Element::as_string);
        }
    }
    else
    {
        throw Exception("Unknown VR: "+as_string(source.vr));
    }

    return destination;
}

template<>
void convert<std::vector<uint8_t>, Value::Binary>(
    DcmElement * source, Element & destination,
    Value::Binary & (Element::*getter)())
{
    auto & destination_values = (destination.*getter)();
    destination_values =
        dcmtkpp::ElementAccessor<std::vector<uint8_t>>::element_get(*source, 0);
}

Element convert(DcmElement * source)
{
    Element destination;

    DcmEVR const source_vr = source->getTag().getVR().getValidEVR();
    VR const destination_vr = convert(source_vr);

    if(source_vr == EVR_AE || source_vr == EVR_AS || source_vr == EVR_CS ||
       source_vr == EVR_DA || source_vr == EVR_DT || source_vr == EVR_LO ||
       source_vr == EVR_LT || source_vr == EVR_PN || source_vr == EVR_SH ||
       source_vr == EVR_ST || source_vr == EVR_TM || source_vr == EVR_UI ||
       source_vr == EVR_UT)
    {
        destination = Element(Value::Strings(), destination_vr);
        convert<std::string, Value::Strings>(source, destination, &Element::as_string);
    }
    else if(source_vr == EVR_AT)
    {
        destination = Element(Value::Strings(), destination_vr);
        destination.as_string().reserve(source->getVM());
        for(unsigned int i=0; i<source->getVM(); ++i)
        {
            DcmTagKey source_tag;
            OFCondition const condition = source->getTagVal(source_tag, i);
            if(condition.bad())
            {
                throw Exception(condition);
            }
            Tag const destination_tag = convert(source_tag);
            destination.as_string().push_back(std::string(destination_tag));
        }
    }
    else if(source_vr == EVR_DS || source_vr == EVR_FD)
    {
        destination = Element(Value::Reals(), destination_vr);
        convert<Float64, Value::Reals>(source, destination, &Element::as_real);
    }
    else if(source_vr == EVR_FL)
    {
        destination = Element(Value::Reals(), destination_vr);
        convert<Float32, Value::Reals>(source, destination, &Element::as_real);
    }
    else if(source_vr == EVR_IS || source_vr == EVR_SL)
    {
        destination = Element(Value::Integers(), destination_vr);
        convert<Sint32, Value::Integers>(source, destination, &Element::as_int);
    }
    else if(source_vr == EVR_SQ)
    {
        destination = Element(Value::DataSets(), destination_vr);
        DcmSequenceOfItems * sequence = dynamic_cast<DcmSequenceOfItems*>(source);
        if(sequence == NULL)
        {
            throw Exception("Element is not a DcmSequenceOfItems");
        }

        Value::DataSets & destination_value = destination.as_data_set();

        destination_value.reserve(sequence->card());
        for(unsigned int i=0; i<sequence->card(); ++i)
        {
            DcmItem * source_item = sequence->getItem(i);
            DataSet const destination_item = convert(source_item);
            destination_value.push_back(destination_item);
        }
    }
    else if(source_vr == EVR_SS)
    {
        destination = Element(Value::Integers(), destination_vr);
        convert<Sint16, Value::Integers>(source, destination, &Element::as_int);
    }
    else if(source_vr == EVR_UL)
    {
        destination = Element(Value::Integers(), destination_vr);
        convert<Uint32, Value::Integers>(source, destination, &Element::as_int);
    }
    else if(source_vr == EVR_OB || source_vr == EVR_OF || source_vr == EVR_OW ||
            source_vr == EVR_UN)
    {
        destination = Element(Value::Binary(), destination_vr);
        convert<std::vector<uint8_t>, Value::Binary>(source, destination, &Element::as_binary);
    }
    else if(source_vr == EVR_US)
    {
        destination = Element(Value::Integers(), destination_vr);
        convert<Uint16, Value::Integers>(source, destination, &Element::as_int);
    }
    else
    {
        throw Exception("Unknown VR: "+std::string(DcmVR(source_vr).getVRName()));
    }

    return destination;
}

void convert(Element const & source, DcmOtherByteOtherWord * destination)
{
    auto const & value = source.as_binary();

    Uint8 * output;
    OFCondition condition;
    if(destination->getTag().getVR().getValidEVR() == EVR_OB)
    {
        condition = destination->createUint8Array(source.size(), output);
    }
    else
    {
        Uint16* temp;
        condition = destination->createUint16Array(source.size()/2, temp);
        output = reinterpret_cast<Uint8*>(temp);
    }

    if(condition.bad())
    {
        throw Exception(condition);
    }

    std::copy(value.begin(), value.end(), output);
}

void convert(Element const & source, DcmOtherFloat * destination)
{
    auto const & value = source.as_binary();
}

DcmItem * convert(DataSet const & source)
{
    DcmDataset * destination = new DcmDataset();

    for(auto const & iterator: source)
    {
        auto const destination_element = convert(
            iterator.first, iterator.second);
        destination->insert(destination_element);
    }

    return destination;
}

DataSet convert(DcmItem * source)
{
    DataSet destination;

    for(unsigned long i=0; i<source->card(); ++i)
    {
        auto const source_element = source->getElement(i);

        auto const destination_tag = convert(source_element->getTag());
        auto const destination_element = convert(source_element);

        destination.add(destination_tag, destination_element);
    }
    return destination;
}

}
