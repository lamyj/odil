/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <cassert>
#include <iostream> // TODO : remove me
#include "odil/webservices/Selector.h"

namespace odil
{

namespace webservices
{

Selector
::Selector(RequestPath const & selector_path, std::vector<int> const & frames):
    study_present(false), series_present(false), instance_present(false)
{
    if (selector_path.find("studies") != selector_path.end())
    {
        this->study_present = true;
        this->study = selector_path.at("studies");
    }
    if (selector_path.find("series") != selector_path.end())
    {
        this->series_present = true;
        this->series = selector_path.at("series");
    }
    if (selector_path.find("instances") != selector_path.end())
    {
        this->instance_present = true;
        this->instance = selector_path.at("instances");
    }
    if (!frames.empty())
    {
        this->frames = frames;
    }
}

bool
Selector
::operator==(Selector const & other) const
{
    return (
        this->study == other.study
        && this->series == other.series
        && this->instance == other.instance
        && this->frames == other.frames
    );
}

bool
Selector
::operator!=(Selector const & other) const
{
    return !(*this == other);
}

std::string
Selector
::get_path(bool include_frames) const
{
    std::string path;
    if(this->study_present)
    {
        path = "/studies/" + this->study;
    }
    if(this->series_present)
    {
        path += "/series/" + this->series;
    }
    if(this->instance_present)
    {
        path += "/instances/" + this->instance;
    }
    if(include_frames && !this->frames.empty())
    {
        path += "/frames/";

        auto const last = --this->frames.end();
        auto it = this->frames.begin();
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
