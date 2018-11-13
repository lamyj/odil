/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _a52696bc_5c6e_402d_a343_6cb085eb0138
#define _a52696bc_5c6e_402d_a343_6cb085eb0138

#include <cstdint>
#include <functional>
#include <map>
#include <string>
#include <vector>

#include "odil/AssociationAcceptor.h"
#include "odil/AssociationParameters.h"
#include "odil/dul/Connection.h"
#include "odil/dul/StateMachine.h"
#include "odil/message/Message.h"
#include "odil/odil.h"

namespace odil
{

/**
 * @brief Association.
 */
class ODIL_API Association
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

    /// @brief Duration of the timeout.
    typedef dul::StateMachine::duration_type duration_type;

    using ErrorHandler = 
        std::function<void(dul::PDU::Pointer, boost::system::error_code)>;

    /// @brief Create a default, un-associated, association.
    Association();

    /// @brief Create an un-associated association.
    Association(Association const & other);

    /// @brief Destroy the association, release it if necessary.
    ~Association();

    /// @brief Return the TCP transport.
    dul::Transport & get_transport();

    /// @brief Assing an un-associated association; it remains un-associated.
    Association & operator=(Association const & other);

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

    /// @}

    /// @brief Return the association parameters.
    AssociationParameters const & get_parameters() const;

    /// @brief Return the association parameters.
    AssociationParameters & update_parameters();

    /// @brief Set the association parameters, throw an exception when associated.
    void set_parameters(AssociationParameters const & value);

    /// @brief Return the negotiated association parameters.
    AssociationParameters const & get_negotiated_parameters() const;

    /// @name Timeouts
    /// @{

    /// @brief Return the TCP timeout, default to infinity.
    duration_type get_tcp_timeout() const;

    /// @brief Set the timeout.
    void set_tcp_timeout(duration_type const & duration);

    /// @brief Return the DIMSE timeout, default to 30s.
    duration_type get_message_timeout() const;

    /// @brief Set the DIMSE timeout.
    void set_message_timeout(duration_type const & duration);

    /// @}

    /// @name Association
    /// @{

    /// @brief Test whether the object is currently associated to its peer.
    bool is_associated() const;

    /** 
     * @brief Synchronously request an association with the peer. Throws an 
     * exception if the endpoint can not be reached.
     */
    void associate();

    /**
     * @brief Asynchronously request an association with the peer.
     * 
     * The success_handler will be called upon association success. The 
     * error_handler will be called if:
     * - The request is rejected
     * - The negotiation is aborted
     * - An error occurs on the transport
     */ 
    void associate(
        std::function<void(Association &)> success_handler, 
        ErrorHandler error_handler);

    /// @brief Synchronously receive an association from a peer.
    void receive_association(
        boost::asio::ip::tcp const & protocol, unsigned short port,
        AssociationAcceptor acceptor=default_association_acceptor);
    
    /**
     * @brief Asynchronously receive an association from a peer.
     * 
     * The success_handler will be called if no error occurs, whether the 
     * association is accepted or rejected. The error_handler will be called if:
     * - The negotiation is aborted
     * - An error occurs on the transport
     */
    void receive_association(
        boost::asio::ip::tcp const & protocol, unsigned short port,
        std::function<void(Association &)> success_handler, 
        ErrorHandler error_handler,
        AssociationAcceptor acceptor=default_association_acceptor);

    /// @brief Reject the received association request.
    void reject(Result result, ResultSource result_source, Diagnostic diagnostic);

    /// @brief Gracefully release the association. Throws an exception if not associated.
    void release();

    void release(
        std::function<void(Association &)> success_handler, 
        ErrorHandler error_handler);

    /// @brief Forcefully release the association. Throws an exception if not associated.
    void abort(int source, int reason);

    void abort(int source, int reason, std::function<void()> close_handler);

    /// @}

    /// @name DIMSE messages sending and reception.
    /// @{

    /**
     * @brief Receive a generic DIMSE message.
     *
     * Throw an AssociationReleased or AssociationAborted if the peer released
     * or aborted the association.
     */
    std::shared_ptr<message::Message> receive_message();

    /// @brief Send a DIMSE message.
    void send_message(
        std::shared_ptr<message::Message const> message,
        std::string const & abstract_syntax);

    /// @brief Return the next available message id.
    uint16_t next_message_id();

    /// @}

private:
    dul::StateMachine _state_machine;

    std::string _peer_host;
    uint16_t _peer_port;

    AssociationParameters _association_parameters;
    AssociationParameters _negotiated_parameters;

    std::map<std::string, std::pair<uint8_t, std::string>>
        _transfer_syntaxes_by_abstract_syntax;
    std::map<uint8_t, std::string> _transfer_syntaxes_by_id;

    uint16_t _next_message_id;

    /**
     * @name Pools of signal connections during the asynchronous functions.
     * 
     * We need to keep these objects alive during the lifetime of their slots,
     * since they are disconnected from the slots themselves.
     */
    /// {@
    std::vector<boost::signals2::connection> _associate_connections;
    std::vector<boost::signals2::connection> _receive_association_connections;
    std::vector<boost::signals2::connection> _release_connections;
    std::vector<boost::signals2::connection> _abort_connections;

    /// @}
};

/** 
 * @brief Exception reported when receiving a message after the association was
 * released.
 */
class ODIL_API AssociationReleased: public Exception
{
public:
    AssociationReleased();
    virtual ~AssociationReleased() noexcept;
};

/** 
 * @brief Exception reported when receiving a message after the association was
 * aborted.
 */
class ODIL_API AssociationAborted: public Exception
{
public:
    /// @brief Source of the error.
    uint8_t source;
    
    /// @brief Reason of the error.
    uint8_t reason;
    
    AssociationAborted(unsigned char source, unsigned char reason);
    virtual ~AssociationAborted() noexcept;
};

}

#endif // _a52696bc_5c6e_402d_a343_6cb085eb0138
