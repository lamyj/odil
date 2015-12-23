/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _a52696bc_5c6e_402d_a343_6cb085eb0138
#define _a52696bc_5c6e_402d_a343_6cb085eb0138

#include <functional>
#include <map>
#include <string>
#include <vector>

#include "dcmtkpp/dul/StateMachine.h"
#include "dcmtkpp/message/Message.h"

namespace dcmtkpp
{

/// @brief User identity types as defined by PS3.8 2013 D.3.3.7
enum class UserIdentityType
{
    None = 0,
    Username = 1,
    UsernameAndPassword = 2,
    Kerberos = 3,
    SAML = 4
};

/**
 * @brief Association.
 */
class Association
{
public:
    /// @brief Association result (ITU-T X.227, PS 3.8, 7.1.1.7 and PS 3.8, 9.3.4).
    enum Result
    {
        Accepted=0,
        RejectedPermanent=1,
        RejectedTransient=2,
    };

    /// @brief Source of association result (PS 3.8, 7.1.1.8 and PS 3.8, 9.3.4).
    enum ResultSource
    {
        ULServiceUser=1,
        ULServiceProviderACSERelatedFunction=2,
        ULServiceProvderPresentationRelatedFunction=3,
    };

    // PS 3.8, 7.1.1.9, and PS 3.8, 9.3.4, and ITU-T X.227 (UL service-user,
    // UL service-provider ACSE-related function), ITU-T X.226 (UL
    // service-provider presentation-related function)
    /// @brief Diagnostic of association result
    enum Diagnostic
    {
        // UL service-user
        NoReasonGiven=1,
        ApplicationContextNameNotSupported=2,
        CallingAETitleNotRecognized=3,
        CallingAPInvocationIdentifierNotRecognized=4,
        CallingAEQualifierNotRecognized=5,
        CallingAEInvocationIdentifierNotRecognized=6,
        CalledAETitleNotRecognized=7,
        CalledAPInvocationIdentifierNotRecognized=8,
        CalledAEQualifierNotRecognized=9,
        CalledAEInvocationIdentifierNotRecognized=10,

        // UL service-provider, ACSE-related function
        NoCommonULVersion=2,

        // UL service-provider, presentation-related function
        TemporaryCongestion=1,
        LocalLimitExceeded=2,
        CalledPresentationAddressUnknown=3,
        PresentationProtocolVersionNotSupported=4,
        NoPresentationServiceAccessPointAvailable=7,
    };

    struct PresentationContext
    {
        std::string abstract_syntax;
        std::vector<std::string> transfer_syntaxes;
    };

    typedef dul::StateMachine::AssociationAcceptor AssociationAcceptor;

    /// @brief Create a default, un-associated, association.
    Association();

    /// @brief Create an un-associated association.
    Association(Association const & other);

    /// @brief Destroy the association, release it if necessary.
    ~Association();

    /// @brief Assing an un-associated association; it remains un-associated.
    Association & operator=(Association const & other);

    /// @brief Return the AE title of the caller. Defaults to "".
    std::string const & get_own_ae_title() const;
    /// @brief Set the AE title of the caller.
    void set_own_ae_title(std::string const & ae_title);

    /// @name Peer
    /// @{

    /// @brief Return the host name of the peer. Defaults to "".
    std::string const & get_peer_host() const;
    /// @brief Set the host name of the peer.
    void set_peer_host(std::string const & host);

    /// @brief Return the port of the peer. Defaults to 104.
    uint16_t get_peer_port() const;
    /// @brief Set the port of the peer.
    void set_peer_port(uint16_t port);

    /// @brief Return the AE title of the peer. Defaults to "".
    std::string const & get_peer_ae_title() const;
    /// @brief Set the AE title of the peer.
    void set_peer_ae_title(std::string const & ae_title);

    /// @}

    // Hide PDU items from user when possible?
    bool has_maximum_length() const;
    int get_maximum_length() const;
    void set_maximum_length(int value);
    void remove_maximum_length();

    /// @name Presentation contexts
    /// @{

    std::vector<PresentationContext> const & get_presentation_contexts() const;
    void set_presentation_contexts(std::vector<PresentationContext> const & value);

    /// @}

    /// @name User identity
    /// @{

    /// @brief Return the user identity type. Defaults to None.
    UserIdentityType get_user_identity_type() const;
    /// @brief Set the user identity type.
    void set_user_identity_type(UserIdentityType type);

    /// @brief Return the user identity primary field. Defaults to "".
    std::string const & get_user_identity_primary_field() const;
    /// @brief Set the user identity primary field.
    void set_user_identity_primary_field(std::string const & value);

    /// @brief Return the user identity secondary field. Defaults to "".
    std::string const & get_user_identity_secondary_field() const;
    /// @brief Set the user identity secondary field.
    void set_user_identity_secondary_field(std::string const & value);

    /// @brief Do no authenticate user.
    void set_user_identity_to_none();

    /// @brief Authenticate user using only a username.
    void set_user_identity_to_username(std::string const & username);

    /// @brief Authenticate user using a username and a password.
    void set_user_identity_to_username_and_password(
        std::string const & username, std::string const & password);

    /// @brief Authenticate user using a Kerberos ticket.
    void set_user_identity_to_kerberos(std::string const & ticket);

    /// @brief Authenticate user using a SAML assertion.
    void set_user_identity_to_saml(std::string const & assertion);

    /// @}

    /// @name Association
    /// @{

    /// @brief Test whether the object is currently associated to its peer.
    bool is_associated() const;

    /// @brief Request an association with the peer.
    void associate();

    /// @brief Receive an association from a peer.
    void receive_association();

    void receive_association(AssociationAcceptor accpetor);

    /// @brief Reject the received association request.
    void reject(Result result, ResultSource result_source, Diagnostic diagnostic);

    /// @brief Gracefully release the association. Throws an exception if not associated.
    void release();
    /// @brief Forcefully release the association. Throws an exception if not associated.
    void abort(int source, int reason);

    /// @}

    /// @brief Receive a generic DIMSE message.
    message::Message receive_message();

    /// @brief Send a DIMSE message.
    void send_message(
        message::Message const & message, std::string const & abstract_syntax);

private:
    dul::StateMachine _state_machine;

    std::string _peer_host;
    uint16_t _peer_port;

    std::string _own_ae_title;
    std::string _peer_ae_title;

    std::vector<PresentationContext> _presentation_contexts;

    UserIdentityType _user_identity_type;
    std::string _user_identity_primary_field;
    std::string _user_identity_secondary_field;

    std::map<std::string, std::pair<uint8_t, std::string>>
        _transfer_syntaxes_by_abstract_syntax;
    std::map<uint8_t, std::string> _transfer_syntaxes_by_id;
};

}

#endif // _a52696bc_5c6e_402d_a343_6cb085eb0138
