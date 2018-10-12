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

void update_0064(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0064, 0x0002), ElementsDictionaryEntry("Deformable Registration Sequence", "DeformableRegistrationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0064, 0x0003), ElementsDictionaryEntry("Source Frame of Reference UID", "SourceFrameOfReferenceUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0064, 0x0005), ElementsDictionaryEntry("Deformable Registration Grid Sequence", "DeformableRegistrationGridSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0064, 0x0007), ElementsDictionaryEntry("Grid Dimensions", "GridDimensions",  "UL", "3"));
    public_dictionary.emplace(Tag(0x0064, 0x0008), ElementsDictionaryEntry("Grid Resolution", "GridResolution",  "FD", "3"));
    public_dictionary.emplace(Tag(0x0064, 0x0009), ElementsDictionaryEntry("Vector Grid Data", "VectorGridData",  "OF", "1"));
    public_dictionary.emplace(Tag(0x0064, 0x000f), ElementsDictionaryEntry("Pre Deformation Matrix Registration Sequence", "PreDeformationMatrixRegistrationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0064, 0x0010), ElementsDictionaryEntry("Post Deformation Matrix Registration Sequence", "PostDeformationMatrixRegistrationSequence",  "SQ", "1"));

    public_tags.emplace("DeformableRegistrationSequence", Tag(0x0064, 0x0002));
    public_tags.emplace("SourceFrameOfReferenceUID", Tag(0x0064, 0x0003));
    public_tags.emplace("DeformableRegistrationGridSequence", Tag(0x0064, 0x0005));
    public_tags.emplace("GridDimensions", Tag(0x0064, 0x0007));
    public_tags.emplace("GridResolution", Tag(0x0064, 0x0008));
    public_tags.emplace("VectorGridData", Tag(0x0064, 0x0009));
    public_tags.emplace("PreDeformationMatrixRegistrationSequence", Tag(0x0064, 0x000f));
    public_tags.emplace("PostDeformationMatrixRegistrationSequence", Tag(0x0064, 0x0010));
}

}

}