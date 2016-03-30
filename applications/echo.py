import logging

import _odil

def add_subparser(subparsers):
    parser = subparsers.add_parser(
        "echo", help="Ping a remote DICOM server (C-ECHO")
    parser.add_argument("host")
    parser.add_argument("port", type=int)
    parser.add_argument("calling_ae_title")
    parser.add_argument("called_ae_title")
    parser.set_defaults(function=echo)

def echo(host, port, calling_ae_title, called_ae_title):
    verification = _odil.AssociationParameters.PresentationContext(
        3, _odil.registry.VerificationSOPClass,
        [ _odil.registry.ImplicitVRLittleEndian ], True, False
    )
    contexts = _odil.AssociationParameters.VPresentationContext()
    contexts.append(verification)

    association = _odil.Association()
    association.set_peer_host(host)
    association.set_peer_port(port)
    association.update_parameters()\
        .set_calling_ae_title(calling_ae_title)\
        .set_called_ae_title(called_ae_title) \
        .set_presentation_contexts(contexts)
    association.associate()
    logging.info("Association established")

    echo = _odil.EchoSCU(association)
    echo.echo()
    logging.info("C-ECHO successful")

    association.release()
    logging.info("Association released")
