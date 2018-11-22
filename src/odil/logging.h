/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _5382f5e0_e993_4966_9447_542844edb635
#define _5382f5e0_e993_4966_9447_542844edb635

#include <memory>
#include <ostream>
#include <sstream>
#include <string>

#include "odil/odil.h"

namespace odil
{

namespace logging
{

/// @brief Logging level, from finest to coarsest.
enum class ODIL_API Level
{
    trace, debug, info, warning, error, fatal,
    off,
};

class Formatter;

/// @brief Return the global log level.
Level get_level();

/// @brief Set the global log level (default to off).
void set_level(Level level);

/// @brief Log at trace level
std::shared_ptr<Formatter> trace();

/// @brief Log at debug level
std::shared_ptr<Formatter> debug();

/// @brief Log at info level
std::shared_ptr<Formatter> info();

/// @brief Log at warning level
std::shared_ptr<Formatter> warning();

/// @brief Log at error level
std::shared_ptr<Formatter> error();

/// @brief Log at fatal level
std::shared_ptr<Formatter> fatal();

/// @brief Macro version of the trace(), debug(), etc. functions.
#define ODIL_LOG(level) ::odil::logging::level()

/// @brief String representation of a logging level.
std::string ODIL_API as_string(Level level);

/// @brief Format a log message.
class ODIL_API Formatter
{
public:
    bool const active;
    std::shared_ptr<std::ostringstream> buffer;

    Formatter(std::ostream * stream, Level level, Level min_level);
    virtual ~Formatter();

private:
    std::ostream * _stream;
};

/// @brief Insert a value to a formatter.
template<typename T>
std::shared_ptr<Formatter>
operator<<(std::shared_ptr<Formatter> formatter, T && value)
{
    if(formatter->active)
    {
        (*formatter->buffer) << value;
    }
    return formatter;
}

/// @brief Core logger singleton.
class Logger
{
public:
    ~Logger() = default;

    static Logger & get();

    std::ostream * get_stream() const;
    Logger & set_stream(std::ostream * stream);

    Level get_level() const;
    Logger & set_level(Level level);

    std::shared_ptr<Formatter> log(Level level) const;

private:
    static std::unique_ptr<Logger> _instance;

    std::ostream * _stream;
    Level _level;

    Logger();

    Logger(Logger const &) = delete;
    Logger(Logger &&) = delete;
    Logger & operator=(Logger const &) = delete;
    Logger & operator=(Logger &&) = delete;
};

}

}

#endif // _5382f5e0_e993_4966_9447_542844edb635
