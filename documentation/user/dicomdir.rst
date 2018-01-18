Create a DICOMDIR
=================

From a set of DICOM files, the command ``odil dicomdir`` creates a DICOMDIR (i.e. a `Basic Directory`_) referencing those files:

.. code-block:: console
  
  $ odil dicomdir /some/location/images/* /some/location
  $ odil print /some/location/DICOMDIR
  ...
  Directory Record Sequence  0004,1220 SQ (sequence, 13 items)
    ...
    Directory Record Type    0004,1430 CS ['PATIENT']
    Patient's Name           0010,0010 PN ['Doe^John']
    ...
    
    ...
    Directory Record Type    0004,1430 CS ['STUDY']
    Study Description        0008,1030 LO ['Brain 32 ch']
    ...
    
    ...
    Directory Record Type    0004,1430 CS ['SERIES']
    Modality                 0008,0060 CS ['MR']
    ...
    
    ...
    Directory Record Type    0004,1430 CS ['IMAGE']
    Referenced File ID       0004,1500 CS ['images', 'dicom', '23492.dcm']
    ...
    
    ...

The last argument is the path to the directory where the DICOMDIR will be created. The DICOM standard requires that this directory contains all the referenced files.

Adding extra elements to records
--------------------------------

In the previous output, note that *Study Description* is present but *Series Description* is not. By default, ``odil dicomdir`` only create `mandatory elements for each record`_. This behavior can be changed using the following options:

+--------------+-------------------+-------------------------+
| Record level | Long option       | Short option            |
+==============+===================+=========================+
| *PATIENT*    | ``--patient-key`` | ``-p``                  |
+--------------+-------------------+-------------------------+
| *STUDY*      | ``--study-key``   | ``-S`` (capital *S*)    |
+--------------+-------------------+-------------------------+
| *SERIES*     | ``--series-key``  | ``-s`` (lower-case *s*) |
+--------------+-------------------+-------------------------+
| *IMAGE*      | ``--image-key``   | ``-i``                  |
+--------------+-------------------+-------------------------+

The element is specified its keyword and an optional `type`_:

- *1*: the element must be present and non-null in all referenced files
- *2*: the element must be present in all referenced files but may be null
- *3*: the element may be missing in referenced files. This is the default value.

To add the *Series Description* element to all *SERIES*-level record:

.. code-block:: console
  
  $ odil dicomdir -s SeriesDescription /some/location/images/* /some/location
  $ odil print /some/location/DICOMDIR
  ...
  Directory Record Sequence  0004,1220 SQ (sequence, 13 items)
    ...

    ...
    Directory Record Type    0004,1430 CS ['SERIES']
    Modality                 0008,0060 CS ['MR']
    Series Description       0008,103e LO ['di_TE00_TI2000']
    ...
    
    ...

.. _Basic Directory: http://dicom.nema.org/medical/dicom/current/output/chtml/part03/chapter_F.html
.. _mandatory elements for each record: http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_F.5.html
.. _type: http://dicom.nema.org/medical/dicom/current/output/chtml/part05/sect_7.4.html
