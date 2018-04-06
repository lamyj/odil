/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/webservices/Selector.h"

#include <string>
#include <utility>
#include <vector>
#include <map>

#include <boost/fusion/include/std_pair.hpp>
#include <boost/spirit/include/qi.hpp>

#include "odil/Exception.h"
#include "odil/odil.h"

namespace odil
{

namespace webservices
{

Selector
::Selector(
    std::map<std::string, std::string> const & selector,
    std::vector<int> const & frames)
: _frames(frames),
  _study_present(false), _series_present(false), _instance_present(false)
{
    for(auto const & pair: selector)
    {
        if (pair.first == "studies")
        {
            this->_study_present = true;
            this->_study = pair.second;
        }
        else if (pair.first == "series")
        {
            this->_series_present = true;
            this->_series = pair.second;
        }
        else if (pair.first == "instances")
        {
            this->_instance_present = true;
            this->_instance = pair.second;
        }
        else
        {
            throw Exception("Unknown option " + pair.first);
        }
    }
}

template <typename Iterator>
struct Grammar:
    boost::spirit::qi::grammar<
        Iterator,
        std::pair<std::map<std::string, std::string>, std::vector<int>>()>
{
    Grammar()
    : Grammar::base_type(selector)
    {
        namespace qi = boost::spirit::qi;

        level %=
            qi::string("studies") | qi::string("series") | qi::string("instances");
        value %= +(~qi::char_("/"));
        objects %= (level >> -(qi::omit["/"] >> value)) % "/";
        frames %= qi::lit("/frames/") >> qi::int_ % ",";
        selector %= objects >> -frames;
    }

    boost::spirit::qi::rule<Iterator, std::string()> level;
    boost::spirit::qi::rule<Iterator, std::string()> value;
    boost::spirit::qi::rule<
            Iterator, std::map<std::string, std::string>()
        > objects;
    boost::spirit::qi::rule<Iterator, std::vector<int>()> frames;
    boost::spirit::qi::rule<
            Iterator,
            std::pair<std::map<std::string, std::string>, std::vector<int>>()
        > selector;
};

std::pair<std::string, Selector>
Selector
::from_path(std::string const & path)
{
    auto const positions = {
        path.rfind("/instances"), path.rfind("/series"), path.rfind("/studies")
    };
    auto const position = std::min(positions);

    auto const service = path.substr(0, position);
    auto const resource = path.substr(position+1);

    Grammar<std::string::const_iterator> grammar;
    std::pair<std::map<std::string, std::string>, std::vector<int>> parsed_value;
    auto iterator = resource.begin();
    auto const is_parsed = boost::spirit::qi::phrase_parse(
        iterator, resource.end(), grammar,
        boost::spirit::qi::ascii::space, parsed_value);
    if(!is_parsed)
    {
        throw Exception("Could not parse path");
    }
    else if(iterator != resource.end())
    {
        throw Exception("Path was only partially parsed");
    }
    return std::make_pair(
        std::move(service), Selector(parsed_value.first, parsed_value.second));
}

bool
Selector
::operator==(Selector const & other) const
{
    return (
        this->_study == other._study
        && this->_study_present == other._study_present
        && this->_series == other._series
        && this->_series_present == other._series_present
        && this->_instance == other._instance
        && this->_instance_present == other._instance_present
        && this->_frames == other._frames
    );
}

bool
Selector
::operator!=(Selector const & other) const
{
    return !(*this == other);
}

bool
Selector
::is_study_present() const
{
    return this->_study_present;
}

bool
Selector
::is_series_present() const
{
    return this->_series_present;
}

bool
Selector
::is_instance_present() const
{
    return this->_instance_present;
}

std::string const &
Selector
::get_study() const
{
    return this->_study;
}

std::string const &
Selector
::get_series() const
{
    return this->_series;
}

std::string const &
Selector
::get_instance() const
{
    return this->_instance;
}

std::vector<int> const &
Selector
::get_frames() const
{
    return this->_frames;
}

Selector &
Selector
::set_study(std::string const & study)
{
    this->_study = study;
    this->_study_present = true;
    return *this;
}

Selector &
Selector
::set_series(std::string const & series)
{
    this->_series = series;
    this->_series_present = true;
    return *this;
}

Selector &
Selector
::set_instance(std::string const & instance)
{
    this->_instance = instance;
    this->_instance_present = true;
    return *this;
}

Selector &
Selector
::set_frames(std::vector<int> const &frames)
{
    this->_frames = frames;
    return *this;
}

std::string
Selector
::get_path(bool include_frames) const
{
    std::string path;
    if(this->_study_present)
    {
        path = "/studies";
        if (!this->_study.empty())
        {
            path += "/" + this->_study;
        }
    }
    if(this->_series_present)
    {
        path += "/series";
        if(!this->_series.empty())
        {
            path += "/" + this->_series;
        }
    }
    if(this->_instance_present)
    {
        path += "/instances";
        if (!this->_instance.empty())
        {
            path += "/" + this->_instance;
        }
    }
    if(include_frames && !this->_frames.empty())
    {
        path += "/frames/";
        auto const last = --this->_frames.end();
        auto it = this->_frames.begin();
        while(it != last)
        {
            path += std::to_string(*it) + ",";
            ++it;
        }
        path += std::to_string(*last);
    }
    return path;
}

}

}
