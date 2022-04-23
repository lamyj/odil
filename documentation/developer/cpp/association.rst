Network association
===================

.. highlight:: c++

The connection between two DICOM peers is handled by `odil::Association`_ and `odil::AssociationParameters`_. The former encapsulates the connection itself (TCP/IP layer and DICOM layer) while the latter handles the various options that parameterize the association (AE titles, presentation contexts, authentication, etc.).

Establishing an association
---------------------------

An association will at least require to define the application entity titles (both local and remote) the presentation contexts (i.e. representation of the data) that are acceptable for the application. The following example shows how to create a simple `odil::AssociationParameters`_ object.

::
  
  #include <odil/AssociationParameters.h>
  #include <odil/registry.h>
  
  odil::AssociationParameters
  create_parameters()
  {
      std::vector<std::string> transfer_syntaxes{
          odil::registry::ExplicitVRLittleEndian, 
          odil::registry::ExplicitVRLittleEndian
      };
      
      odil::AssociationParameters parameters;
      parameters
          .set_calling_ae_title("WORKSTATION")
          .set_called_ae_title("SERVER")
          .set_presentation_contexts({
              { 
                  odil::registry::Verification, 
                  transfer_syntaxes, 
                  odil::AssociationParameters::PresentationContext::Role::SCU
              },
              { 
                  odil::registry::PatientRootQueryRetrieveInformationModelFind,
                  transfer_syntaxes, 
                  odil::AssociationParameters::PresentationContext::Role::SCU
              }
          });
      return parameters;
  }

Note that the `odil::AssociationParameters`_ object uses parameter chaining. The objects passed to ``set_presentation_contexts`` are of type `odil::AssociationParameters::PresentationContext`_. In this example, the id of the presentation context is not specified: it is instead set to an special value by the constructor, and a valid id is then assigned in ``set_presentation_contexts``.

After setting the address and port of the remote peer, the association is established through the ``associate`` member function. Once established, the negotiated parameters (i.e. acceptable to both peers) may be obtained by the ``get_negotiated_parameters`` member function. 

::
  
  #include <odil/Association.h>
  
  int main()
  {
      odil::Association association;
      association.set_peer_host("www.dicomserver.co.uk");
      association.set_peer_port(11112);
      association.set_parameters(create_parameters());
      association.associate();
      
      auto const & contexts =
          association.get_negotiated_parameters().get_presentation_contexts();
      std::cout << "Presentation contexts (" << contexts.size() << ")\n";
      for(auto const & context: contexts)
      {
          std::cout
              << "\t"
              << odil::registry::uids_dictionary.at(context.abstract_syntax).name
              << ": "
              << odil::registry::uids_dictionary.at(context.transfer_syntaxes[0]).name
              << ", "
              << (context.scu_role_support?"SCU":"")
              << ((context.scu_role_support & context.scp_role_support)?"/":"")
              << (context.scp_role_support?"SCP":"")
              << std::endl;
      }
  }
  
Receiving an association
------------------------

Receiving an association is performed by the ``receive_association`` member function. It will listen on the given IP address and TCP port and block until an acceptable association request is received or until an error occurs. By default all association requests are deemed acceptable, and the first transfer syntax of each presentation context is accepted. Errors (unacceptable association, low-level protocol error) will throw an exception. After acceptance, the association object contains the negotiated parameters:

::
  
  #include <odil/Association.h>
  
  int main()
  {
      odil::Association association;
      
      association.receive_association(boost::asio::ip::tcp::v4(), 11112);
      
      std::cout
            << "Received association from "
            << association.get_peer_host() << ":" << association.get_peer_port()
            << std::endl ;

        auto const & contexts =
            association.get_negotiated_parameters().get_presentation_contexts();
        std::cout << "Presentation contexts (" << contexts.size() << ")\n";
        for(auto const & context: contexts)
        {
            std::cout
                << "\t"
                << odil::registry::uids_dictionary.at(context.abstract_syntax).name
                << ": "
                << odil::registry::uids_dictionary.at(context.transfer_syntaxes[0]).name
                << ", "
                << (context.scu_role_support?"SCU":"")
                << ((context.scu_role_support & context.scp_role_support)?"/":"")
                << (context.scp_role_support?"SCP":"")
                << std::endl;
        }
    }

Optionally, a callback which indicates whether the association request is acceptable or may be specified. If the request is acceptable, the callback must return the accepted parameters, otherwise it must throw an exception of type `odil::AssociationRejected`_. As an example, the default acceptation callback, which accepts the first transfer syntax for all abstract syntaxes, would be:

::
  
  #include <odil/Association.h>
  
  odil::AssociationParameters
  acceptor(odil::AssociationParameters const & input)
  {
      odil::AssociationParameters output;

      output.set_called_ae_title(input.get_called_ae_title());
      output.set_calling_ae_title(input.get_calling_ae_title());

      auto presentation_contexts = input.get_presentation_contexts();
      for(auto & presentation_context: presentation_contexts)
      {
          presentation_context.transfer_syntaxes =
              { presentation_context.transfer_syntaxes[0] };
          presentation_context.result =
              odil::AssociationParameters::PresentationContext::Result::Acceptance;
      }
      output.set_presentation_contexts(presentation_contexts);
      
      output.set_maximum_length(input.get_maximum_length());
      
      return output;
  }

.. _odil::Association: ../../_static/doxygen/classodil_1_1Association.html
.. _odil::AssociationParameters: ../../_static/doxygen/classodil_1_1AssociationParameters.html
.. _odil::AssociationParameters::PresentationContext: ../../_static/doxygen/structodil_1_1AssociationParameters_1_1PresentationContext.html
.. _odil::AssociationRejected: ../../_static/doxygen/structodil_1_1AssociationRejected.html
