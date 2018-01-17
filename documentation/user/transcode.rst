Convert a binary DICOM file
===========================

Binary DICOM files can be converted to their JSON or XML representation or recoded using another transfer syntax using ``odil transcode``.

Convert to JSON
---------------

Specify ``-f json`` to convert to JSON:

.. code-block:: console

  $ odil transcode -f json file.dcm /dev/stdout
  { "00080005":{"Value":["ISO_IR 100"],"vr":"CS"}, ... }

If the output is to be read by a human being, the condensed format is not appropriate, and the result can be pretty-printed using the ``-p`` flag:

.. code-block:: console

  $ odil transcode -f json -p file.dcm /dev/stdout
  {
    "00080005" : {
      "Value" : [ "ISO_IR 100" ],
      "vr" : "CS"
    },
    ...
    "00080016" : {
      "Value" : [ "1.2.840.10008.5.1.4.1.1.4" ],
      "vr" : "UI"
    },
    ...
  }

Convert to XML
--------------

Similarly, specify ``-f xml`` to convert to XML, with optional pretty-printing with the ``-p`` flag:

.. code-block:: console

  $ odil transcode -f xml -p file.dcm /dev/stdout
  <?xml version="1.0" encoding="utf-8"?>
  <NativeDicomModel>
    <DicomAttribute vr="CS" tag="00080005" keyword="SpecificCharacterSet">
      <Value number="1">ISO_IR 100</Value>
    </DicomAttribute>
    ...
    <DicomAttribute vr="UI" tag="00080016" keyword="SOPClassUID">
      <Value number="1">1.2.840.10008.5.1.4.1.1.4</Value>
    </DicomAttribute>
    ...
  </NativeDicomModel>

Change the transfer syntax
--------------------------

The transfer syntax of a file can also be changed through the ``-t`` flag with either a transfer syntax UID or a transfer syntax name:

.. code-block:: console

  $ odil transcode -t ExplicitVRLittleEndian input.dcm output.dcm
  $ odil print -H -u output.dcm | grep "Transfer Syntax"
  Transfer Syntax UID  0002,0010 UI ['Explicit VR Little Endian']
