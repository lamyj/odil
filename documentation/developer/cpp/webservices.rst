DICOM web services
==================

.. highlight:: c++

.. note::
  
  Even though Odil implements the DICOM web services, it does not contain an HTTP server; the library however contains everything required to create and parse the content of HTTP requests and responses.

The web services implementation in Odil revolves around two classes: `odil::webservices::HTTPRequest`_ and `odil::webservices::HTTPResponse`_ which create and parse HTTP requests and responses. Each web service is implemented by a pair of classes which generate and parse the specific service requests and responses, as show in the table below.

.. table:: DICOM wen services and Odil classes
  
  +------------+--------------------------------------+
  | Service    | Odil classes                         |
  +============+======================================+
  | `QIDO-RS`_ | `odil::webservices::QIDORSRequest`_, |
  |            | `odil::webservices::QIDORSResponse`_ |
  +------------+--------------------------------------+
  | `WADO-RS`_ | `odil::webservices::WADORSRequest`_, |
  |            | `odil::webservices::WADORSResponse`_ |
  +------------+--------------------------------------+
  | `STOW-RS`_ | `odil::webservices::STOWRSRequest`_, |
  |            | `odil::webservices::STOWRSResponse`_ |
  +------------+--------------------------------------+

Common data structures
----------------------

URLs are represented by `odil::webservices::URL`_ and contain fields as defined in `RFC 3986`_ (scheme, authority, path, query and fragment). The ``URL`` class can parse a string to the URL components and be converted to a string:

::

  #include <iostream>
  #include <odil/webservices/URL.h>
  
  int main()
  {
      auto url = odil::webservices::URL::parse("foo://info.example.com?fred");
      url.path = "/people";
      std::cout << url << "\n";
  }

HTTP messages, i.e. requests and responses, are handled by `odil::webservices::HTTPRequest`_ and `odil::webservices::HTTPResponse`_, both having serialization (i.e. ``operator<<``) and de-serialization (i.e. ``operator>>``). Both contains headers and a body; the HTTP request contains the method (e.g. *GET* or *POST*), the target URL, the HTTP version, the headers and the body; the HTTP response contains the HTTP version, the status and its text representation (i.e. the reason), the headers and the body.

::
  
  #include <iostream>
  #include <sstream>
  #include <odil/webservices/HTTPRequest.h>
  #include <odil/webservices/HTTPResponse.h>

  int main()
  {
      odil::webservices::HTTPRequest request{
          "POST", odil::webservices::URL::parse("https://www.example.com:80/")};
      request.set_header("Content-Type", "application/json");
      request.set_body("{\"foo\": \"bar\" }");
      std::cout << request << "\n";
      
      std::istringstream stream(
          "HTTP/1.0 200 OK\n"
          "Content-Type: application/json\n");
      
      odil::webservices::HTTPResponse response;
      stream >> response;
      std::cout << response.has_header("Content-Type") << "\n";
  }


Querying a database
-------------------

The following example show how to use `Boost.Asio`_ in order to create a very simple HTTP client. The ``http_client`` function is assume to be defined in subsequent examples.

::
  
  #include <boost/asio.hpp>
  #include <odil/webservices/HTTPRequest.h>
  #include <odil/webservices/HTTPResponse.h>
  #include <odil/webservices/URL.h>

  odil::webservices::HTTPResponse 
  http_client(
      std::string const & host, std::string const & port,
      odil::webservices::HTTPRequest const & request)
  {
      boost::asio::ip::tcp::iostream stream;
      stream.connect(host, port);
      
      stream << request;
      
      odil::webservices::HTTPResponse response;
      stream >> response;
      
      return response;
  }

QIDO-RS queries are similar to C-FIND queries: both have a query root and a data set. The query root is specified by ``set_affected_sop_class`` in C-services, while in web services it is specified by `odil::webservices::Selector`_. The data set is specified the same way in C-services and web services: non-empty elements are used as filters while empty terms are used to specified extra fields to be returned. The following example shows how to retrieve all the studies of a given patient through QIDO:

::
  
  #include <iostream>
  #include <odil/DataSet.h>
  #include <odil/webservices/QIDORSRequest.h>
  #include <odil/webservices/QIDORSResponse.h>
  #include <odil/webservices/Selector.h>
  #include <odil/webservices/URL.h>

  int main()
  {
      auto const root = odil::webservices::URL::parse(
          "http://dicomserver.co.uk:81/qido");
      
      odil::webservices::QIDORSRequest qido_request(root);
      
      odil::webservices::Selector selector;
      selector.set_study("");
      
      odil::DataSet query;
      query.add("PatientName", {"Doe"});
      query.add("StudyDescription");
      
      qido_request.request_datasets(
          odil::webservices::Representation::DICOM_JSON, selector, query,
          false, -1, 0, true);
      
      auto http_request = qido_request.get_http_request();
      auto const http_response = http_client(
          "dicomserver.co.uk", "81", http_request);
      
      odil::webservices::QIDORSResponse qido_response(http_response);
      
      std::cout 
          << "Got " << qido_response.get_data_sets().size() << " data sets" 
          << "\n";
  }
  

Retrieving data sets
--------------------

The data sets to be received through WADO-RS works are specified by the selector. Using WADO-RS is otherwise very similar to using QIDO-RS:

::

  #include <iostream>
  #include <odil/DataSet.h>
  #include <odil/webservices/QIDORSRequest.h>
  #include <odil/webservices/QIDORSResponse.h>
  #include <odil/webservices/WADORSRequest.h>
  #include <odil/webservices/WADORSResponse.h>
  #include <odil/webservices/Selector.h>
  #include <odil/webservices/URL.h>

  int main()
  {
      odil::webservices::QIDORSRequest qido_request(
          odil::webservices::URL::parse("http://dicomserver.co.uk:81/qido"));
      
      odil::DataSet query;
      query.add("PatientName", {"Doe"});
      
      qido_request.request_datasets(
          odil::webservices::Representation::DICOM_JSON, 
          std::map<std::string, std::string>({{"studies", ""}}),
          query, false, 1, 0, true);
      
      auto http_request = qido_request.get_http_request();
      auto http_response = http_client("dicomserver.co.uk", "81", http_request);
      
      odil::webservices::QIDORSResponse const qido_response(http_response);
      auto const study = qido_response.get_data_sets()[0];
      
      odil::webservices::WADORSRequest wado_request(
          odil::webservices::URL::parse("http://dicomserver.co.uk:81/wado")); 
      wado_request.request_dicom(
          odil::webservices::Representation::DICOM_JSON,
          std::map<std::string, std::string>({
              {"studies", study.as_string("StudyInstanceUID")[0]}})
      );
      
      http_request = wado_request.get_http_request();
      http_response = http_client("dicomserver.co.uk", "81", http_request);
      
      odil::webservices::WADORSResponse const wado_response(http_response);
      auto const data_sets = wado_response.get_data_sets();
      std::cout 
          << "Got " << wado_response.get_data_sets().size() << " data sets" 
          << "\n";
  }

Storing data sets
-----------------

STOW-RS requires both a selector and a vector of data sets. The selector must contain the *studies* term, and may specify the Study Instance UID:

::
  
  #include <iostream>
  #include <odil/DataSet.h>
  #include <odil/uid.h>
  #include <odil/webservices/STOWRSRequest.h>
  #include <odil/webservices/STOWRSResponse.h>
  #include <odil/webservices/Selector.h>
  #include <odil/webservices/URL.h>

  int main()
  {
      odil::webservices::STOWRSRequest stow_request(
          odil::webservices::URL::parse("http://dicomserver.co.uk:81/stow"));
      
      odil::DataSet data_set;
      data_set.add("PatientName", {"Doe^John"});
      data_set.add("PatientID", {odil::generate_uid()});
      
      data_set.add("StudyInstanceUID", {odil::generate_uid()});
      
      data_set.add("Modality", {"OT"});
      data_set.add("SeriesInstanceUID", {odil::generate_uid()});
      
      data_set.add("SOPClassUID", {odil::registry::RawDataStorage});
      data_set.add("SOPInstanceUID", {odil::generate_uid()});
      
      stow_request.request_dicom(
          {data_set}, std::map<std::string,std::string>({{"studies", ""}}),
          odil::webservices::Representation::DICOM_XML);
      
      auto http_request = stow_request.get_http_request();
      http_request.set_http_version("HTTP/1.1");
      http_request.set_header("Host", stow_request.get_base_url().authority);
      http_request.set_header("Content-Length", std::to_string(http_request.get_body().size()));
      http_request.set_header("Accept", "application/dicom+xml");
      http_request.set_header("Connection", "close");
      
      auto const http_response = http_client(
        "dicomserver.co.uk", "81", http_request);
      
      odil::webservices::STOWRSResponse const stow_response(http_response);
      auto const responses = stow_response.get_store_instance_responses();
  }

.. _Boost.Asio: http://www.boost.org/doc/libs/release/libs/asio/

.. _odil::webservices::HTTPRequest:
  ../../_static/doxygen/classodil_1_1webservices_1_1HTTPRequest.html

.. _odil::webservices::HTTPResponse: 
  ../../_static/doxygen/classodil_1_1webservices_1_1HTTPResponse.html

.. _odil::webservices::QIDORSRequest: 
  ../../_static/doxygen/classodil_1_1webservices_1_1QIDORSRequest.html

.. _odil::webservices::QIDORSResponse: 
  ../../_static/doxygen/classodil_1_1webservices_1_1QIDORSResponse.html

.. _odil::webservices::Selector: 
  ../../_static/doxygen/classodil_1_1webservices_1_1Selector.html

.. _odil::webservices::STOWRSRequest: 
  ../../_static/doxygen/classodil_1_1webservices_1_1STOWRSRequest.html

.. _odil::webservices::STOWRSResponse: 
  ../../_static/doxygen/classodil_1_1webservices_1_1STOWRSResponse.html

.. _odil::webservices::URL: 
  ../../_static/doxygen/structodil_1_1webservices_1_1URL.html

.. _odil::webservices::WADORSRequest: 
  ../../_static/doxygen/classodil_1_1webservices_1_1WADORSRequest.html

.. _odil::webservices::WADORSResponse: 
  ../../_static/doxygen/classodil_1_1webservices_1_1WADORSResponse.html

.. _QIDO-RS: 
  http://dicom.nema.org/medical/dicom/current/output/chtml/part18/sect_6.7.html

.. _RFC 3986: https://tools.ietf.org/html/rfc3986

.. _STOW-RS: 
  http://dicom.nema.org/medical/dicom/current/output/chtml/part18/sect_6.6.html

.. _WADO-RS: 
  http://dicom.nema.org/medical/dicom/current/output/chtml/part18/sect_6.5.html
