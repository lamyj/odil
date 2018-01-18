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


.. _data set: http://dicom.nema.org/medical/dicom/current/output/chtml/part05/chapter_7.html
.. _odil::DataSet: ../../_static/doxygen/classodil_1_1_data_set.html
.. _odil::Value: ../../_static/doxygen/classodil_1_1_value.html
.. _typed: http://dicom.nema.org/medical/dicom/current/output/chtml/part05/sect_6.2.html
