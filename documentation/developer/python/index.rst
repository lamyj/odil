Python API
==========

.. highlight:: python

The Python API tries to mimic the :doc:`C++ API <../cpp/index>` as much as possible: most classes and other constructs keep the same name and semantics. However, when C++ and Python differ too much, new Python functions or classes are defined. 

Basic operations
----------------

The following example show basic manipulations of a data set. This code snippet, and all the others in this section assume that for Python 2, ``from __future__ import print_function`` was used. Note that the Python version of ``odil.DataSet`` adds a few member functions to the C++ version (e.g. ``items``, ``__len__``, ``__iter__``) to make it more similar to Python containers.

::
  
  import sys
  import odil

  # Reading a data set
  with odil.open(sys.argv[1]) as stream:
      header, data_set = odil.Reader.read_file(stream)

  # Data set size, using C++ API
  print(
      "The header {} empty and has {} elemens".format(
          "is" if header.empty() else "is not", header.size()))
  # Data set size, using Python API
  print(
      "The data set {} empty and has {} elements".format(
          "is" if not data_set else "is not", len(data_set)))

  # Element presence, C++ and Python API
  print("Patient's Name {} in header".format(
      "is" if header.has(odil.registry.PatientName) else "is not"))
  print("Patient's Name {} in data set".format(
      "is" if "PatientName" in data_set else "is not"))

  # Element access, assuming PatientName is in data set
  data_set.as_string("PatientName")[0] = "Somebody^Else"
  print("Patient's Name: {}".format(list(data_set.as_string("PatientName"))))

  # Iteration, sequence-like
  for tag in header:
      element = header[tag]
      print(tag.get_name(), element.vr)
  # Iteration, dict-like
  for tag, element in data_set.items():
      try:
          name = tag.get_name()
      except odil.Exception as e:
          name = str(tag)
      print(name, element.vr)

  # Writing a data set
  with odil.open(sys.argv[2], "w") as stream:
      odil.Writer.write_file(data_set, stream)

DICOM services -- client side
-----------------------------

The behavior of C++ SCUs w is kept as is in Python: services which return data sets (C-FIND, C-GET, C-MOVE) either return all data sets to the caller or call a function for each of them. The following example adapts the C++ examples for C-ECHO, C-FIND and C-GET in Python.

::
  
  import sys

  import odil

  transfer_syntaxes = [
      getattr(odil.registry, "{}VRLittleEndian".format(x))
      for x in ["Implicit", "Explicit"]]

  # Create the association
  association = odil.Association()
  association.set_peer_host("www.dicomserver.co.uk")
  association.set_peer_port(11112)
  association.update_parameters()\
      .set_calling_ae_title("WORKSTATION")\
      .set_called_ae_title("SERVER")\
      .set_presentation_contexts([
          odil.AssociationParameters.PresentationContext(
              odil.registry.Verification,
              transfer_syntaxes, True, False
          ),
          odil.AssociationParameters.PresentationContext(
              odil.registry.StudyRootQueryRetrieveInformationModelFind,
              transfer_syntaxes, True, False
          )
      ]) 
  association.associate()

  # Check DICOM connectivity
  echo_scu = odil.EchoSCU(association)
  try:
      echo_scu.echo()
  except odil.Exception as e:
      print("DICOM connection to remote server failed: {}".format(e))
      sys.exit(1)

  # Find the matching studies
  query = odil.DataSet()
  query.add("QueryRetrieveLevel", [ "STUDY" ])
  query.add("PatientName", ["Doe"])
  query.add("StudyInstanceUID")
  query.add("SOPClassesInStudy")

  find_scu = odil.FindSCU(association)
  find_scu.set_affected_sop_class(odil.registry.StudyRootQueryRetrieveInformationModelFind)
  study = find_scu.find(query)[0]

  # Fetch the first study
  association.release()
  association = odil.Association()
  association.set_peer_host("www.dicomserver.co.uk")
  association.set_peer_port(11112)
  association.update_parameters()\
      .set_calling_ae_title("WORKSTATION")\
      .set_called_ae_title("SERVER")\
      .set_presentation_contexts([
          odil.AssociationParameters.PresentationContext(
              odil.registry.StudyRootQueryRetrieveInformationModelGet,
              transfer_syntaxes, True, False
          )
      ]
      +[
          odil.AssociationParameters.PresentationContext(
              x, [odil.registry.ExplicitVRLittleEndian], True, False)
          for x in study.as_string("SOPClassesInStudy")
      ]) 
  association.associate()

  query = odil.DataSet()
  query.add("QueryRetrieveLevel", [ "STUDY" ])
  query.add("StudyInstanceUID", study.as_string("StudyInstanceUID"))
  query.add("SOPClassesInStudy")

  get_scu = odil.GetSCU(association)
  get_scu.set_affected_sop_class(odil.registry.StudyRootQueryRetrieveInformationModelGet)

  def data_set_received(data_set):
      print("Got data set {}".format(data_set.as_string("SOPInstanceUID")[0]))
  get_scu.get(query, data_set_received)


DICOM services -- server side
-----------------------------

Similar to C++ SCPs, the Python SCPs work with generators, inherited from their base classes (e.g. ``odil.FindSCP.DataSetGenerator``). The following example shows the implementation of a dummy C-FIND SCP.

::
  
  import odil

  # Create the association
  association = odil.Association()
  association.receive_association("v4", 11112)

  # Create the generator
  class Generator(odil.FindSCP.DataSetGenerator):
      def __init__(self):
          odil.FindSCP.DataSetGenerator.__init__(self)
          self._responses = []
          self._response_index = None
          
      def initialize(self, message):
          data_set = odil.DataSet()
          data_set.add("PatientName", ["Hello^World"])
          data_set.add("PatientID", ["1234"])
          self._responses.append(data_set)
          
          self._response_index = 0
      
      def done(self):
          return (self._response_index == len(self._responses))
      
      def next(self):
          self._response_index += 1
      
      def get(self):
          return self._responses[self._response_index]

  find_scp = odil.FindSCP(association)
  generator = Generator()
  find_scp.set_generator(generator)

  # Receive and handle a message
  message = association.receive_message()
  find_scp(message)

  # Check if we have more
  termination_ok = False
  try:
      association.receive_message()
  except odil.AssociationReleased:
      print("Association released")
  except odil.AssociationAborted:
      print("Association aborted")
