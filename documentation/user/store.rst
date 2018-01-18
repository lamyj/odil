Storing DICOM data on a remote server
=====================================

Storing DICOM data on a remote server is performed through ``odil store``:

.. code-block:: bash
  
  odil store \
    www.dicomserver.co.uk 11112 WORKSTATION SERVER \
    file1.dcm file2.dcm fileN.dcm

The first four arguments are the TCP/IP information (respectively the host and port) and the `name of the DICOM applications`_ (respectively the calling and called AE titles). The remaining arguments are the paths to the files to be sent to the remote application.

.. _name of the DICOM applications: http://dicom.nema.org/medical/dicom/current/output/chtml/part08/chapter_C.html
