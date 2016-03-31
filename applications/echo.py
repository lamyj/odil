import logging

import _odil

def add_subparser(subparsers):
    parser = subparsers.add_parser(
        "echo", help="Ping a remote DICOM server (C-ECHO)")
    parser.add_argument("host", help="Remote host address")
    parser.add_argument("port", type=int, help="Remote host port")
    parser.add_argument(
        "calling_ae_title", help="AE title of the calling application")
    parser.add_argument(
        "called_ae_title", help="AE title of the called application")
    parser.set_defaults(function=echo)
    return parser

def echo(host, port, calling_ae_title, called_ae_title):
    association = _odil.Association()
    association.set_peer_host(host)
    association.set_peer_port(port)
    association.update_parameters()\
        .set_calling_ae_title(calling_ae_title)\
        .set_called_ae_title(called_ae_title) \
        .set_presentation_contexts([
            _odil.AssociationParameters.PresentationContext(
                3, _odil.registry.VerificationSOPClass,
                [ _odil.registry.ImplicitVRLittleEndian ], True, False
            )
        ])
    association.associate()
    logging.info("Association established")

    echo = _odil.EchoSCU(association)
    echo.echo()
    logging.info("C-ECHO successful")

    association.release()
    logging.info("Association released")
