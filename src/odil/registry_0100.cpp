/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <map>
#include <string>
#include <tuple>

#include "odil/ElementsDictionary.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{

void update_0100(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0100, 0x0410), ElementsDictionaryEntry("SOP Instance Status", "SOPInstanceStatus",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0100, 0x0420), ElementsDictionaryEntry("SOP Authorization DateTime", "SOPAuthorizationDateTime",  "DT", "1"));
    public_dictionary.emplace(Tag(0x0100, 0x0424), ElementsDictionaryEntry("SOP Authorization Comment", "SOPAuthorizationComment",  "LT", "1"));
    public_dictionary.emplace(Tag(0x0100, 0x0426), ElementsDictionaryEntry("Authorization Equipment Certification Number", "AuthorizationEquipmentCertificationNumber",  "LO", "1"));

    public_tags.emplace("SOPInstanceStatus", Tag(0x0100, 0x0410));
    public_tags.emplace("SOPAuthorizationDateTime", Tag(0x0100, 0x0420));
    public_tags.emplace("SOPAuthorizationComment", Tag(0x0100, 0x0424));
    public_tags.emplace("AuthorizationEquipmentCertificationNumber", Tag(0x0100, 0x0426));
}

}

}