DICOM services -- server side
=============================

.. highlight:: c++

The design of the :abbr:`SCPs (Service Class Provider)`: an abstract base class, `odil::SCP`_, implementing common features and concrete classes for each service (see table below). Every service requires an association which is correctly associated and has negotiated the corresponding abstract syntax.

.. table:: DICOM services and Odil classes
  
  +-------------+-------------------+
  | Service     | Odil class        |
  +=============+===================+
  | `C-ECHO`_   | `odil::EchoSCP`_  |
  +-------------+-------------------+
  | `C-FIND`_   | `odil::FindSCP`_  |
  +-------------+-------------------+
  | `C-GET`_    | `odil::GetSCP`_   |
  +-------------+-------------------+
  | `C-MOVE`_   | `odil::MoveSCP`_  |
  +-------------+-------------------+
  | `C-STORE`_  | `odil::StoreSCP`_ |
  +-------------+-------------------+

The SCP classes handle the low-level message exchange, and the action (e.g. querying a data base or storing a file) is left to the user. If the SCP's responses contain no data set (C-ECHO, C-STORE), the action is a callback with a single parameter (the request message) which returns the status of the operation; if the SCP returns data sets (C-FIND, C-GET, C-MOVE), the action is specified as a class which inherits from `odil::SCP::DataSetGenerator`_. A data set generator must specify the following member functions:

- ``void initialize(message::Request const &request)``: initialize the generator given an incoming request
- ``bool done()``: test whether all elements have been generated
- ``void next()``: prepare the next element
- ``DataSet get()``: return the current element

The SCP may process an already-existing message using the ``operator()`` or may receive a message on the underlying association and process it through the ``receive_and_process`` member function. In the former case, the function will return once the response has been sent; in the latter case, the function will block until a message has been received *and* the response has been sent.

SCPs returning no data set
--------------------------

The following example show the use of a C-ECHO SCP. The message handler prints a message on the server console and returns successfully.

::

  #include <iostream>
  
  #include <odil/Association.h>
  #include <odil/EchoSCP.h>
  #include <odil/message/CEchoRequest.h>
  
  odil::Value::Integer echo(odil::message::CEchoRequest const & request)
  {
      std::cout << "Received echo\n";
      std::cout << "  ID: " << request.get_message_id() << "\n";
      std::cout << "  Affected SOP Class UID: " << request.get_affected_sop_class_uid() << "\n";
      return odil::message::Response::Success;
  }
    
  int main()
  {
      odil::Association association;
      association.receive_association(boost::asio::ip::tcp::v4(), 11112);
      odil::EchoSCP scp(association, echo);
      scp.receive_and_process();
  }

SCPs returning data sets
------------------------

The following example shows an implementation of a ``DataSetGenerator`` which simulates the query of a database returning two matching data sets. The generator is the used in a C-FIND SCP.

::
  
  #include <vector>
  
  #include <odil/Association.h>
  #include <odil/DataSet.h>
  #include <odil/FindSCP.h>
  #include <odil/message/CFindRequest.h>
  
  class FindGenerator: public odil::SCP::DataSetGenerator
  {
  public:
      FindGenerator()
      {
          // Nothing to do
      }

      virtual ~FindGenerator()
      {
          // Nothing to do.
      }

      virtual void initialize(odil::message::CFindRequest const & )
      {
          odil::DataSet data_set_1;
          data_set_1.add(odil::registry::PatientName, {"Hello^World"});
          data_set_1.add(odil::registry::PatientID, {"1234"});
          this->_responses.push_back(data_set_1);

          odil::DataSet data_set_2;
          data_set_2.add(odil::registry::PatientName, {"Doe^John"});
          data_set_2.add(odil::registry::PatientID, {"5678"});
          this->_responses.push_back(data_set_2);

          this->_response_iterator = this->_responses.begin();
      }

      virtual bool done() const
      {
          return (this->_response_iterator == this->_responses.end());
      }

      virtual odil::DataSet get() const
      {
          return *this->_response_iterator;
      }

      virtual void next()
      {
          ++this->_response_iterator;
      }


  private:
      std::vector<odil::DataSet> _responses;
      std::vector<odil::DataSet>::const_iterator _response_iterator;
  };
  
  int main()
  {
      odil::Association association;
      association.receive_association(boost::asio::ip::tcp::v4(), 11112);
      
      FindGenerator generator;
      odil::FindSCP scp(association, generator);
      scp.receive_and_process();
  }

The generators used by the C-GET and C-MOVE SCPs have an extra member function, ``count``, which must return the number of data sets that the SCP will send. Moreover, since C-MOVE needs to establish a new association to send its responses, generators for the C-MOVE SCPs must implement the ``get_association`` member function which returns a non-associated association.

SCP dispatcher
--------------

In order to facilitate the development of a DICOM server handling multiple services, the `odil::SCPDispatcher`_ class maps the type of a message to an instance of a SCP and dispatches an incoming message to the correct SCP.

::
  
  #include <iostream>
  #include <memory>
  
  #include <odil/EchoSCP.h>
  #include <odil/FindSCP.h>
  #include <odil/message/CEchoRequest.h>
  #include <odil/message/CFindRequest.h>
  #include <odil/SCPDispatcher.h>
  
  // See above for the definitions
  odil::Value::Integer echo(odil::message::CEchoRequest const & request);
  class FindGenerator;
    
  int main()
  {
      odil::Association association;
      association.receive_association(boost::asio::ip::tcp::v4(), 11112);
      
      auto echo_scp = std::make_shared<odil::EchoSCP>(association, echo);
      auto find_scp = std::make_shared<odil::FindSCP>(
        association, std::make_shared<FindGenerator>());
      
      odil::SCPDispatcher dispatcher(association);
      dispatcher.set_scp(odil::message::Message::Command::C_ECHO_RQ, echo_scp);
      dispatcher.set_scp(odil::message::Message::Command::C_FIND_RQ, find_scp);
      
      bool done = false;
      while(!done)
      {
          try
          {
              dispatcher.dispatch();
          }
          catch(odil::AssociationReleased const &)
          {
              std::cout << "Peer released association" << std::endl;
              done = true;
          }
          catch(odil::AssociationAborted const & e)
          {
              std::cout
                  << "Peer aborted association, "
                  << "source: " << int(e.source) << ", "
                  << "reason: " << int(e.reason)
                  << std::endl;
              done = true;
          }
      }
  }

.. _C-ECHO: http://dicom.nema.org/medical/dicom/current/output/chtml/part04/chapter_A.html
.. _C-FIND: http://dicom.nema.org/medical/dicom/current/output/chtml/part04/sect_C.4.html#sect_C.4.1
.. _C-GET: http://dicom.nema.org/medical/dicom/current/output/chtml/part04/sect_C.4.3.html
.. _C-MOVE: http://dicom.nema.org/medical/dicom/current/output/chtml/part04/sect_C.4.2.html
.. _C-STORE: http://dicom.nema.org/medical/dicom/current/output/chtml/part04/chapter_B.html
.. _odil::EchoSCP: ../../_static/doxygen/classodil_1_1EchoSCP.html
.. _odil::FindSCP: ../../_static/doxygen/classodil_1_1FindSCP.html
.. _odil::GetSCP: ../../_static/doxygen/classodil_1_1GetSCP.html
.. _odil::MoveSCP: ../../_static/doxygen/classodil_1_1MoveSCP.html
.. _odil::SCP: ../../_static/doxygen/classodil_1_1SCP.html
.. _odil::SCP::DataSetGenerator: ../../_static/doxygen/classodil_1_1SCP_1_1DataSetGenerator.html
.. _odil::SCPDispatcher: ../../_static/doxygen/classodil_1_1SCPDispatcher.html
.. _odil::StoreSCP: ../../_static/doxygen/classodil_1_1StoreSCP.html
