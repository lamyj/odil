/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "DcmtkAssociation.h"

#include <algorithm>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmnet/assoc.h>
#include <dcmtk/dcmnet/cond.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/Reader.h"
#include "dcmtkpp/registry.h"
#include "dcmtkpp/Writer.h"

namespace dcmtkpp
{

DcmtkAssociation
::DcmtkAssociation()
: _own_ae_title(""),
  _peer_host_name(""), _peer_port(104), _peer_ae_title(""),
  _presentation_contexts({}), _user_identity_type(UserIdentityType::None),
  _user_identity_primary_field(""), _user_identity_secondary_field(""),
  _association(NULL), _network_timeout(30)
{
    // Nothing else
}

DcmtkAssociation
::DcmtkAssociation(DcmtkAssociation const & other)
: _own_ae_title(other.get_own_ae_title()),
  _peer_host_name(other.get_peer_host_name()), _peer_port(other.get_peer_port()),
  _peer_ae_title(other.get_peer_ae_title()),
  _presentation_contexts(other._presentation_contexts),
  _user_identity_type(other.get_user_identity_type()),
  _user_identity_primary_field(other.get_user_identity_primary_field()),
  _user_identity_secondary_field(other.get_user_identity_secondary_field()),
  _association(NULL), _network_timeout(other._network_timeout)
{
}

DcmtkAssociation
::~DcmtkAssociation()
{
    if(this->is_associated())
    {
        this->release();
    }
}

DcmtkAssociation &
DcmtkAssociation
::operator=(DcmtkAssociation const & other)
{
    if(this != &other)
    {
        this->set_own_ae_title(other.get_own_ae_title());
        this->set_peer_host_name(other.get_peer_host_name());
        this->set_peer_port(other.get_peer_port());
        this->set_peer_ae_title(other.get_peer_ae_title());
        this->set_presentation_contexts(other.get_presentation_contexts());
        this->set_user_identity_type(other.get_user_identity_type());
        this->set_user_identity_primary_field(other.get_user_identity_primary_field());
        this->set_user_identity_secondary_field(other.get_user_identity_secondary_field());
        this->set_network_timeout(other.get_network_timeout());
    }

    return *this;
}

std::string const &
DcmtkAssociation
::get_own_ae_title() const
{
    return this->_own_ae_title;
}

void
DcmtkAssociation
::set_own_ae_title(std::string const & ae_title)
{
    if(this->is_associated())
    {
        throw Exception("Cannot set member while associated");
    }

    this->_own_ae_title = ae_title;
}

std::string const &
DcmtkAssociation
::get_peer_host_name() const
{
    return this->_peer_host_name;
}

void
DcmtkAssociation
::set_peer_host_name(std::string const & host_name)
{
    if(this->is_associated())
    {
        throw Exception("Cannot set member while associated");
    }

    this->_peer_host_name = host_name;
}

uint16_t
DcmtkAssociation
::get_peer_port() const
{
    return this->_peer_port;
}

void
DcmtkAssociation
::set_peer_port(uint16_t port)
{
    if(this->is_associated())
    {
        throw Exception("Cannot set member while associated");
    }

    this->_peer_port = port;
}

std::string const &
DcmtkAssociation
::get_peer_ae_title() const
{
    return this->_peer_ae_title;
}

void
DcmtkAssociation
::set_peer_ae_title(std::string const & ae_title)
{
    if(this->is_associated())
    {
        throw Exception("Cannot set member while associated");
    }

    this->_peer_ae_title = ae_title;
}

void
DcmtkAssociation
::set_presentation_contexts(std::vector<DcmtkAssociation::PresentationContext>
                            const & presentation_contexts)
{
    if(this->is_associated())
    {
        throw Exception("Cannot set member while associated");
    }

    this->_presentation_contexts = presentation_contexts;
}

std::vector<DcmtkAssociation::PresentationContext>
DcmtkAssociation
::get_presentation_contexts() const
{
    return this->_presentation_contexts;
}

UserIdentityType
DcmtkAssociation
::get_user_identity_type() const
{
    return this->_user_identity_type;
}

void
DcmtkAssociation
::set_user_identity_type(UserIdentityType type)
{
    if(this->is_associated())
    {
        throw Exception("Cannot set member while associated");
    }

    this->_user_identity_type = type;
}

std::string const &
DcmtkAssociation
::get_user_identity_primary_field() const
{
    return this->_user_identity_primary_field;
}

void
DcmtkAssociation
::set_user_identity_primary_field(std::string const & value)
{
    if(this->is_associated())
    {
        throw Exception("Cannot set member while associated");
    }

    this->_user_identity_primary_field = value;
}

std::string const &
DcmtkAssociation
::get_user_identity_secondary_field() const
{
    return this->_user_identity_secondary_field;
}

void
DcmtkAssociation
::set_user_identity_secondary_field(std::string const & value)
{
    if(this->is_associated())
    {
        throw Exception("Cannot set member while associated");
    }

    this->_user_identity_secondary_field = value;
}

void
DcmtkAssociation
::set_user_identity_to_none()
{
    this->set_user_identity_type(UserIdentityType::None);
    this->set_user_identity_primary_field("");
    this->set_user_identity_secondary_field("");
}

void
DcmtkAssociation
::set_user_identity_to_username(std::string const & username)
{
    this->set_user_identity_type(UserIdentityType::Username);
    this->set_user_identity_primary_field(username);
    this->set_user_identity_secondary_field("");
}

void
DcmtkAssociation
::set_user_identity_to_username_and_password(
    std::string const & username, std::string const & password)
{
    this->set_user_identity_type(UserIdentityType::UsernameAndPassword);
    this->set_user_identity_primary_field(username);
    this->set_user_identity_secondary_field(password);
}

void
DcmtkAssociation
::set_user_identity_to_kerberos(std::string const & ticket)
{
    this->set_user_identity_type(UserIdentityType::Kerberos);
    this->set_user_identity_primary_field(ticket);
    this->set_user_identity_secondary_field("");
}

void
DcmtkAssociation
::set_user_identity_to_saml(std::string const & assertion)
{
    this->set_user_identity_type(UserIdentityType::SAML);
    this->set_user_identity_primary_field(assertion);
    this->set_user_identity_secondary_field("");
}

void
DcmtkAssociation
::set_network_timeout(int timeout)
{
    this->_network_timeout = timeout;
}

int
DcmtkAssociation
::get_network_timeout() const
{
    return this->_network_timeout;
}

bool
DcmtkAssociation
::is_associated() const
{
    return (this->_association != NULL);
}

void
DcmtkAssociation
::associate(Network & network)
{
    if(!network.is_initialized())
    {
        throw Exception("Network is not initialized");
    }

    if(this->is_associated())
    {
        throw Exception("Already associated");
    }

    OFCondition condition;

    T_ASC_Parameters * params;
    condition = ASC_createAssociationParameters(&params, ASC_MAXIMUMPDUSIZE);
    if(condition.bad())
    {
        throw Exception(condition);
    }

    condition = ASC_setAPTitles(params,
        this->_own_ae_title.c_str(), this->_peer_ae_title.c_str(), NULL);
    if(condition.bad())
    {
        ASC_destroyAssociationParameters(&params);
        throw Exception(condition);
    }

    std::string localhost(128, '\0');
    gethostname(&localhost[0], localhost.size()-1);

    std::ostringstream peer;
    peer << this->_peer_host_name << ":" << this->_peer_port;

    condition = ASC_setPresentationAddresses(params,
        "localhost", peer.str().c_str());
    if(condition.bad())
    {
        ASC_destroyAssociationParameters(&params);
        throw Exception(condition);
    }

    unsigned int context_id = 1;
    for(auto const & context: this->_presentation_contexts)
    {
        char const ** transfer_syntaxes = new char const *[context.transfer_syntaxes.size()];
        for(std::size_t i = 0; i < context.transfer_syntaxes.size(); ++i)
        {
            transfer_syntaxes[i] = context.transfer_syntaxes[i].c_str();
        }

        condition = ASC_addPresentationContext(params,
            context_id, context.abstract_syntax.c_str(),
            transfer_syntaxes, context.transfer_syntaxes.size(), context.role);
        if(condition.bad())
        {
            ASC_destroyAssociationParameters(&params);
            throw Exception(condition);
        }

        context_id += 2;
    }

    if(this->_user_identity_type == UserIdentityType::None)
    {
        // Nothing to do.
    }
    else if(this->_user_identity_type == UserIdentityType::Username)
    {
        condition = ASC_setIdentRQUserOnly(params,
            this->_user_identity_primary_field.c_str());
    }
    else if(this->_user_identity_type == UserIdentityType::UsernameAndPassword)
    {
        condition = ASC_setIdentRQUserOnly(params,
            this->_user_identity_primary_field.c_str(),
            this->_user_identity_secondary_field.c_str());
    }
    else if(this->_user_identity_type == UserIdentityType::Kerberos)
    {
        condition = ASC_setIdentRQKerberos(params,
            this->_user_identity_primary_field.c_str(),
            this->_user_identity_primary_field.size());
    }
    else if(this->_user_identity_type == UserIdentityType::SAML)
    {
        condition = ASC_setIdentRQSaml(params,
            this->_user_identity_primary_field.c_str(),
            this->_user_identity_primary_field.size());
    }
    else
    {
        ASC_destroyAssociationParameters(&params);
        throw Exception("Unknown identity type");
    }

    if(condition.bad())
    {
        ASC_destroyAssociationParameters(&params);
        throw Exception(condition);
    }

    condition = ASC_requestAssociation(
        network.get_network(), params, &this->_association);
    if(condition.bad())
    {
        OFString empty;

        if(condition == DUL_ASSOCIATIONREJECTED)
        {
            T_ASC_RejectParameters rej;
            ASC_getRejectParameters(params, &rej);

            ASC_destroyAssociationParameters(&params);
            throw Exception(ASC_printRejectParameters(empty, &rej).c_str());
        }
        else
        {
            ASC_destroyAssociationParameters(&params);
            throw Exception(DimseCondition::dump(empty, condition).c_str());
        }
    }

    this->set_network_timeout(network.get_timeout());
}

void
DcmtkAssociation
::receive(Network & network, bool accept_all)
{
    this->receive(
        network, [](DcmtkAssociation const &) { return true; }, {"*"}, accept_all);
}

void
DcmtkAssociation
::receive(Network &network,
          std::function<bool (const DcmtkAssociation &)> authenticator,
          std::vector<std::string> const & aetitles,
          bool accept_all)
{
    if(!network.is_initialized())
    {
        throw Exception("Network is not initialized");
    }

    if(this->is_associated())
    {
        throw Exception("Already associated");
    }

    OFCondition condition;

    condition = ASC_receiveAssociation(
        network.get_network(), &this->_association, ASC_DEFAULTMAXPDU);
    if(condition.bad())
    {
        throw Exception(condition);
    }

    T_ASC_Parameters * const params = this->_association->params;
    DUL_ASSOCIATESERVICEPARAMETERS const dul = params->DULparams;
    // No peer port should be defined when receiving
    this->_peer_host_name = dul.callingPresentationAddress;
    this->_peer_port = 0;
    this->_peer_ae_title = dul.callingAPTitle;
    this->_own_ae_title = dul.calledAPTitle;

    // check Peer ae title
    // '*' => everybody allowed
    if (std::find(aetitles.begin(), aetitles.end(), "*") == aetitles.end() &&
        std::find(aetitles.begin(), aetitles.end(),
                  this->_peer_ae_title.c_str()) == aetitles.end())
    {
        this->reject(RejectedPermanent, ULServiceUser,
                     CallingAETitleNotRecognized);
        this->drop();
        throw Exception("Bad AE Title");
    }

    // Check Application Context Name
    char buf[BUFSIZ];
    condition = ASC_getApplicationContextName(params, buf);
    if (condition.bad() || std::string(buf) != DICOM_STDAPPLICATIONCONTEXT)
    {
        // reject: application context name not supported
        this->reject(RejectedPermanent, ULServiceUser,
                     ApplicationContextNameNotSupported);
        this->drop();
        throw Exception("Bad Application context name");
    }

    if(accept_all)
    {
        unsigned int const pc_count = ASC_countPresentationContexts(params);
        for(unsigned int pc_index=0; pc_index<pc_count; ++pc_index)
        {
            T_ASC_PresentationContext pc;
            memset(&pc, 0, sizeof(pc));
            ASC_getPresentationContext(params, pc_index, &pc);

            for(unsigned int ts_index=0; ts_index<pc.transferSyntaxCount; ++ts_index)
            {
                std::string const abstract_syntax = pc.abstractSyntax;
                char const * abstract_syntax_data = abstract_syntax.c_str();

                condition = ASC_acceptContextsWithTransferSyntax(
                    this->_association->params,
                    pc.proposedTransferSyntaxes[ts_index],
                    1, &abstract_syntax_data);
                if(condition.bad())
                {
                    this->reject(RejectedPermanent, ULServiceUser, NoReasonGiven);
                    this->drop();
                    throw Exception(condition);
                }
            }
        }
    }
    else
    {
        for(auto const & context: this->_presentation_contexts)
        {
            for(std::size_t i = 0; i < context.transfer_syntaxes.size(); ++i)
            {
                char const * abstract_syntax = context.abstract_syntax.c_str();
                char const * transfer_syntax = context.transfer_syntaxes[i].c_str();
                condition = ASC_acceptContextsWithTransferSyntax(
                    this->_association->params, transfer_syntax,
                    1, &abstract_syntax);
                if(condition.bad())
                {
                    this->reject(RejectedPermanent, ULServiceUser, NoReasonGiven);
                    this->drop();
                    throw Exception(condition);
                }
            }
        }
    }

    // Get user identity information
    UserIdentityNegotiationSubItemRQ* identity =
            this->_association->params->DULparams.reqUserIdentNeg;

    this->_user_identity_primary_field = "";
    this->_user_identity_secondary_field = "";
    if (identity == NULL ||
        identity->getIdentityType() == ASC_USER_IDENTITY_NONE)
    {
        this->_user_identity_type = UserIdentityType::None;
    }
    else if (identity->getIdentityType() != ASC_USER_IDENTITY_UNKNOWN)
    {
        this->_user_identity_type =
                    (UserIdentityType)identity->getIdentityType();

        // Get primary field
        char * primary_field;
        Uint16 primary_field_length;
        identity->getPrimField(primary_field, primary_field_length);
        // user is not NULL-terminated
        this->_user_identity_primary_field = std::string(primary_field,
                                                         primary_field_length);

        if (identity->getIdentityType() == ASC_USER_IDENTITY_USER_PASSWORD)
        {
            // Get secondary field
            char * secondary_field;
            Uint16 secondary_field_length;
            identity->getSecField(secondary_field, secondary_field_length);
            // password is not NULL-terminated
            this->_user_identity_primary_field =
                    std::string(secondary_field, secondary_field_length);
        }
    }
    else
    {
        throw Exception("Unknown user identity type");
    }

    // Authentication
    if(authenticator(*this))
    {
        condition = ASC_acknowledgeAssociation(this->_association);
        if(condition.bad())
        {
            throw Exception(condition);
        }
    }
    else
    {
        this->reject(RejectedPermanent, ULServiceUser, NoReasonGiven);
        this->drop();
        throw Exception("Bad Authentication");
    }

    this->set_network_timeout(network.get_timeout());
}

void
DcmtkAssociation
::reject(Result result, ResultSource result_source, Diagnostic diagnostic)
{
    T_ASC_RejectParameters reject_parameters;
    reject_parameters.result = T_ASC_RejectParametersResult(result);
    reject_parameters.source = T_ASC_RejectParametersSource(result_source);
    reject_parameters.reason = T_ASC_RejectParametersReason(diagnostic);

    OFCondition const condition = ASC_rejectAssociation(
        this->_association, &reject_parameters);
    if(condition.bad())
    {
        throw Exception(condition);
    }
}

T_ASC_Association *
DcmtkAssociation
::get_association()
{
    return this->_association;
}

void
DcmtkAssociation
::release()
{
    if(!this->is_associated())
    {
        throw Exception("Not associated");
    }

    ASC_releaseAssociation(this->_association);
    ASC_destroyAssociation(&this->_association);
    this->_association = NULL;
}

void
DcmtkAssociation
::abort()
{
    if(!this->is_associated())
    {
        throw Exception("Not associated");
    }

    ASC_abortAssociation(this->_association);
    ASC_destroyAssociation(&this->_association);
    this->_association = NULL;
}

void
DcmtkAssociation
::drop()
{
    if(!this->is_associated())
    {
        throw Exception("Not associated");
    }

    ASC_acknowledgeRelease(this->_association);
    ASC_dropSCPAssociation(this->_association);
    ASC_destroyAssociation(&this->_association);
    this->_association = NULL;
}

message::Message
DcmtkAssociation
::receive(DcmtkAssociation::ProgressCallback callback,
           void *callback_data)
{
    // Receive command set
    auto const command = this->_receive_dataset(callback, callback_data);
    if(command.second != DUL_COMMANDPDV)
    {
        throw Exception("Did not receive command set");
    }
    DataSet const & command_set = command.first;

    // Receive potential data set
    DataSet data_set;
    bool has_data_set;
    if(command_set.as_int(registry::CommandDataSetType, 0) != DIMSE_DATASET_NULL)
    {
        auto const data = this->_receive_dataset(callback, callback_data);
        if(data.second != DUL_DATASETPDV)
        {
            throw Exception("Did not receive data set");
        }
        data_set = data.first;
        has_data_set = true;
    }
    else
    {
        has_data_set = false;
    }

    return (
        has_data_set?
        message::Message(command_set, data_set):message::Message(command_set));
}

std::pair<DataSet, DUL_DATAPDV>
DcmtkAssociation
::_receive_dataset(DcmtkAssociation::ProgressCallback callback,
                   void *callbackContext)
{
    DataSet data_set;

    std::stringstream stream;
    std::string transfer_syntax;
    bool keep_group_length;

    /* start a loop in which we want to read a DIMSE command from the incoming socket stream. */
    /* Since the command could stretch over more than one PDU, the use of a loop is mandatory. */
    DUL_DATAPDV type;
    bool last = false;
    DIC_UL pdvCount = 0;
    T_ASC_PresentationContextID pid = 0;
    while(!last)
    {
        DUL_PDV const pdv = this->_read_next_pdv();

        /* if this is the first loop iteration, get the presentation context ID
         * which is captured in the current PDV. If this is not the first loop
         * iteration, check if the presentation context IDs in the current PDV
         * and in the last PDV are identical. If they are not, return an error.
         */
        if (pdvCount == 0)
        {
            pid = pdv.presentationContextID;
        }
        else if (pdv.presentationContextID != pid)
        {
            std::ostringstream message;
            message << "Different presentation IDs inside Command Set: "
                    << pid << " != " << pdv.presentationContextID;
            throw Exception(message.str());
        }

        /* check if the fragment length of the current PDV is odd. This should */
        /* never happen (see DICOM standard (year 2000) part 7, annex F) (or */
        /* the corresponding section in a later version of the standard.) */
        if ((pdv.fragmentLength % 2) != 0)
        {
            /* This should NEVER happen.  See Part 7, Annex F. */
            std::ostringstream message;
            message << "Odd fragment length: " << pdv.fragmentLength;
            throw Exception(message.str());
        }

        /* if information is contained the PDVs fragment, we want to insert
         * this information into the buffer
         */
        stream.write(reinterpret_cast<char *>(pdv.data), pdv.fragmentLength);

        if(pdv.pdvType == DUL_COMMANDPDV)
        {
            /* DIMSE commands are always specified in the little endian implicit
             * transfer syntax. Additionally, we want to remove group length
             * tags.
             */
            transfer_syntax = registry::ImplicitVRLittleEndian;
            keep_group_length = false;
        }
        else if(pdv.pdvType == DUL_DATASETPDV)
        {
            /* figure out if is this a valid presentation context */
            T_ASC_PresentationContext pc;
            OFCondition const cond =
                ASC_findAcceptedPresentationContext(
                    this->_association->params, pid, &pc);
            if (cond.bad())
            {
                throw Exception("No valid presentation context");
            }

            /* determine the transfer syntax which is specified in the presentation context */
            transfer_syntax = pc.acceptedTransferSyntax;
            keep_group_length = true;
        }
        else
        {
            throw Exception("Unknown PDV type");
        }

        /* update the following variables which will be evaluated at the beginning of each loop iteration. */
        last = pdv.lastPDV;
        type = pdv.pdvType;

        /* update the counter that counts how many PDVs were received on the incoming */
        /* socket stream. This variable will be used for determining the first */
        /* loop iteration and dumping general information. */
        pdvCount++;
    }

    Reader reader(stream, transfer_syntax, keep_group_length);
    data_set = reader.read_data_set();

    return std::make_pair(data_set, type);
}

void
DcmtkAssociation
::send(message::Message const & message, std::string const & abstract_syntax,
       DcmtkAssociation::ProgressCallback callback, void *callback_data)
{
    T_ASC_PresentationContextID const presentation_context =
        this->_find_presentation_context(abstract_syntax);

    this->_send(
        message.get_command_set(),
        presentation_context, registry::ImplicitVRLittleEndian,
        DUL_COMMANDPDV, NULL, NULL);
    if(message.has_data_set() && !message.get_data_set().empty())
    {
        // FIXME: transfer syntax
        this->_send(
            message.get_data_set(),
            presentation_context, registry::ImplicitVRLittleEndian,
            DUL_DATASETPDV, callback, callback_data);
    }
}

T_ASC_PresentationContextID
DcmtkAssociation
::_find_presentation_context(const std::string &abstract_syntax) const
{
    T_ASC_PresentationContextID const presentation_id =
        ASC_findAcceptedPresentationContextID(
            this->_association,
            abstract_syntax.c_str());
    if(presentation_id == 0)
    {
        throw Exception("No Presentation Context for Get Operation");
    }

    return presentation_id;
}

void
DcmtkAssociation
::_send(DataSet const & obj, T_ASC_PresentationContextID presID,
        std::string const & transfer_syntax, DUL_DATAPDV pdvType,
        DcmtkAssociation::ProgressCallback callback, void *callbackContext)
    /*
     * This function sends all information which is included in a DcmDataset object over
     * the network which is provided in assoc.
     *
     * Parameters:
     *   obj             - [in] Contains the information which shall be sent over the network.
     *   presId          - [in] The ID of the presentation context which shall be used
     *   xferSyntax      - [in] The transfer syntax which shall be used.
     *   pdvType         - [in] Specifies if the information in this DcmDataset object belongs to
     *                          a DIMSE command (as for example C-STORE) (DUL_COMMANDPDV) or if
     *                          the information is actual instance information (DUL_DATASETPDV).
     *   callback        - [in] Pointer to a function which shall be called to indicate progress.
     *   callbackContext - []
     */
{
    bool const use_group_length = (pdvType == DUL_COMMANDPDV);
    std::stringstream stream;
    Writer writer(
        stream, transfer_syntax, Writer::ItemEncoding::ExplicitLength,
        use_group_length);
    writer.write_data_set(obj);
    std::string const data = stream.str();

    /* we may wish to restrict output PDU size */
    /* max PDV size is max PDU size minus 12 bytes PDU/PDV header */
    unsigned long bufLen = this->_association->sendPDVLength;
    if (bufLen + 12 > dcmMaxOutgoingPDUSize.get())
    {
        bufLen = dcmMaxOutgoingPDUSize.get() - 12;
    }

    bool done = false;
    unsigned long bytesTransmitted=0;
    while(!done)
    {
        std::string const buffer = data.substr(bytesTransmitted, bufLen);

        /* count the bytes and the amount of PDVs which were transmitted */
        bytesTransmitted += buffer.size();
        done = (bytesTransmitted>=data.size());

        /* initialize a DUL_PDV variable with the buffer's data */
        DUL_PDV pdv;
        pdv.fragmentLength = buffer.size();
        pdv.presentationContextID = presID;
        pdv.pdvType = pdvType;
        pdv.lastPDV = done;
        pdv.data = reinterpret_cast<void*>(const_cast<char*>(&buffer[0]));

        /* append this PDV to a PDV list structure, set the counter variable */
        /* to 1 since this structure contains only 1 element */
        DUL_PDVLIST pdvList;
        pdvList.count = 1;
        pdvList.pdv = &pdv;

        /* send information over the network to the other DICOM application */
        OFCondition const dulCond = DUL_WritePDVs(
            &this->get_association()->DULassociation, &pdvList);
        if (dulCond.bad())
        {
            throw Exception(
                makeDcmnetSubCondition(
                    DIMSEC_SENDFAILED, OF_error, "DIMSE Failed to send message",
                    dulCond));
        }

        /* execute callback function to indicate progress */
        if(callback)
        {
            callback(callbackContext, bytesTransmitted);
        }
    }
}

DUL_PDV
DcmtkAssociation
::_read_next_pdv()
    /*
     * This function returns the next PDV which was (earlier or just now) received on the incoming
     * socket stream. If there are no PDVs (which were already received earlier) waiting to be picked
     * up, this function will go ahead and read a new PDU (containing one or more new PDVs) from the
     * incoming socket stream.
     */
{
    /* get the next PDV from the association, in case there are still some PDVs waiting to be picked up */
    DUL_PDV pdv;
    OFCondition cond = DUL_NextPDV(
        &this->get_association()->DULassociation, &pdv);

    if (cond.bad())
    {
        /* in case DUL_NextPDV(...) did not return DUL_NORMAL, the association */
        /* did not contain any more PDVs that are waiting to be picked up. Hence, */
        /* we need to read new PDVs from the incoming socket stream. */

        /* if the blocking mode is DIMSE_NONBLOCKING and there is no data waiting after timeout seconds, report an error */
        if(!ASC_dataWaiting(
            this->get_association(), this->get_network_timeout()))
        {
            throw Exception(DIMSE_NODATAAVAILABLE);
        }

        /* try to receive new PDVs on the incoming socket stream (in detail, try to receive one PDU) */
        cond = DUL_ReadPDVs(
            &this->get_association()->DULassociation, NULL,
            DUL_BLOCK, this->get_network_timeout());

        /* check return value, if it is different from DUL_PDATAPDUARRIVED, an error occurred */
        if (cond != DUL_PDATAPDUARRIVED)
        {
            if (cond == DUL_NULLKEY || cond == DUL_ILLEGALKEY)
            {
                throw Exception(DIMSE_ILLEGALASSOCIATION);
            }
            else if (cond == DUL_PEERREQUESTEDRELEASE ||
                cond == DUL_PEERABORTEDASSOCIATION)
            {
                throw Exception(cond);
            }
            else
            {
                throw Exception(
                    makeDcmnetSubCondition(
                        DIMSEC_READPDVFAILED, OF_error,
                        "DIMSE Read PDV failed", cond));
            }
        }

        /* get the next PDV, assign it to pdv */
        cond = DUL_NextPDV(
            &this->get_association()->DULassociation, &pdv);
        if (cond.bad())
        {
            throw Exception(
                makeDcmnetSubCondition(
                    DIMSEC_READPDVFAILED, OF_error,
                    "DIMSE Read PDV failed", cond));
        }
    }

    return pdv;
}

void
DcmtkAssociation
::_progress_callback_wrapper(void *data, unsigned long bytes_count)
{
    ProgressCallbackData * encapsulated =
        reinterpret_cast<ProgressCallbackData*>(data);
    encapsulated->callback(encapsulated->data, bytes_count);
}

}
