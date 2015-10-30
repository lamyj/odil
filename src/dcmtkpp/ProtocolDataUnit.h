/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _d83d6c51_1173_4426_9034_c3b57b323ae1
#define _d83d6c51_1173_4426_9034_c3b57b323ae1

#include <cstdint>
#include <memory>
#include <vector>

namespace dcmtkpp
{

/// @brief Abstract class for all Protocol Data Units.
class ProtocolDataUnit
{
public:
    /// @brief Binary data container
    typedef std::vector<uint8_t> Data;

    /// @brief PDU Type, PS 3.8, 9.3.1 sq.
    enum Type
    {
        A_ASSOCIATE_RQ = 0x01,
        A_ASSOCIATE_AC = 0x02,
        A_ASSOCIATE_RJ = 0x03,

        P_DATA_TF = 0x04,

        A_RELEASE_RQ = 0x05,
        A_RELEASE_RP = 0x06,

        A_ABORT = 0x07,
    };

    /// @brief Factory building concrete PDU objects based on binary data.
    static std::shared_ptr<ProtocolDataUnit> factory(Data const & data);

    /// @brief Constructor.
    ProtocolDataUnit(Type pdu_type);

    /// @brief Destructor.
    virtual ~ProtocolDataUnit();

    /// @brief Return the binary representation of the PDU.
    virtual Data as_binary() const =0;

    /// @brief Return the type of the PDU.
    Type get_pdu_type() const;

protected:
    Type _pdu_type;
};

}

#endif // _d83d6c51_1173_4426_9034_c3b57b323ae1
