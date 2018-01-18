Retrieving DICOM data sets
==========================

Based on the results of :doc:`queries <find>`, the matching data sets can be retrieved using ``odil find``:

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
  $ odil get \
    www.dicomserver.co.uk 11112 WORKSTATION SERVER \
    patient QueryRetrieveLevel=PATIENT PatientID=05256
  Completed: 1, remaining: 0, failed: 0, warning: 0
  $ LC_ALL=C ls -l
  total 3752
  -rw-rw----  1 user  group  1920876 Jan 18 12:38 2.25.310762891399725865476346432149665484276
  $ odil print 2.25.310762891399725865476346432149665484276
  ...
  Patient's Name         0010,0010 PN ['Doo^Shaggy']
  Patient ID             0010,0020 LO ['05256']
  ...

The arguments in the previous example are the same as in :doc:`odil find <find>`

By default, the files will be stored in the current directory and named according to the value of their *SOP Instance UID* element.

Modifying the storage
---------------------

The files hierarchy can be modified with the ``--layout`` (or ``-l``) option. The default is ``flat`` layout, where all the files are in the same directory; a ``tree`` where a *patient/study/series* hierarchy is created can also be used:

.. code-block:: console
  
  $ odil get -l tree \
    www.dicomserver.co.uk 11112 WORKSTATION SERVER \
    study QueryRetrieveLevel=STUDY StudyInstanceUID=1.2.76.0.7230010.3.2.107
  Completed: 18, remaining: 0, failed: 0, warning: 0
  $ tree
  .
  └── BEETHOVEN^LUDWIG
      └── 1
          └── 1
              ├── 1.2.826.0.1.3680043.6.11323.24626.20170922143703.136.48
              ├── 1.2.826.0.1.3680043.6.11840.18756.20170922143703.136.44
              ├── 1.2.826.0.1.3680043.6.14604.32391.20170922143702.136.12
              ...

To `comply with the DICOM standard`_, the files and directories created by ``odil get`` can also be created with ISO-9660 names with the ``--iso-9660`` (or ``-I``) option:

.. code-block:: console
  
  $ odil get -I \
    www.dicomserver.co.uk 11112 WORKSTATION SERVER \
    study QueryRetrieveLevel=STUDY StudyInstanceUID=1.2.76.0.7230010.3.2.107
  Completed: 18, remaining: 0, failed: 0, warning: 0
  $ ls -l
  total 218880
  -rw-rw----  1 user  group  6221840 Jan 18 13:02 IM000001
  -rw-rw----  1 user  group  6221840 Jan 18 13:02 IM000002
  -rw-rw----  1 user  group  6221844 Jan 18 13:02 IM000003
  ...

This option may be used along with the layout option:

.. code-block:: console
  
  $ odil get -l tree -I \
    www.dicomserver.co.uk 11112 WORKSTATION SERVER \
    study QueryRetrieveLevel=STUDY StudyInstanceUID=1.2.76.0.7230010.3.2.107
  Completed: 18, remaining: 0, failed: 0, warning: 0
  $ tree
  .
  └── BEETHOVE
      └── 1
          └── 1
              ├── IM000001
              ├── IM000002
              ├── IM000003
              ...


Creating a DICOMDIR
-------------------

A DICOMDIR can be created for the retrieved files by using the ``--dicomdir`` (or ``-D``) option. Additional record keys can be specified using the same options than in :doc:`odil dicomdir <dicomdir>`. Creating a DICOM requires the use of ISO-9660 file names, but may use flat or hierarchical storage.

.. _comply with the DICOM standard: http://dicom.nema.org/medical/dicom/current/output/chtml/part10/sect_8.2.html
