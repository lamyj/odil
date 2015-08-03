/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _f4b88e07_d515_41be_ad1b_37899ec6451e
#define _f4b88e07_d515_41be_ad1b_37899ec6451e

#include <map>
#include <string>

#include <dcmtkpp/Tag.h>

namespace dcmtkpp
{

/**
 * @brief Entry in a dictionary of DICOM elements.
 */
struct ElementsDictionaryEntry
{
    std::string name;
    std::string keyword;
    std::string vr;
    std::string vm;

    ElementsDictionaryEntry(
        std::string const & name, std::string const & keyword,
        std::string const & vr, std::string const & vm);
};

typedef std::map<Tag, ElementsDictionaryEntry> ElementsDictionary;

}

#endif // _f4b88e07_d515_41be_ad1b_37899ec6451e
