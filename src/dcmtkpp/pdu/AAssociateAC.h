/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _00e9792a_98a8_4ca7_9272_43dcd7e331ea
#define _00e9792a_98a8_4ca7_9272_43dcd7e331ea

#include <cstdint>
#include <istream>
#include <string>
#include <vector>

#include "dcmtkpp/pdu/ApplicationContext.h"
#include "dcmtkpp/pdu/Object.h"
#include "dcmtkpp/pdu/PresentationContext.h"
#include "dcmtkpp/pdu/UserInformation.h"

namespace dcmtkpp
{

namespace pdu
{

/// @brief A-ASSOCIATE-AC PDU, cf. PS 3.8, 9.3.3.
class AAssociateAC: public Object
{
public:
    /// @brief Constructor.
    AAssociateAC();

    /// @brief Constructor for binary data.
    AAssociateAC(std::istream & stream);

    /// @brief Return the protocol version.
    uint16_t get_protocol_version() const;

    /// @brief Set the protocol version.
    void set_protocol_version(uint16_t value);

    /// @brief Return the called AE title.
    std::string get_called_ae_title() const;

    /**
     * @brief Set the called AE title.
     *
     * An exception is raised if the value is empty or if it is longer than
     * 16 characters.
     */
    void set_called_ae_title(std::string const & value);

    /// @brief Return the calling AE title.
    std::string get_calling_ae_title() const;

    /**
     * @brief Set the calling AE title.
     *
     * An exception is raised if the value is empty or if it is longer than
     * 16 characters.
     */
    void set_calling_ae_title(std::string const & value);

    /// @brief Return the Application Context sub-item.
    ApplicationContext get_application_context() const;

    /// @brief Set the Application Context sub-item.
    void set_application_context(ApplicationContext const & value);

    /// @brief Return the Presentation Context sub-items.
    std::vector<PresentationContext> get_presentation_contexts() const;

    /// @brief Set the Presentation Context sub-items.
    void set_presentation_contexts(std::vector<PresentationContext> const & value);

    /// @brief Return the User Information sub-item.
    UserInformation get_user_information() const;

    /// @brief Set the User Information sub-item.
    void set_user_information(UserInformation const & value);

private:
    /// @brief Pad the value with spaces so that it is 16 characters long.
    static std::string _encode_ae_title(std::string const & value);

    /// @brief Remove the leading and trailing spaces.
    static std::string _decode_ae_title(std::string const & value);
};

}

}

#endif // _00e9792a_98a8_4ca7_9272_43dcd7e331ea
