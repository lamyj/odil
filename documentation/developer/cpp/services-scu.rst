DICOM services -- client side
=============================

.. highlight:: c++

:abbr:`SCUs (Service Class User)` (i.e. *clients*) are available for `C-ECHO`_, `C-FIND`_, `C-GET`_, `C-MOVE`_, and `C-STORE`_, with an abstract base class, `odil::SCU`_, implementing common features and concrete classes for each service (see table below). Every service requires an association which is correctly associated and has negotiated the corresponding abstract syntax.

.. table:: DICOM services and Odil classes
  
  +----------+-------------------+
  | Service  | Odil class        |
  +==========+===================+
  | C-ECHO   | `odil::EchoSCU`_  |
  +----------+-------------------+
  | C-FIND   | `odil::FindSCU`_  |
  +----------+-------------------+
  | C-GET    | `odil::GetSCU`_   |
  +----------+-------------------+
  | C-MOVE   | `odil::MoveSCU`_  |
  +----------+-------------------+
  | C-STORE  | `odil::StoreSCU`_ |
  +----------+-------------------+

Verifying DICOM communication
-----------------------------

The simplest service is C-ECHO, used to verify that the two peers can exchange information using DICOM. 

::
  
  #include <odil/Association.h>
  #include <odil/EchoSCU.h>
  #include <odil/registry.h>
  
  int main()
  {
      odil::Association association;
      association.set_peer_host("www.dicomserver.co.uk");
      association.set_peer_port(11112);
      association.update_parameters()
          .set_calling_ae_title("WORKSTATION")
          .set_called_ae_title("SERVER")
          .set_presentation_contexts({
              {
                  odil::registry::Verification,
                  { odil::registry::ExplicitVRLittleEndian }, true, false
              }
          });  
      association.associate();
      
      odil::EchoSCU echo_scu(association);
      echo_scu.echo();
      
      association.release();  
  }

Querying a database
-------------------

The query service, C-FIND, is parameterized by a query and either returns all the matching data sets or calls a function for each match.

::
  
  #include <iostream>
  
  #include <odil/Association.h>
  #include <odil/FindSCU.h>
  #include <odil/registry.h>
  
  void print_informations(odil::DataSet const & response)
  {
      auto const name = 
          (response.has("PatientName") && !response.empty("PatientName"))
          ?response.as_string("PatientName", 0):"(no name)";
      auto const study = 
          (response.has("StudyDescription") && !response.empty("StudyDescription"))
          ?response.as_string("StudyDescription", 0):"(no description)";
      
      std::cout << name << ": " << study << "\n";
  }
  
  int main()
  {
      auto const model = odil::registry::StudyRootQueryRetrieveInformationModelFind;
      
      odil::Association association;
      association.set_peer_host("www.dicomserver.co.uk");
      association.set_peer_port(11112);
      association.update_parameters()
          .set_calling_ae_title("WORKSTATION")
          .set_called_ae_title("SERVER")
          .set_presentation_contexts({
              { model, { odil::registry::ExplicitVRLittleEndian }, true, false }
          });  
      association.associate();
      
      odil::DataSet query;
      query.add("PatientName", { "*" });
      query.add("QueryRetrieveLevel", { "STUDY" });
      query.add("StudyDescription");
      query.add("StudyDate");
      
      odil::FindSCU find_scu(association);
      find_scu.set_affected_sop_class(model);
      
      auto const result = find_scu.find(query);
      for(auto const & dataset: result)
      {
          print_informations(dataset);
      }
      
      find_scu.find(query, print_informations);
      
      association.release();  
  }

Retrieving data sets
--------------------

The retrieval of data sets, using either C-GET or C-MOVE, is very similar to querying a database. The main difference is the additional presentation contexts required to transfer the data sets.

::
  
  #include <iostream>
  #include <string>
  #include <vector>

  #include <odil/Association.h>
  #include <odil/FindSCU.h>
  #include <odil/GetSCU.h>
  #include <odil/registry.h>

  odil::DataSet find(
      std::string const & host, unsigned int port, 
      std::string const & calling_aet, std::string const & called_aet)
  {
      auto const model = odil::registry::StudyRootQueryRetrieveInformationModelFind;
      
      odil::Association association;
      association.set_peer_host(host);
      association.set_peer_port(port);
      association.update_parameters()
          .set_calling_ae_title(calling_aet).set_called_ae_title(called_aet)
          .set_presentation_contexts({
              { model, { odil::registry::ExplicitVRLittleEndian }, true, false }
          });  
      association.associate();
      
      odil::DataSet query;
      query.add("QueryRetrieveLevel", { "STUDY" });
      query.add("StudyInstanceUID");
      query.add("SOPClassesInStudy");
      query.add("StudyDate");
      
      odil::FindSCU scu(association);
      scu.set_affected_sop_class(model);
      auto const studies = scu.find(query);
      
      association.release();
      
      if(studies.empty())
      {
          throw std::runtime_error("No matching studies");
      }
      return studies[0];
  }

  std::vector<odil::DataSet> 
  get_study(
      std::string const & host, unsigned int port, 
      std::string const & calling_aet, std::string const & called_aet,
      odil::DataSet const & study)
  {
      auto const model = odil::registry::StudyRootQueryRetrieveInformationModelGet;
      
      odil::Association association;
      association.set_peer_host(host);
      association.set_peer_port(port);
      association.update_parameters()
          .set_calling_ae_title(calling_aet).set_called_ae_title(called_aet);
      
      std::vector<odil::AssociationParameters::PresentationContext> contexts{
          { model, { odil::registry::ExplicitVRLittleEndian }, true, false }
      };
      for(auto const & abstract_syntax: study.as_string("SOPClassesInStudy"))
      {
          contexts.push_back({
              abstract_syntax, { odil::registry::ExplicitVRLittleEndian }, 
              false, true
          });
      }
      association.update_parameters().set_presentation_contexts(contexts);
      
      association.associate();
      
      odil::DataSet query;
      query.add("QueryRetrieveLevel", { "STUDY" });
      query.add("StudyInstanceUID", study.as_string("StudyInstanceUID"));
      
      odil::GetSCU scu(association);
      scu.set_affected_sop_class(model);
      auto const data_sets = scu.get(query);
      
      association.release();
      
      return data_sets;
  }

  int main()
  {
      std::string const host = "www.dicomserver.co.uk";
      unsigned int port = 11112;
      std::string const calling_aet = "WORKSTATION";
      std::string const called_aet = "SERVER";
      
      auto const study = find(host, port, calling_aet, called_aet);
      auto const data_sets = get_study(
          host, port, calling_aet, called_aet, study);
      std::cout 
          << data_sets.size() << " data set" << (data_sets.size()>0?"s":"") << " "
          << "received\n";
  }

Note that several presentation contexts must be specified: the C-GET context and one for each type of object returned by C-FIND in the *SOP Classes In Study* element.

The C-GET SCU can also be called using one or two callbacks: one which will be called for each C-STORE operation initiated by the server and an optional one which will be called for each C-GET response. The latter one may for example be used for progress information.

The C-MOVE SCU is similar to the C-GET SCU in terms of required presentation contexts (the *XXX Root Query Retrieve Information Model GET* being replaced by *XXX Root Query Retrieve Information Model MOVE*) and callbacks. The C-MOVE SCU has additional member functions used to specify where the remote peer will send the data sets: ``get_move_destination`` and ``set_move_destination``. If the move destination is the local peer and not a third party, the port of a temporary C-STORE SCP may be specified through ``set_incoming_port``. The default value of ``0`` means that no C-STORE SCP should be started.

Storing data sets
-----------------

The C-STORE SCU differs from the query/retrieve SCUs since it has no callback: each data set is either stored successfully or an exception is raised. An optional move origin (if the C-STORE SCU is created by a C-MOVE SCP) may be specified.

.. _C-ECHO: http://dicom.nema.org/medical/dicom/current/output/chtml/part04/chapter_A.html
.. _C-FIND: http://dicom.nema.org/medical/dicom/current/output/chtml/part04/sect_C.4.html#sect_C.4.1
.. _C-GET: http://dicom.nema.org/medical/dicom/current/output/chtml/part04/sect_C.4.3.html
.. _C-MOVE: http://dicom.nema.org/medical/dicom/current/output/chtml/part04/sect_C.4.2.html
.. _C-STORE: http://dicom.nema.org/medical/dicom/current/output/chtml/part04/chapter_B.html
.. _odil::EchoSCU: ../../_static/doxygen/classodil_1_1EchoSCU.html
.. _odil::FindSCU: ../../_static/doxygen/classodil_1_1FindSCU.html
.. _odil::GetSCU: ../../_static/doxygen/classodil_1_1GetSCU.html
.. _odil::MoveSCU: ../../_static/doxygen/classodil_1_1MoveSCU.html
.. _odil::SCU: ../../_static/doxygen/classodil_1_1SCU.html
.. _odil::StoreSCU: ../../_static/doxygen/classodil_1_1StoreSCU.html
