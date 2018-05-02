/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0004
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0004

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const FileSetID(0x0004, 0x1130);
Tag const FileSetDescriptorFileID(0x0004, 0x1141);
Tag const SpecificCharacterSetOfFileSetDescriptorFile(0x0004, 0x1142);
Tag const OffsetOfTheFirstDirectoryRecordOfTheRootDirectoryEntity(0x0004, 0x1200);
Tag const OffsetOfTheLastDirectoryRecordOfTheRootDirectoryEntity(0x0004, 0x1202);
Tag const FileSetConsistencyFlag(0x0004, 0x1212);
Tag const DirectoryRecordSequence(0x0004, 0x1220);
Tag const OffsetOfTheNextDirectoryRecord(0x0004, 0x1400);
Tag const RecordInUseFlag(0x0004, 0x1410);
Tag const OffsetOfReferencedLowerLevelDirectoryEntity(0x0004, 0x1420);
Tag const DirectoryRecordType(0x0004, 0x1430);
Tag const PrivateRecordUID(0x0004, 0x1432);
Tag const ReferencedFileID(0x0004, 0x1500);
Tag const MRDRDirectoryRecordOffset(0x0004, 0x1504);
Tag const ReferencedSOPClassUIDInFile(0x0004, 0x1510);
Tag const ReferencedSOPInstanceUIDInFile(0x0004, 0x1511);
Tag const ReferencedTransferSyntaxUIDInFile(0x0004, 0x1512);
Tag const ReferencedRelatedGeneralSOPClassUIDInFile(0x0004, 0x151a);
Tag const NumberOfReferences(0x0004, 0x1600);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0004