/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

#include "streambuf.h"

#include <algorithm>
#include <ios>
#include <streambuf>
#include <string>
#include <vector>

#include <boost/python.hpp>

#include "odil/Exception.h"

#if PY_MAJOR_VERSION >= 3
    #define FromStringAndSize(v, len) PyBytes_FromStringAndSize(v, len)
#else
    #define IS_PY2
    #define FromStringAndSize(v, len) PyString_FromStringAndSize(v, len)
#endif

namespace odil
{

namespace wrappers
{

namespace python
{

streambuf
::streambuf(boost::python::object object, std::string::size_type buffer_size)
: _object(object),
  _buffer_size(buffer_size), _buffer(), _current(std::string::npos)
{
    this->setg(nullptr, nullptr, nullptr);
    this->setp(nullptr, nullptr);
}

std::streambuf::pos_type
streambuf
::seekoff(
    std::streambuf::off_type off, std::ios_base::seekdir dir,
    std::ios_base::openmode which)
{
    std::streambuf::off_type adjusted_offset;
    if(dir == std::ios_base::cur)
    {
        // We need to adjust the offset since the position of the Python
        // file-like object is at the end of the buffer.
        std::streambuf::off_type const position_offset =
            this->_buffer.size()-this->_current;
        adjusted_offset = off-position_offset;
    }
    else
    {
        // Either beg or end, the semantics don't change
        adjusted_offset = off;
    }

    int whence;
    if(dir == std::ios::beg)
    {
        whence = 0;
    }
    else if(dir == std::ios::cur)
    {
        whence = 1;
    }
    else if(dir == std::ios::end)
    {
        whence = 2;
    }
    else
    {
        throw Exception("Invalid direction");
    }

    this->_object.attr("seek")(adjusted_offset, whence);
    this->_update_buffer();

    return (
        int(boost::python::extract<int>(this->_object.attr("tell")())
        - this->_buffer.size()));
}

std::streambuf::pos_type
streambuf
::seekpos(std::streambuf::pos_type pos, std::ios_base::openmode which)
{
    return this->seekoff(pos, std::ios_base::beg);
}

int
streambuf
::underflow()
{
    if(this->_current == std::string::npos)
    {
        this->_update_buffer();
    }

    if(this->_current == std::string::npos)
    {
        return std::char_traits<char>::eof();
    }
    else
    {
        auto const character = this->_buffer.at(this->_current);
        return std::char_traits<char>::to_int_type(character);
    }
}

int
streambuf
::uflow()
{
    auto const character = this->underflow();
    if(character != std::char_traits<char>::eof())
    {
        ++this->_current;
        if(this->_current >= this->_buffer.size())
        {
            this->_current = std::string::npos;
        }
    }
    return character;
}

int
streambuf
::overflow(int ch)
{
    if(ch != std::char_traits<char>::eof())
    {
        char const cast_ch(ch);
        boost::python::object bytes_ch = boost::python::object(
            boost::python::handle<>(FromStringAndSize(&cast_ch, 1)));
        this->_object.attr("write")(bytes_ch);
    }
    return ch;
}

void
streambuf
::_update_buffer()
{
    boost::python::object data = this->_object.attr("read")(this->_buffer_size);
    if(boost::python::len(data) == 0)
    {
        // EOF
        this->_current = std::string::npos;
    }
    else
    {
#if PY_MAJOR_VERSION == 3 && PY_MINOR_VERSION <= 2
        // Exception as seen in Debian Wheezy / Ubuntu Precise:
        // No registered converter was able to produce a C++ rvalue of type
        //   std::string from this Python object of type bytes
        std::vector<int> data_int =
            boost::python::extract<std::vector<int>>(data);
        this->_buffer.resize(data_int.size());
        std::copy(data_int.begin(), data_int.end(), this->_buffer.begin());
#else
        this->_buffer = boost::python::extract<std::string>(data);
#endif
        this->_current = 0;
    }
}

}

}

}

void wrap_iostream()
{
    using namespace boost::python;
    using namespace odil::wrappers::python;

    class_<iostream, boost::noncopyable>("iostream", init<object>());
}
