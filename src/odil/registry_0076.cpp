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

void update_0076(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0076, 0x0001), ElementsDictionaryEntry("Implant Assembly Template Name", "ImplantAssemblyTemplateName",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0076, 0x0003), ElementsDictionaryEntry("Implant Assembly Template Issuer", "ImplantAssemblyTemplateIssuer",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0076, 0x0006), ElementsDictionaryEntry("Implant Assembly Template Version", "ImplantAssemblyTemplateVersion",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0076, 0x0008), ElementsDictionaryEntry("Replaced Implant Assembly Template Sequence", "ReplacedImplantAssemblyTemplateSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0076, 0x000a), ElementsDictionaryEntry("Implant Assembly Template Type", "ImplantAssemblyTemplateType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0076, 0x000c), ElementsDictionaryEntry("Original Implant Assembly Template Sequence", "OriginalImplantAssemblyTemplateSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0076, 0x000e), ElementsDictionaryEntry("Derivation Implant Assembly Template Sequence", "DerivationImplantAssemblyTemplateSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0076, 0x0010), ElementsDictionaryEntry("Implant Assembly Template Target Anatomy Sequence", "ImplantAssemblyTemplateTargetAnatomySequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0076, 0x0020), ElementsDictionaryEntry("Procedure Type Code Sequence", "ProcedureTypeCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0076, 0x0030), ElementsDictionaryEntry("Surgical Technique", "SurgicalTechnique",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0076, 0x0032), ElementsDictionaryEntry("Component Types Sequence", "ComponentTypesSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0076, 0x0034), ElementsDictionaryEntry("Component Type Code Sequence", "ComponentTypeCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0076, 0x0036), ElementsDictionaryEntry("Exclusive Component Type", "ExclusiveComponentType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0076, 0x0038), ElementsDictionaryEntry("Mandatory Component Type", "MandatoryComponentType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0076, 0x0040), ElementsDictionaryEntry("Component Sequence", "ComponentSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0076, 0x0055), ElementsDictionaryEntry("Component ID", "ComponentID",  "US", "1"));
    public_dictionary.emplace(Tag(0x0076, 0x0060), ElementsDictionaryEntry("Component Assembly Sequence", "ComponentAssemblySequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0076, 0x0070), ElementsDictionaryEntry("Component 1 Referenced ID", "Component1ReferencedID",  "US", "1"));
    public_dictionary.emplace(Tag(0x0076, 0x0080), ElementsDictionaryEntry("Component 1 Referenced Mating Feature Set ID", "Component1ReferencedMatingFeatureSetID",  "US", "1"));
    public_dictionary.emplace(Tag(0x0076, 0x0090), ElementsDictionaryEntry("Component 1 Referenced Mating Feature ID", "Component1ReferencedMatingFeatureID",  "US", "1"));
    public_dictionary.emplace(Tag(0x0076, 0x00a0), ElementsDictionaryEntry("Component 2 Referenced ID", "Component2ReferencedID",  "US", "1"));
    public_dictionary.emplace(Tag(0x0076, 0x00b0), ElementsDictionaryEntry("Component 2 Referenced Mating Feature Set ID", "Component2ReferencedMatingFeatureSetID",  "US", "1"));
    public_dictionary.emplace(Tag(0x0076, 0x00c0), ElementsDictionaryEntry("Component 2 Referenced Mating Feature ID", "Component2ReferencedMatingFeatureID",  "US", "1"));

    public_tags.emplace("ImplantAssemblyTemplateName", Tag(0x0076, 0x0001));
    public_tags.emplace("ImplantAssemblyTemplateIssuer", Tag(0x0076, 0x0003));
    public_tags.emplace("ImplantAssemblyTemplateVersion", Tag(0x0076, 0x0006));
    public_tags.emplace("ReplacedImplantAssemblyTemplateSequence", Tag(0x0076, 0x0008));
    public_tags.emplace("ImplantAssemblyTemplateType", Tag(0x0076, 0x000a));
    public_tags.emplace("OriginalImplantAssemblyTemplateSequence", Tag(0x0076, 0x000c));
    public_tags.emplace("DerivationImplantAssemblyTemplateSequence", Tag(0x0076, 0x000e));
    public_tags.emplace("ImplantAssemblyTemplateTargetAnatomySequence", Tag(0x0076, 0x0010));
    public_tags.emplace("ProcedureTypeCodeSequence", Tag(0x0076, 0x0020));
    public_tags.emplace("SurgicalTechnique", Tag(0x0076, 0x0030));
    public_tags.emplace("ComponentTypesSequence", Tag(0x0076, 0x0032));
    public_tags.emplace("ComponentTypeCodeSequence", Tag(0x0076, 0x0034));
    public_tags.emplace("ExclusiveComponentType", Tag(0x0076, 0x0036));
    public_tags.emplace("MandatoryComponentType", Tag(0x0076, 0x0038));
    public_tags.emplace("ComponentSequence", Tag(0x0076, 0x0040));
    public_tags.emplace("ComponentID", Tag(0x0076, 0x0055));
    public_tags.emplace("ComponentAssemblySequence", Tag(0x0076, 0x0060));
    public_tags.emplace("Component1ReferencedID", Tag(0x0076, 0x0070));
    public_tags.emplace("Component1ReferencedMatingFeatureSetID", Tag(0x0076, 0x0080));
    public_tags.emplace("Component1ReferencedMatingFeatureID", Tag(0x0076, 0x0090));
    public_tags.emplace("Component2ReferencedID", Tag(0x0076, 0x00a0));
    public_tags.emplace("Component2ReferencedMatingFeatureSetID", Tag(0x0076, 0x00b0));
    public_tags.emplace("Component2ReferencedMatingFeatureID", Tag(0x0076, 0x00c0));
}

}

}