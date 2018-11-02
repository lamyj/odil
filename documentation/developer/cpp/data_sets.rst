Data sets, elements and values
==============================

.. highlight:: c++

The `data set`_ is the central data structure in the DICOM standard and in Odil. In Odil, it is a dictionary of elements (i.e. `typed`_ values), where the key is a tag, identifying the semantics of the element. Data sets are handled by the `odil::DataSet`_ class.

The `odil::Value`_ class holds the actual value of an element, stored as an array of one of five types, each of them mapped to some of the 31 VRs of DICOM:

- Integers (IS, SL, SS, UL, US)
- Reals (DS, FL, FD)
- Strings (AE, AS, AT, CS, DA, DT, LO, LT, PN, SH, ST, TM, UC, UI, UR, UT)
- Binary (OB, OD, OF, OL, OW, UN)
- DataSets (SQ)

The default constructor creates an empty data set, as can be shown by the ``size()`` or the ``empty()`` member function:

::
  
  #include <iostream>
  #include <odil/DataSet.h>

  int main()
  {
      odil::DataSet data_set;
      std::cout << std::boolalpha
          << "Size: " << data_set.size() << ", empty: " << data_set.empty()
          << "\n";
  }

Adding an element is done through the ``add()`` member function. All public tags are pre-defined in ``odil::registry``, but can also be created when needed. Most of the functions that have `odil::Tag`_ parameters may also use the keywords of public tags (an exception will be raised if no such name exists in the directory). 

::
  
  #include <odil/DataSet.h>
  #include <odil/registry.h>
  #include <odil/Tag.h>

  int main()
  {
      odil::DataSet data_set;
      
      // Pre-defined tag
      data_set.add(odil::registry::PatientName, {"Doe^John"});
      // Temporary Tag object for Patient ID
      data_set.add(odil::Tag(0x0010, 0x0020), {"12345"});
      // Using the keyword of the tag
      data_set.add("PixelSpacing", {1.0, 1.0});
  }

In the previous example, note that the type of the value and the VR of the element are inferred from the parameters. *Patient Name* and *Patient ID* will have a *Strings* value, and *Pixel Spacing* will have a *Reals* value. The `VR`_ is inferred from the dictionary, but can be explicit, as in ``data_set.add(tag, value, odil::VR::SL)``.

Access to already-inserted elements is done through one of the ``as_XXX(tag)`` functions (``as_int``, ``as_real``, ``as_string``, ``as_data_set``, ``as_binary``). The type of the element will be checked, and an exception will be raised if there is a mismatch. The presence of an element can be checked with the ``has(tag)`` member function and the type of an element with the ``is_XXX(tag)`` member functions.

::
  
  #include <iostream>
  #include <odil/DataSet.h>
  
  int main()
  {
      odil::DataSet data_set;
      
      data_set.add("PatientName", {"Doe^John"});
      std::cout << data_set.as_string("PatientName")[0] << "\n";
      
      data_set.as_string("PatientName") = {"Bloggs^Jane"};
      
      std::cout << "PatientName " 
          << (data_set.is_string("PatientName")?"contains ":"does not contain ")
          << "strings" << "\n";
      
      std::cout << "PatientID is " 
          << (data_set.has("PatientID")?"present":"missing") << "\n";  
  }

Note that the value of an element is *always an array* even if it is empty or contains only one element. The number of items in an element can be obtained with the ``size(tag)`` member function:

::
  
  #include <iostream>
  #include <odil/DataSet.h>
  
  int main()
  {
      odil::DataSet data_set;
      
      // Empty element
      data_set.add("PatientName");
      
      std::cout << std::boolalpha
          << "Size of PatientName: " << data_set.size("PatientName") 
          << ", empty: " << data_set.empty("PatientName")
          << "\n";
  }

.. _data set: http://dicom.nema.org/medical/dicom/current/output/chtml/part05/chapter_7.html
.. _odil::DataSet: ../../_static/doxygen/classodil_1_1DataSet.html
.. _odil::Tag: ../../_static/doxygen/classodil_1_1Tag.html
.. _odil::Value: ../../_static/doxygen/classodil_1_1Value.html
.. _VR: ../../_static/doxygen/VR_8h.html
.. _typed: http://dicom.nema.org/medical/dicom/current/output/chtml/part05/sect_6.2.html
