/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _fc7ce52d_b32d_43c4_87fc_465b674e6726
#define _fc7ce52d_b32d_43c4_87fc_465b674e6726

#include <ios>
#include <streambuf>
#include <string>

#include <boost/python.hpp>

namespace odil
{

namespace wrappers
{

namespace python
{

/// @brief streambuf wrapper around Python file-like objects.
class streambuf : public std::streambuf
{
public:
    streambuf(
        boost::python::object object, std::string::size_type buffer_size=4096);

    ~streambuf() =default;
    streambuf(streambuf const &) =delete;
    streambuf(streambuf &&) =default;
    streambuf & operator=(streambuf const &) =delete;
    streambuf & operator=(streambuf &&) =default;

protected:
    std::streambuf::pos_type
    seekoff(
        std::streambuf::off_type off, std::ios_base::seekdir dir,
        std::ios_base::openmode which = std::ios_base::in | std::ios_base::out);

    std::streambuf::pos_type
    seekpos(
        std::streambuf::pos_type pos,
        std::ios_base::openmode which = std::ios_base::in | std::ios_base::out);

    int underflow();

    int uflow();

    int overflow(int ch=std::char_traits<char>::eof());

private:
    boost::python::object _object;
    std::string::size_type _buffer_size;
    std::string _buffer;
    std::string::size_type _current;

    void _update_buffer();
};

class iostream: public std::iostream
{
public:
    iostream(boost::python::object file_like)
    : std::iostream(nullptr), _streambuf(file_like)
    {
        this->rdbuf(&this->_streambuf);
    }
private:
    streambuf _streambuf;
};

}

}

}

#endif // _fc7ce52d_b32d_43c4_87fc_465b674e6726
