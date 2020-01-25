/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0400
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0400

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const MACIDNumber(0x0400, 0x0005);
Tag const MACCalculationTransferSyntaxUID(0x0400, 0x0010);
Tag const MACAlgorithm(0x0400, 0x0015);
Tag const DataElementsSigned(0x0400, 0x0020);
Tag const DigitalSignatureUID(0x0400, 0x0100);
Tag const DigitalSignatureDateTime(0x0400, 0x0105);
Tag const CertificateType(0x0400, 0x0110);
Tag const CertificateOfSigner(0x0400, 0x0115);
Tag const Signature(0x0400, 0x0120);
Tag const CertifiedTimestampType(0x0400, 0x0305);
Tag const CertifiedTimestamp(0x0400, 0x0310);
Tag const DigitalSignaturePurposeCodeSequence(0x0400, 0x0401);
Tag const ReferencedDigitalSignatureSequence(0x0400, 0x0402);
Tag const ReferencedSOPInstanceMACSequence(0x0400, 0x0403);
Tag const MAC(0x0400, 0x0404);
Tag const EncryptedAttributesSequence(0x0400, 0x0500);
Tag const EncryptedContentTransferSyntaxUID(0x0400, 0x0510);
Tag const EncryptedContent(0x0400, 0x0520);
Tag const ModifiedAttributesSequence(0x0400, 0x0550);
Tag const NonconformingModifiedAttributesSequence(0x0400, 0x0551);
Tag const NonconformingDataElementValue(0x0400, 0x0552);
Tag const OriginalAttributesSequence(0x0400, 0x0561);
Tag const AttributeModificationDateTime(0x0400, 0x0562);
Tag const ModifyingSystem(0x0400, 0x0563);
Tag const SourceOfPreviousValues(0x0400, 0x0564);
Tag const ReasonForTheAttributeModification(0x0400, 0x0565);
Tag const InstanceOriginStatus(0x0400, 0x0600);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0400