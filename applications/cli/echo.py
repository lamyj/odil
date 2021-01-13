import argparse
import logging

import odil

def add_subparser(subparsers):
    parser = subparsers.add_parser(
        "echo", help="Ping a remote DICOM server (C-ECHO)",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument("host", help="Remote host address")
    parser.add_argument("port", type=int, help="Remote host port")
    parser.add_argument(
        "calling_ae_title", help="AE title of the calling application")
    parser.add_argument(
        "called_ae_title", help="AE title of the called application")
    parser.set_defaults(function=echo)
    return parser

def echo(host, port, calling_ae_title, called_ae_title):
    association = odil.Association()
    association.set_peer_host(host)
    association.set_peer_port(port)
    association.update_parameters()\
        .set_calling_ae_title(calling_ae_title)\
        .set_called_ae_title(called_ae_title) \
        .set_presentation_contexts([
            odil.AssociationParameters.PresentationContext(
                3, odil.registry.Verification,
                [ odil.registry.ImplicitVRLittleEndian ], True, False
            )
        ])
    association.associate()
    logging.info("Association established")

    echo = odil.EchoSCU(association)
    echo.echo()
    logging.info("C-ECHO successful")

    association.release()
    logging.info("Association released")
