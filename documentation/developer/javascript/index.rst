Javascript API
==============

.. highlight:: javascript

As opposed to the :doc:`Python API <../python/index>`, the Javascript API covers fewer parts of the :doc:`C++ API <../cpp/index>` and differs more often. Due to the focus of Javascript to web applications, the wrappers cover basic manipulation of data sets and the DICOM web services.

Adding Odil.js to an HTML document
----------------------------------

The following example show how to integrate Odil.js in an HTML web page:

.. code-block:: html

  <!doctype html>
  <html>
    <head>
      <title>Odil web app</title>
    </head>
    
    <body>
      <script>
        function main() {
          window.odil = Module;
        }
        
        var Module = {
            onRuntimeInitialized: main
        };
      </script>
      <script src="odil.js"></script>
    </body>
  </html>

Tags
----

The ``Tag`` object exposes the ``group`` and ``element`` member variables, and the ``is_private`` and ``get_name`` member functions. Additional C++ operators are exposed as Javascript member functions:

.. table:: C++ operators on Tag objects and their Javascript equivalents

  +------------------------+------------------------------+
  | C++                    | Javascript                   |
  +========================+==============================+
  | ``tag1 == tag2;``      | ``tag1.equal(tag2);``        | 
  +------------------------+------------------------------+
  | ``tag1 != tag2;``      | ``tag1.notEqual(tag2);``     |
  +------------------------+------------------------------+
  | ``tag1 < tag1;``       | ``tag1.less(tag2);``         |
  +------------------------+------------------------------+
  | ``tag1 > tag2;``       | ``tag1.greater(tag2);``      |
  +------------------------+------------------------------+
  | ``tag1 <= tag2;``      | ``tag1.lessEqual(tag2);``    |
  +------------------------+------------------------------+
  | ``tag1 >= tag2;``      | ``tag1.greaterEqual(tag2);`` |
  +------------------------+------------------------------+
  | ``std::string(tag1);`` | ``tag1.toString;``           |
  +------------------------+------------------------------+

The registry of elements is looked up using the ``getTag`` function:

::
  
  var tag = odil.getTag("PatientName");
  console.log(tag.get_name());

Value representations (VR)
--------------------------

The members of the `VR`_ enum are exposed as individual variables, with an additional ``VRtoString`` function to convert them to their name.

::
  
  var vr = odil.PN;
  console.log(odil.VRtoString(vr));

Data sets
---------

Data sets can be read from an `ArrayBuffer`_ object using the ``readBuffer`` function, which return an array comprised of the meta-information and the data set in a file. This can be used in conjunction with a `FileReader`_ to read a user-selected file as shown in the following example:

.. code-block:: html
  
  <!doctype html>
  <html>
  <head>
    <title>Odil web app</title>
  </head>
    
  <body>
    <label for="file">Select a DICOM file: </label>
    <input type="file" id="file" name="file"/><br>
    <script>
      function onFileRead(event) {
        var headerAndDataSet = odil.readBuffer(event.target.result);
      }
      
      function onFileSelect(event) {
        var reader = new FileReader();
        reader.addEventListener('loadend', onFileRead);
        reader.readAsArrayBuffer(event.target.files[0]);
      }
      
      function main() {
        window.odil = Module;
        document.querySelector('#file').addEventListener(
          'change', onFileSelect);
      }
      
      var Module = { onRuntimeInitialized: main };
    </script>
  </body>
  </html>

Accessing the element of the data set is done as in Python or C++:

::
  
  function onFileRead(event) {
    var headerAndDataSet = odil.readBuffer(event.target.result);
    var dataSet = headerAndDataSet.get(1);
    console.log(dataSet.as_string(odil.getTag("PatientName")).get(0));
  }

In addition to the ``as_XXX`` member functions, the following member functions are also exposed:

- ``is_XXX``
- ``remove``
- ``has``
- ``get_vr``
- ``get_transfer_syntax`` and ``set_transfer_syntax``

The equality and difference operators are exposed as ``equal`` and ``notEqual``, as for ``Tag`` objects. Some member functions in C++ and Python which may apply to either the whole data set or just an element (``empty``, ``size``, ``clear``) are exposed as to Javascript functions: ``empty`` will apply to the whole data set, while ``empty_tag`` will apply to a single element specified by its tag.

It is also possible to iterate the data sets, by iterating the tags of its elements:

::
  
  function onFileRead(event) {
    var headerAndDataSet = odil.readBuffer(event.target.result);
    var dataSet = headerAndDataSet.get(1);
    var tags = dataSet.get_tags();
    for(var i=0; i<tags.length; ++i) {
      console.log(tags[i].toString());
    }
  }

.. _ArrayBuffer: https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/ArrayBuffer
.. _FileReader: https://developer.mozilla.org/en-US/docs/Web/API/FileReader
.. _VR: ../../_static/doxygen/VR_8h.html
