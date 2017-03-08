/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/write_ds.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// Helper functions
namespace 
{

/// @brief Remove the trailing zeros of the mantissa.
void clean(char * mantissa)
{
    char * it = mantissa + strlen(mantissa) - 1;
    while(*it == '0' && it > mantissa)
    {
        *it = '\0';
        --it;
    }
    
    if(*it == '.')
    {
        *it = '\0';
    }
}

/**
 * @brief Add 1 to the integer contained in (buffer[0], buffer[n]) (end included).
 * @return 1 if a carry was used, 0 otherwise.
 */
int add1(char * buffer, int n)
{
    if(n < 0)
    {
        return 1;
    }
    
    if(buffer[n] == '9')
    {
        buffer[n] = '0';
        return add1(buffer, n-1);
    }
    else
    {
        buffer[n] += 1;
    }
    return 0;
}

/**
 * @brief Round the integer contained in (buffer[0], buffer[n]) (end included)
 *        to the nearest factor of 10.
 * @return 1 if rounding was carried to next digit, 0 otherwise.
 */
int doround(char * buffer, unsigned int n)
{
    if(n >= strlen(buffer))
    {
        return 0;
    }
    
    char const c = buffer[n];
    buffer[n] = 0;
    if(c >= '5' && c <= '9')
    {
        return add1(buffer, n-1);
    }
    
    return 0;
}

int roundat(char * buffer, unsigned int i, int exponent) 
{
    if(doround(buffer, i) != 0) 
    {
        exponent += 1;
        switch(exponent) 
        {
            case -2:
                strcpy(buffer, ".01");
                break;
            case -1:
                strcpy(buffer, ".1");
                break;
            case 0:
                strcpy(buffer, "1.");
                break;
            case 1:
                strcpy(buffer, "10");
                break;
            case 2:
                strcpy(buffer, "100");
                break;
            default:
                sprintf(buffer, "1e%d", exponent);
        }
        return 1;
    }
    return 0;
}

}

namespace odil
{

void write_ds(double f, char * buffer, int size)
{
    // Negative number: add initial '-' to buffer and process as positive number
    if(f < 0)
    {
        f = -f;
        size -= 1;
        *buffer = '-';
        ++buffer;
    }
    
    
    char line[40];
    sprintf(line, "%1.16e", f);
    
    if(line[0] == '-')
    {
        // Happens in the case of -0, other negative numbers have been already
        // handled
        f = -f;
        size -= 1;
        *buffer = '-';
        ++buffer;
        sprintf(line, "%1.16e", f);
    }
    
    char * mantissa = line+1;
    *mantissa = line[0];
    
    auto const end_of_mantissa = strcspn(mantissa, "eE");
    mantissa[end_of_mantissa] = '\0';
    int const exponent = strtol(mantissa + end_of_mantissa + 1, NULL, 10);
    
    if((exponent >= size) || (exponent < -3))
    {
        char exponent_buffer[6];
        auto const exponent_length = sprintf(exponent_buffer, "e%d", exponent);
        
        auto const i = roundat(mantissa, size - 1 - exponent_length, exponent);
        if(i == 1)
        {
            strcpy(buffer, mantissa);
            return;
        }
        buffer[0] = mantissa[0];
        buffer[1] = '.';
        strncpy(buffer + i + 2, mantissa + 1, size - 2 - exponent_length);
        buffer[size-exponent_length] = 0;
        clean(buffer);
        strcat(buffer, exponent_buffer);
    }
    else if(exponent >= size - 2)
    {
        roundat(mantissa, exponent + 1, exponent);
        strcpy(buffer, mantissa);
    }
    else if(exponent >= 0)
    {
        auto const i = roundat(mantissa, size - 1, exponent);
        if(i == 1)
        {
            strcpy(buffer, mantissa);
            return;
        }
        strncpy(buffer, mantissa, exponent + 1);
        buffer[exponent + 1] = '.';
        strncpy(buffer + exponent + 2, mantissa + exponent + 1, size - exponent - 1);
        buffer[size] = 0;
        clean(buffer);
    }
    else
    {
        int const i = roundat(mantissa, size + 1 + exponent, exponent);
        if (i == 1)
        {
            strcpy(buffer, mantissa);
            return;
        }
        buffer[0] = '.';
        for(int j=0; j< -1 - exponent; j++)
        {
            buffer[j+1] = '0';
        }
        if((i == 1) && (exponent != -1))
        {
            buffer[-exponent] = '1';
            ++buffer;
        }
        strncpy(buffer - exponent, mantissa, size + 1 + exponent);
        buffer[size] = 0;
        clean(buffer);
    }
}

}
