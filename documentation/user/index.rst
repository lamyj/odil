User documentation
==================

*Odil* (the software package) includes a command-line tool called ``odil`` which gives access to:

.. toctree::
  :maxdepth: 2
  
  print
  transcode
  dicomdir
  echo
  find
  get
  store

.. note:: If Odil was installed from source, the command-line tool requires the Python wrappers.

Complete usage for each command and for the whole tool can be obtained with the ``-h`` flag:

.. code-block:: console
  
  $ odil print -h
  usage: odil print [-h] [--print-header] [--decode-uids]
                    [--verbosity {warning,info,debug}]
                    FILE [FILE ...]

    positional arguments:
    FILE                  Input files

    optional arguments:
    -h, --help            show this help message and exit
    --print-header, -H    Print the header as well as the data set 
                          (default: False)
    --decode-uids, -u     Print human-friendly name of known UIDs 
                          (default: False)
    --verbosity {warning,info,debug}, -v {warning,info,debug}
