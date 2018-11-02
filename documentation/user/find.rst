Querying a DICOM database
=========================

`Queries to a DICOM database`_ are performed through ``odil find``:

.. code-block:: console
  
  $ odil find \
    www.dicomserver.co.uk 11112 WORKSTATION SERVER \
    patient \
    QueryRetrieveLevel=PATIENT PatientName PatientID
  347 answers
  Specific Character Set 0008,0005 CS []
  Query/Retrieve Level   0008,0052 CS ['PATIENT']
  Retrieve AE Title      0008,0054 AE ['SERVER']
  Patient's Name         0010,0010 PN ['Abdomen^Abby^']
  Patient ID             0010,0020 LO ['AA']
  
  Specific Character Set 0008,0005 CS []
  Query/Retrieve Level   0008,0052 CS ['PATIENT']
  Retrieve AE Title      0008,0054 AE ['SERVER']
  Patient's Name         0010,0010 PN ['Doo^Scooby']
  Patient ID             0010,0020 LO ['05255']
  
  ...

The first four arguments are the TCP/IP information (respectively the host and port) and the `name of the DICOM applications`_ (respectively the calling and called AE titles). The fifth argument is the `information model`_ to use in the query (either ``patient`` or ``study``). Following are the query elements. Each query element may be either an element keyword and a value (as *QueryRetrieveLevel=PATIENT*) or only the element keyword (as *PatientName* or *PatientID*). In the former case, the value will be matched against the records on the remote application and in the latter case the keyword indicates that the user wishes to retrieve the value from the server.

The *QueryRetrieveLevel* element must be specified and determines what objects the server will return (``PATIENT``, ``STUDY``, ``SERIES``, ``IMAGE``).

The various `attribute matching rules`_ can be used:

.. code-block:: console
  
  $ odil find \
    www.dicomserver.co.uk 11112 WORKSTATION SERVER \
    patient \
    QueryRetrieveLevel=PATIENT PatientName=Doo* PatientID
  2 answers
  Specific Character Set 0008,0005 CS []
  Query/Retrieve Level   0008,0052 CS ['PATIENT']
  Retrieve AE Title      0008,0054 AE ['SERVER']
  Patient's Name         0010,0010 PN ['Doo^Scooby']
  Patient ID             0010,0020 LO ['05255']

  Specific Character Set 0008,0005 CS []
  Query/Retrieve Level   0008,0052 CS ['PATIENT']
  Retrieve AE Title      0008,0054 AE ['SERVER']
  Patient's Name         0010,0010 PN ['Doo^Shaggy']
  Patient ID             0010,0020 LO ['05256']

.. _attribute matching rules: http://dicom.nema.org/medical/dicom/current/output/chtml/part04/sect_C.2.2.2.html
.. _information model: http://dicom.nema.org/medical/dicom/current/output/chtml/part04/sect_C.3.html
.. _name of the DICOM applications: http://dicom.nema.org/medical/dicom/current/output/chtml/part08/chapter_C.html
.. _Queries to a DICOM database: http://dicom.nema.org/medical/dicom/current/output/chtml/part04/sect_C.4.html#sect_C.4.1
