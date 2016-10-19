/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _061fafd4_982e_4a7e_9eb0_29e06443ebf3
#define _061fafd4_982e_4a7e_9eb0_29e06443ebf3

#include <cstdint>
#include <string>
#include <vector>

#include "odil/pdu/AAssociateAC.h"
#include "odil/pdu/AAssociateRQ.h"
#include "odil/pdu/SOPClassCommonExtendedNegotiation.h"
#include "odil/pdu/SOPClassExtendedNegotiation.h"

namespace odil
{

/// @brief Encapsulate association parameters
class AssociationParameters
{
public:
    /**
     * @brief Presentation Context, cf. PS 3.8, 9.3.2.2, PS 3.8, 9.3.3.2,
     * PS 3.7, D.3.3.4.1 and PS 3.7 D.3.3.4.2.
     */
    struct PresentationContext
    {
        /// @brief Result of the presentation context negotiation.
        enum class Result
        {
            Acceptance = 0,
            UserRejection = 1,
            NoReason = 2,
            AbstractSyntaxNotSupported = 3,
            TransferSyntaxesNotSupported = 4,
        };

        PresentationContext(
            uint8_t id,
            std::string const & abstract_syntax,
            std::vector<std::string> const & transfer_syntaxes,
            bool scu_role_support, bool scp_role_support,
            Result result=Result::NoReason);

        /// @brief Identifier of the presentation context, must be odd.
        uint8_t id;
        
        /// @brief Proposed abstract syntax.
        std::string abstract_syntax;
        
        /// @brief Proposed transfer syntaxes or accepted transfer syntax.
        std::vector<std::string> transfer_syntaxes;
        
        /// @brief Support for SCU role.
        bool scu_role_support;
        
        /// @brief Support for SCP role.
        bool scp_role_support;
        
        /// @brief Result of the negotiation.
        Result result;

        /// @brief Member-wise equality.
        bool operator==(PresentationContext const & other) const;
    };

    /// @brief User Identity, cf. PS3.8 D.3.3.7
    struct UserIdentity
    {
        /// @brief User identity type.
        enum class Type
        {
            None = 0,
            Username = 1,
            UsernameAndPassword = 2,
            Kerberos = 3,
            SAML = 4
        };

        UserIdentity();

        UserIdentity(
            Type type, std::string const & primary_field,
            std::string const & secondary_field);

        /// @brief Identity type.
        Type type;
        
        /// @brief Primary identity field.
        std::string primary_field;
        
        /// @brief Secondary identity field.
        std::string secondary_field;

        /// @brief Member-wise equality.
        bool operator==(UserIdentity const & other) const;
    };

    /// @brief Constructor.
    AssociationParameters();

    /// @brief Constructor from an A-ASSOCIATE-RQ PDU.
    AssociationParameters(pdu::AAssociateRQ const & pdu);

    /// @brief Constructor from an A-ASSOCIATE-RQ PDU.
    AssociationParameters(
        pdu::AAssociateAC const & pdu, AssociationParameters const & request);

    /// @brief Return the called AE title, default to empty.
    std::string const & get_called_ae_title() const;

    /**
     * @brief Set the called AE title.
     *
     * An exception is raised if the value is empty or if it is longer than
     * 16 characters.
     */
    AssociationParameters & set_called_ae_title(std::string const & value);

    /// @brief Return the calling AE title, default to empty.
    std::string const & get_calling_ae_title() const;

    /**
     * @brief Set the calling AE title.
     *
     * An exception is raised if the value is empty or if it is longer than
     * 16 characters.
     */
    AssociationParameters & set_calling_ae_title(std::string const & value);

    /// @brief Return the presentation contexts, default to empty.
    std::vector<PresentationContext> const & get_presentation_contexts() const;

    /// @brief Set the presentation contexts. All ids must be odd and unique.
    AssociationParameters &
    set_presentation_contexts(std::vector<PresentationContext> const & value);

    /// @brief Return the user identity, default to None.
    UserIdentity const & get_user_identity() const;

    /// @brief Do no authenticate user.
    AssociationParameters & set_user_identity_to_none();

    /// @brief Authenticate user using only a username.
    AssociationParameters &
    set_user_identity_to_username(std::string const & username);

    /// @brief Authenticate user using a username and a password.
    AssociationParameters &
    set_user_identity_to_username_and_password(
        std::string const & username, std::string const & password);

    /// @brief Authenticate user using a Kerberos ticket.
    AssociationParameters &
    set_user_identity_to_kerberos(std::string const & ticket);

    /// @brief Authenticate user using a SAML assertion.
    AssociationParameters &
    set_user_identity_to_saml(std::string const & assertion);

    /// @brief Return the maximum length of a PDU, default to 16384.
    uint32_t get_maximum_length() const;

    /**
     * @brief Set the maximum length of a PDU, the value 0 meaning
     * no maximum length.
     */
    AssociationParameters & set_maximum_length(uint32_t value);
    
    /// @brief Return the maximum number of outstanding operations invoked
    uint16_t get_maximum_number_operations_invoked() const;

    /**
     * @brief Set the maximum number of outstanding operations invoked,
     * default to 1.
     */
    AssociationParameters & set_maximum_number_operations_invoked(uint16_t value);

    /// @brief Return the maximum number of outstanding operations performed
    uint16_t get_maximum_number_operations_performed() const;

    /**
     * @brief Set the maximum number of outstanding operations performed,
     * default to 1.
     */
    AssociationParameters & set_maximum_number_operations_performed(uint16_t value);
    
    /// @brief Return the list of SOP Class Extended Negotiation items.
    std::vector<pdu::SOPClassExtendedNegotiation>
    get_sop_class_extended_negotiation() const;

    /**
     * @brief Set the list of SOP Class Extended Negotiation items, default
     * to an empty list.
     */
    void set_sop_class_extended_negotiation(
        std::vector<pdu::SOPClassExtendedNegotiation> const & value);

    /// @brief Return the list of SOP Class Extended Negotiation items.
    std::vector<pdu::SOPClassCommonExtendedNegotiation>
        get_sop_class_common_extended_negotiation() const;
    
    /**
     * @brief Set the list of SOP Class Common Extend Negotiation items, default
     * to an empty list.
     */
    void set_sop_class_common_extended_negotiation(
        std::vector<pdu::SOPClassCommonExtendedNegotiation> const & value);

    /// @brief Create an A-ASSOCIATE-RQ PDU.
    pdu::AAssociateRQ as_a_associate_rq() const;

    /// @brief Create an A-ASSOCIATE-AC PDU.
    pdu::AAssociateAC as_a_associate_ac() const;

    /// @brief Member-wise equality.
    bool operator==(AssociationParameters const & other) const;

private:
    std::string _called_ae_title;
    std::string _calling_ae_title;
    std::vector<PresentationContext> _presentation_contexts;
    UserIdentity _user_identity;
    uint32_t _maximum_length = 16384;
    uint16_t _maximum_number_operations_invoked = 1;
    uint16_t _maximum_number_operations_performed = 1;
    std::vector<pdu::SOPClassExtendedNegotiation>
        _sop_class_extended_negotiation;
    std::vector<pdu::SOPClassCommonExtendedNegotiation> 
        _sop_class_common_extended_negotiation;

    /// @brief Set the user identity.
    AssociationParameters & _set_user_identity(UserIdentity const & value);
};

}

#endif // _061fafd4_982e_4a7e_9eb0_29e06443ebf3
