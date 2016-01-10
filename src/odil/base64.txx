/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/base64.h"

#include <iostream>
#include <string>

#ifndef _90eec83b_0ab6_4669_8454_e5a7e0a11a26
#define _90eec83b_0ab6_4669_8454_e5a7e0a11a26

namespace odil
{

namespace base64
{

template<typename TInputIterator, typename TOutputIterator>
void encode(
    TInputIterator begin, TInputIterator end, TOutputIterator destination)
{
    auto iterator = begin;
    unsigned char carry=0;
    unsigned int position=0;
    while(iterator != end)
    {
        unsigned char const input = static_cast<unsigned char>(*iterator);

        unsigned char symbol_index;
        if(position%3 == 0)
        {
            symbol_index = input >> 2;
            carry = input & 3;

            *destination = symbols[symbol_index];
        }
        else if(position%3 == 1)
        {
            symbol_index = (carry << 4) + (input >> 4);
            carry = input & 15;

            *destination = symbols[symbol_index];
        }
        else // position%3 == 2
        {
            symbol_index = (carry << 2) + (input >> 6);
            carry = input & 63;

            *destination = symbols[symbol_index];
            ++destination;
            *destination = symbols[carry];
        }

        ++iterator;
        ++destination;
        ++position;
    }

    if(position%3 == 1)
    {
        *destination = symbols[carry<<4];
        ++destination;
        *destination = '=';
        ++destination;
        *destination = '=';
    }
    else if(position%3 == 2)
    {
        *destination = symbols[carry<<2];
        ++destination;
        *destination = '=';
    }
    // Otherwise (position%3 == 0), nothing to do.
}

template<typename TInputIterator, typename TOutputIterator>
void decode(
    TInputIterator begin, TInputIterator end, TOutputIterator destination)
{
    auto iterator = begin;
    unsigned char current=0;
    unsigned int position=0;

    while(iterator != end)
    {
        unsigned char input = static_cast<unsigned char>(*iterator);
        if(input != '=')
        {
            input = reversed_symbols[input];

            if(position%4 == 0)
            {
                current = input;
            }
            else if(position%4 == 1)
            {
                current = (current << 2) + (input >> 4);
                *destination = current;
                ++destination;
                current = input & 15;
            }
            else if(position%4 == 2)
            {
                current = (current << 4) + (input >> 2);
                *destination = current;
                ++destination;
                current = input & 3;
            }
            else // position%4 == 3
            {
                current = (current << 6) + input;
                *destination = current;
                ++destination;
            }
        }

        ++iterator;
        ++position;
    }
}

}

}

#endif // _90eec83b_0ab6_4669_8454_e5a7e0a11a26
