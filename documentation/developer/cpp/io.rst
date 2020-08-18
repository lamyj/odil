Reading and writing files
=========================

.. highlight:: c++

Odil reads and write data sets using the three standard formats `binary`_, `JSON`_ and `XML`_.

Binary format
-------------

Two classes are responsible for reading and writing using the binary DICOM format: `odil::Reader`_ and `odil::Writer`_. Both classes handle not only whole data sets stored in DICOM files, but also give access to lower-level functions like individual elements and tags. These two classes are based on C++ streams and so can any class that implement the streams API.

The simplest usage to write a data set to a file is:

::
  
  #include <fstream>
  
  #include <odil/DataSet.h>
  #include <odil/registry.h>
  #include <odil/uid.h>
  #include <odil/Writer.h>
  
  int main()
  {
      odil::DataSet data_set;
      data_set.add("SOPClassUID", {odil::registry::RawDataStorage});
      data_set.add("SOPInstanceUID", {odil::generate_uid()});
      data_set.add("PatientName", {"Doe^John"});
      
      std::ofstream stream{"foo.dcm"};
      odil::Writer::write_file(data_set, stream);
  }

This will use a default transfer syntax (*Explicit VR Little Endian*) and add required meta information extracted from the data set. Note that the data set must include the *SOP Class UID* and *SOP Instance UID* to be written to a file. The previous example uses `odil::generate_uid`_ to create a random UID.

Reading from a file return a pair of data sets: the first element of the pair is file meta-information, the second is the data set itself.

::
  
  #include <fstream>
  #include <iostream>
  #include <tuple>

  #include <odil/DataSet.h>
  #include <odil/Reader.h>

  int main()
  {
      std::ifstream stream{"foo.dcm"};
      
      std::shared_ptr<odil::DataSet> header, data_set;
      std::tie(header, data_set) = odil::Reader::read_file(stream);
      
      std::cout << header->as_string("ImplementationVersionName")[0] << "\n";
      std::cout << data_set->as_string("SOPInstanceUID")[0] << "\n";
  }

JSON format
-----------

JSON serialization and de-serialization is managed by two functions `odil::as_json`_ and `odil::as_dataset(json)`_. Reading and writing to a file is delegated to the underlying JSON toolkit, `JsonCpp`_.

The following code sample converts a data set to JSON and writes it to a file. Refer to the JsonCpp documentation for more information about `formatting`_.

::
  
  #include <fstream>
  
  #include "odil/json_converter.h"
  
  int main()
  {
      odil::DataSet data_set;
      // Fill data set
      
      auto const json = odil::as_json(data_set);
      
      std::ofstream foo{"foo.json"};
      foo << json;
      
      return 0;
  }

The converse operation, reading from a file and converting the JSON to a data set, is similar.

::
  
  #include <fstream>
  
  #include "odil/json_converter.h"
  
  int main()
  {
      Json::Value json
      std::ifstream foo{"foo.json"};
      foo >> json;
      
      auto const data_set = odil::as_dataset(json);
      
      return 0;
  }

XML format
----------

The XML serialization and de-serialization is very similar to the JSON one: the respective functions performing these tasks are `odil::as_xml`_ and `odil::as_dataset(xml)`_. The underlying toolkit in the XML case is `Boost.PropertyTree`_.

The following snippet saves a data set to an XML file:

::
  
  #include <fstream>
  #include <boost/property_tree/xml_parser.hpp>
  #include "odil/xml_converter.h"
  
  int main()
  {
      odil::DataSet data_set;
      // Fill data set
      
      auto const xml = odil.as_xml(data_set);
      
      std::ofstream foo{"foo.xml"};
      boost::propery_tree::write_xml(foo, xml);
      
      return 0;
  }

The following snippet loads a data set from an XML file:

::
  
  #include <fstream>
  #include <boost/property_tree/xml_parser.hpp>
  #include "odil/xml_converter.h"
  
  int main()
  {
      std::ifstream foo{"foo.xml"};
      boost::property_tree::ptree xml;
      boost::propery_tree::read_xml(foo, xml);
      
      auto const data_set = odil::as_dataset(xml);
      
      return 0;
  }

.. _binary: http://dicom.nema.org/medical/dicom/current/output/chtml/part10/chapter_7.html
.. _Boost.PropertyTree: http://www.boost.org/doc/libs/1_66_0/doc/html/property_tree.html
.. _formatting: http://open-source-parsers.github.io/jsoncpp-docs/doxygen/index.html
.. _JSON: http://dicom.nema.org/medical/dicom/current/output/chtml/part18/chapter_F.html
.. _JsonCpp: https://github.com/open-source-parsers/jsoncpp
.. _odil::as_dataset(json): ../../_static/doxygen/namespaceodil.html#aecc7f7828df77fd27dd166f4748f5d5d
.. _odil::as_dataset(xml): ../../_static/doxygen/namespaceodil.html#a03f0a5fe3c4acac080a627c90ef81dee
.. _odil::as_json: ../../_static/doxygen/namespaceodil.html#a2c6f4e235991f2082e45f0db5611a177
.. _odil::as_xml: ../../_static/doxygen/namespaceodil.html#adea55ac4f5896897390b0c0474400ee8
.. _odil::Reader: ../../_static/doxygen/classodil_1_1Reader.html
.. _odil::generate_uid: ../../_static/doxygen/namespaceodil.html#ab4e34fa7513bb4d7890586e99a9d7add
.. _odil::Writer: ../../_static/doxygen/classodil_1_1Writer.html
.. _XML: http://dicom.nema.org/medical/dicom/2016b/output/chtml/part19/chapter_A.html
