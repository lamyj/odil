Verifying DICOM communication
=============================

Similarly to the ICMP ping, DICOM has a `communication verification service`_ which checks that two peers can communicate at the DICOM level. It is accessible through ``odil echo``:

.. code-block:: bash
  
  odil echo www.dicomserver.co.uk 11112 WORKSTATION SERVER

The first two arguments are the TCP/IP information (respectively the host and port) and the last two arguments are the `name of the DICOM applications`_ (respectively the calling and called AE titles). If the DICOM ping fails, the error is displayed; otherwise the command just returns.

.. _communication verification service: http://dicom.nema.org/medical/dicom/current/output/chtml/part04/chapter_A.html
.. _name of the DICOM applications: http://dicom.nema.org/medical/dicom/current/output/chtml/part08/chapter_C.html
