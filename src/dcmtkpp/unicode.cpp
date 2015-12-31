/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/unicode.h"

#include <algorithm>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>

#include <unicode/errorcode.h>
#include <unicode/unistr.h>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/Value.h"

namespace dcmtkpp
{

std::map<std::string, std::string> const icu_encodings = {
    { "", "" },
    // Single-Byte Character Sets Without Code Extensions
    { "ISO_IR 100", "iso-ir-100" },
    { "ISO_IR 101", "iso-ir-101" },
    { "ISO_IR 109", "iso-ir-109" },
    { "ISO_IR 110", "iso-ir-110" },
    { "ISO_IR 144", "iso-ir-144" },
    { "ISO_IR 127", "iso-ir-127" },
    { "ISO_IR 126", "iso-ir-126" },
    { "ISO_IR 138", "iso-ir-138" },
    { "ISO_IR 148", "iso-ir-148" },
    { "ISO_IR 13", "Shift_JIS" }, // Since the 0x00 to 0x7f characters
    // match ASCII (i.e. Romaji) and the 0xa1 to 0xdf map to half-width
    // katakana of JIS X 0201. cf. https://en.wikipedia.org/wiki/Shift_JIS
    { "ISO_IR 166", "TIS-620" },

    // Single-Byte Character Sets with Code Extensions
    { "ISO 2022 IR 6", "" },
    { "ISO 2022 IR 100", "iso-ir-100" },
    { "ISO 2022 IR 101", "iso-ir-101" },
    { "ISO 2022 IR 109", "iso-ir-109" },
    { "ISO 2022 IR 110", "iso-ir-110" },
    { "ISO 2022 IR 144", "iso-ir-144" },
    { "ISO 2022 IR 127", "iso-ir-127" },
    { "ISO 2022 IR 126", "iso-ir-126" },
    { "ISO 2022 IR 138", "iso-ir-138" },
    { "ISO 2022 IR 148", "iso-ir-148" },
    { "ISO 2022 IR 13", "Shift_JIS" },
    { "ISO 2022 IR 166", "TIS-620" },

    { "\x1B\x28\x42", "" },
    { "\x1B\x2D\x41", "iso-ir-100" },
    { "\x1B\x2D\x42", "iso-ir-101" },
    { "\x1B\x2D\x43", "iso-ir-109" },
    { "\x1B\x2D\x44", "iso-ir-110" },
    { "\x1B\x2D\x4C", "iso-ir-144" },
    { "\x1B\x2D\x47", "iso-ir-127" },
    { "\x1B\x2D\x46", "iso-ir-126" },
    { "\x1B\x2D\x48", "iso-ir-138" },
    { "\x1B\x2D\x4D", "iso-ir-148" },
    { "\x1B\x29\x49", "ISO-2022-JP" },
    { "\x1B\x28\x4A", "ISO-2022-JP" },
    { "\x1B\x2D\x54", "TIS-620" },

    // Multi-Byte Character Sets with Code Extensions
    { "ISO 2022 IR 87", "ISO-2022-JP" },
    { "ISO 2022 IR 149", "EUC-KR" },
    { "ISO 2022 IR 58", "ISO-2022-CN" },

    { "\x1B\x24\x42", "ISO-2022-JP" },
    { "\x1B\x24\x28\x44", "ISO-2022-JP" },
    { "\x1B\x24\x29\x43", "iso-ir-149" },
    { "\x1B\x24\x29\x41", "iso-ir-58" },

    // Multi-Byte Character Sets Without Code Extensions
    { "ISO_IR 192", "UTF-8" },
    { "GB18030", "GB18030" },
    // GBK
};

std::map<std::string, std::vector<std::string>> const escape_sequences = {
    { "",   { "\x1B\x28\x42" } },
    { "ISO 2022 IR 6",   { "\x1B\x28\x42" } },
    { "ISO 2022 IR 100", { "\x1B\x2D\x41", "\x1B\x28\x42" } },
    { "ISO 2022 IR 101", { "\x1B\x2D\x42", "\x1B\x28\x42" } },
    { "ISO 2022 IR 109", { "\x1B\x2D\x43", "\x1B\x28\x42" } },
    { "ISO 2022 IR 110", { "\x1B\x2D\x44", "\x1B\x28\x42" } },
    { "ISO 2022 IR 144", { "\x1B\x2D\x4C", "\x1B\x28\x42" } },
    { "ISO 2022 IR 127", { "\x1B\x2D\x47", "\x1B\x28\x42" } },
    { "ISO 2022 IR 126", { "\x1B\x2D\x46", "\x1B\x28\x42" } },
    { "ISO 2022 IR 138", { "\x1B\x2D\x48", "\x1B\x28\x42" } },
    { "ISO 2022 IR 148", { "\x1B\x2D\x4D", "\x1B\x28\x42" } },
    { "ISO 2022 IR 13",  { "\x1B\x29\x49", "\x1B\x28\x4A" } },
    { "ISO 2022 IR 166", { "\x1B\x2D\x54", "\x1B\x28\x42" } },

    { "ISO 2022 IR 87",  { "\x1B\x24\x42", "\x1B\x28\x42" } },
    { "ISO 2022 IR 159", { "\x1B\x24\x28\x44" } },
    { "ISO 2022 IR 149", { "\x1B\x24\x29\x43" } },
    { "ISO 2022 IR 58",  { "\x1B\x24\x29\x41" } },
};

std::string find_encoder(std::string const & specific_character_set)
{
    std::string encoder;
    auto const it = icu_encodings.find(specific_character_set);
    if(it == icu_encodings.end())
    {
        throw Exception("Unknown encoding: "+specific_character_set);
    }
    encoder = it->second;

    return encoder;
}

std::string as_utf8(
    std::string::const_iterator const begin, std::string::const_iterator const end,
    std::string const & encoding)
{
    icu::UnicodeString unicode(&(*begin), end-begin, encoding.c_str());
    std::string result;
    unicode.toUTF8String(result);

    return result;
}

std::string as_utf8(
    std::string::const_iterator const begin, std::string::const_iterator const end,
    std::string const & initial_encoder,
    std::vector<std::string> const & active_escape_sequences)
{
    std::string encoded;

    auto encoder = initial_encoder;

    auto item_begin = begin;
    while(item_begin != end)
    {
        auto const item_end = std::find(item_begin+1, end, '\x1B');

        if(*item_begin == '\x1B')
        {
            std::string escape_sequence(item_begin, item_begin+3);

            // Find an encoder for the escape sequence
            if(
                std::find(
                active_escape_sequences.begin(), active_escape_sequences.end(),
                escape_sequence) != active_escape_sequences.end())
            {
                encoder = find_encoder(escape_sequence);
            }
            else
            {
                escape_sequence += *(item_begin+3);
                if(
                    std::find(
                    active_escape_sequences.begin(), active_escape_sequences.end(),
                    escape_sequence) != active_escape_sequences.end())
                {
                    encoder = find_encoder(escape_sequence);
                }
                else
                {
                    // Unknown escape sequence: do not update the encoder,
                    // hope for the best.
                }
            }

            if(encoder != "ISO-2022-JP")
            {
                // The ISO-2022-JP encoder of ICU must have the escape
                // sequences
                item_begin += escape_sequence.size();
            }
        }

        encoded += as_utf8(item_begin, item_end, encoder);

        item_begin = item_end;
    }

    return encoded;
}

enum class Group
{
    Alphabetic,
    Ideographic,
    Phonetic
};

std::vector<std::string> get_active_escape_sequences(
    Value::Strings const & specific_character_set, Group const & group)
{
    std::vector<std::string> active_escape_sequences;

    if(specific_character_set.size() >= 2)
    {
        auto const escape_sequences_it = escape_sequences.find(specific_character_set[1]);
        if(escape_sequences_it == escape_sequences.end())
        {
            throw Exception("Unknown specific character set: "+specific_character_set[1]);
        }
        std::copy(
            escape_sequences_it->second.begin(),
            escape_sequences_it->second.end(),
            std::back_inserter(active_escape_sequences));
    }
    if(group == Group::Phonetic)
    {
        auto const escape_sequences_it = escape_sequences.find(specific_character_set[0]);
        if(escape_sequences_it != escape_sequences.end())
        {
            std::copy(
                escape_sequences_it->second.begin(),
                escape_sequences_it->second.end(),
                std::back_inserter(active_escape_sequences));
        }
        if(specific_character_set.size() >= 3)
        {
            auto const escape_sequences_it = escape_sequences.find(specific_character_set[2]);
            if(escape_sequences_it == escape_sequences.end())
            {
                throw Exception("Unknown specific character set: "+specific_character_set[2]);
            }
            std::copy(
                escape_sequences_it->second.begin(),
                escape_sequences_it->second.end(),
                std::back_inserter(active_escape_sequences));
        }
    }

    return active_escape_sequences;
}

std::string as_utf8(
    std::string const & input, Value::Strings const & specific_character_set,
    bool is_pn)
{
    // Control characters: line feed, carriage return, form feed and tabulation
    // For Person Name, add the group splitters
    std::string splitters = "\n\r\f\t";
    if(is_pn)
    {
        if(
            std::find(
                specific_character_set.begin(), specific_character_set.end(),
                "ISO 2022 IR 13") != specific_character_set.end() ||
            std::find(
                specific_character_set.begin(), specific_character_set.end(),
                "ISO 2022 IR 87") != specific_character_set.end())
        {
            // The ISO-2022-JP encoder of ICU is stateful, whereas all other
            // ISO 2022 encoders seem to be only codepages (i.e. stateless)
            splitters.append("=");
        }
        else
        {
            splitters.append("^=");
        }
    }

    std::string result;

    Group group=Group::Alphabetic;

    auto begin = input.begin();
    while(begin != input.end())
    {
        // Active character set resets to default before any of the splitters
        // cf. PS 3.5, 6.1.2.5.3
        auto const end = std::find_first_of(
            begin, input.end(), splitters.begin(), splitters.end());

        std::string encoded;

        if(specific_character_set.empty())
        {
            encoded = std::string(begin, end);
        }
        else if(is_pn && group != Group::Alphabetic)
        {
            auto const initial_encoder = find_encoder(specific_character_set[0]);
            auto const active_escape_sequences =
                get_active_escape_sequences(specific_character_set, group);
            encoded = as_utf8(begin, end, initial_encoder, active_escape_sequences);
        }
        else
        {
            auto const encoder = find_encoder(specific_character_set[0]);
            encoded = as_utf8(begin, end, encoder);
        }

        result.append(encoded);

        // If present, add the splitter to the UTF-8 string.
        if(end != input.end())
        {
            result.push_back(*end);
            begin = end+1;
            if(is_pn && *end == '=')
            {
                if(group == Group::Alphabetic)
                {
                    group = Group::Ideographic;
                }
                else if(group == Group::Ideographic)
                {
                    group = Group::Phonetic;
                }
                else
                {
                    throw Exception("Too many groups");
                }
            }
        }
        else
        {
            begin = end;
        }
    }

    return result;
}

}
