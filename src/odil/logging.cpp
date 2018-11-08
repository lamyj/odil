/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/logging.h"

#include <iomanip>
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <thread>

#include "odil/odil.h"

namespace odil
{

namespace logging
{

Formatter
::Formatter(std::ostream * stream, Level level, Level min_level)
: active(level >= min_level), buffer(new std::ostringstream), _stream(stream)
{
    if(this->active && this->_stream)
    {
        auto const now = std::time(nullptr);
        
        static char time_buffer[100];
        std::strftime(time_buffer, sizeof(time_buffer), "%F %T", std::localtime(&now));

        (*this->buffer)
            // WARNING: put_time is missing in g++ <= 4.9
            //<< std::put_time(std::localtime(&now), "%F %T") << " "
            << time_buffer << " "
            << as_string(level) << " " << std::this_thread::get_id() << ": ";
    }
}

Formatter
::~Formatter()
{
    if(this->active && this->_stream)
    {
        (*this->_stream) << this->buffer->str() << std::endl;
    }
}

void set_level(Level level)
{
    odil::logging::Logger::get().set_level(level);
}

std::shared_ptr<Formatter> trace() { return Logger::get().log(Level::trace); }
std::shared_ptr<Formatter> info() { return Logger::get().log(Level::info); }
std::shared_ptr<Formatter> debug() { return Logger::get().log(Level::debug); }
std::shared_ptr<Formatter> warning() { return Logger::get().log(Level::warning); }
std::shared_ptr<Formatter> error() { return Logger::get().log(Level::error); }
std::shared_ptr<Formatter> fatal() { return Logger::get().log(Level::fatal); }

std::string as_string(Level level)
{
    if(level == Level::trace) { return "TRACE"; }
    else if(level == Level::debug) { return "DEBUG"; }
    else if(level == Level::info) { return "INFO"; }
    else if(level == Level::warning) { return "WARNING"; }
    else if(level == Level::error) { return "ERROR"; }
    else if(level == Level::fatal) { return "FATAL"; }
    else
    {
        throw std::runtime_error("Unknown logging level");
    }
}

std::unique_ptr<Logger>
Logger
::_instance = nullptr;

Logger &
Logger
::get()
{
    if(!Logger::_instance)
    {
        Logger::_instance = std::unique_ptr<Logger>(new Logger());
    }
    return *Logger::_instance;
}

std::ostream *
Logger
::get_stream() const
{
    return this->_stream;
}

Logger &
Logger
::set_stream(std::ostream * stream)
{
    this->_stream = stream;
    return *this;
}

Logger
::Logger()
: _stream(&std::clog), _level(Level::error)
{
    // Nothing else
}

Level
Logger
::get_level() const
{
    return this->_level;
}

Logger &
Logger
::set_level(Level level)
{
    this->_level = level;
    return *this;
}

std::shared_ptr<Formatter>
Logger
::log(Level level) const
{
    return std::make_shared<Formatter>(this->_stream, level, this->_level);
}

}

}
