/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/webservices/Selector.h"

namespace odil
{

namespace webservices
{

Selector
::Selector(
    std::string const & study, std::string const & series,
    std::string const & instance, std::vector<int> const & frames)
{
    if(!study.empty())
    {
        this->study = study;
        if(!series.empty())
        {
            this->series = series;
            if(!instance.empty())
            {
                this->instance = instance;
                if(!frames.empty())
                {
                    this->frames = frames;
                }
            }
        }
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
    if(this->study.empty())
    {
        throw Exception("Study may not be empty");
    }

    std::string path = "/studies/" + this->study;
    if(!this->series.empty())
    {
        path += "/series/" + this->series;
        if(!this->instance.empty())
        {
            path += "/instances/" + this->instance;
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

        }
    }

    return path;
}

}

}
