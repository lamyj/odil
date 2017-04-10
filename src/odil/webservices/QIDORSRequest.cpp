/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/


#include "odil/webservices/QIDORSRequest.h"

#include <boost/lexical_cast.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/qi.hpp>
#include <string>
#include <sstream>


#include "odil/webservices/ItemWithParameters.h"
#include "odil/VR.h"

namespace odil
{

namespace webservices
{

QIDORSRequest
::QIDORSRequest(const URL &base_url)
    : _base_url(base_url), _media_type(), _representation(Representation::DICOM_JSON),
      _url(), _selector(), _query_data_set(), _includefields(),
      _fuzzymatching(false), _limit(-1), _offset(0)
{
    // Nothing else
}

QIDORSRequest
::QIDORSRequest(HTTPRequest const & request)
{
    // Build tmp URL from target and "Host" header
    URL tmp_url = URL::parse(request.get_target());
    if(request.has_header("Host"))
    {
        this->_url.authority = request.get_header("Host");
    }

    // Find the media type.
    if(!request.has_header("Accept"))
    {
        throw Exception("Cannot parse request: Accept header missing");
    }
    auto const header_accept = boost::lexical_cast<ItemWithParameters>(
        request.get_header("Accept"));

    // if we have multipart/related, we will have then have application/dicom+xml
    // otherwise we will have application/dicom+json
    if(header_accept.name == "multipart/related")
    {
        auto const it = header_accept.name_parameters.find("type");
        // check if the type is not found
        if(it == header_accept.name_parameters.end())
        {
            std::ostringstream message;
            message
                << "Missing type in Accept header: "
                << request.get_header("Accept");
            throw Exception(message.str());
        }
        // check if type is different from the only available type
        if (it->second != "application/dicom+xml")
        {
            throw Exception("The only available type with multipart option is dicom+xml");
        }
        this->_media_type = it->second;
        this->_representation = Representation::DICOM_XML;
    }
    else
    {
        if (header_accept.name != "application/dicom+json")
        {
            throw Exception("The type cannot be different from dicom+json");
        }
        this->_media_type = header_accept.name;
        this->_representation = Representation::DICOM_JSON;
    }

    std::tie(this->_base_url, this->_url, this->_selector, this->_query_data_set, this->_includefields,
             this->_fuzzymatching, this->_limit, this->_offset) =
        QIDORSRequest::_split_full_url(tmp_url);
}

bool
QIDORSRequest
::operator ==(QIDORSRequest const & other) const
{
    return(
        this->_base_url == other._base_url
        && this->_media_type == other._media_type
        && this->_representation == other._representation
        && this->_url == other._url
        && this->_selector == other._selector
        && this->_query_data_set == other._query_data_set
        && this->_includefields == other._includefields
        && this->_fuzzymatching == other._fuzzymatching
        && this->_limit == other._limit
        && this->_offset == other._offset
    );
}

bool
QIDORSRequest
::operator !=(QIDORSRequest const & other) const
{
    return !(*this == other);
}

URL const &
QIDORSRequest
::get_base_url() const
{
    return this->_base_url;
}

void
QIDORSRequest
::set_base_url(const URL &url)
{
    this->_base_url = url;
}

std::string const &
QIDORSRequest
::get_media_type() const
{
    return this->_media_type;
}

Representation const &
QIDORSRequest
::get_representation() const
{
    return this->_representation;
}

URL const &
QIDORSRequest
::get_url() const
{
    return this->_url;
}

Selector const &
QIDORSRequest
::get_selector() const
{
    return this->_selector;
}

DataSet const &
QIDORSRequest
::get_query_data_set() const
{
    return this->_query_data_set;
}

std::set < std::vector < odil::Tag > > const &
QIDORSRequest
::get_includefields() const
{
    return this->_includefields;
}

bool
QIDORSRequest
::get_fuzzymatching() const
{
    return this->_fuzzymatching;
}

int
QIDORSRequest
::get_limit() const
{
    return this->_limit;
}

int
QIDORSRequest
::get_offset() const
{
    return this->_offset;
}

std::tuple<URL, URL, Selector, DataSet, std::set< std::vector <odil::Tag> >,
           bool /*fuzzymatching*/, int /*offset*/, int /*limit*/>
QIDORSRequest
::_split_full_url(const URL &url)
{
    Selector selector;
    URL base_url;

    typedef std::string::const_iterator Iterator;

    namespace qi = boost::spirit::qi;
    namespace p = boost::phoenix; // boost::phoenix::ref clashes with std::ref


    typedef std::vector <std::pair <std::string, std::string> >  KeyVal;


    auto const positions = {url.path.rfind("/instances"),
                            url.path.rfind("/series"),
                            url.path.rfind("/studies")};

    auto const position = std::min(positions);

    if(position != std::string::npos)
    {
        base_url = {
            url.scheme, url.authority, url.path.substr(0, position), "", "" };
        auto const resource = url.path.substr(position+1);


        using boost::spirit::qi::digit;
        using boost::spirit::qi::int_;
        using boost::spirit::qi::lit;
        using boost::spirit::qi::omit;
        using boost::spirit::qi::string;
        using boost::spirit::qi::_1;

        qi::rule<Iterator, std::string()> uid = digit >> *(string(".") >> +digit);

        qi::rule<Iterator, std::string()> selec =
                -string("studies")
                >> -string("series")
                >> -string("instances");

        qi::rule<Iterator, KeyVal()> retrieve_selector =
                (selec >> -(omit["/"] >> uid))% "/";

        KeyVal selector_vector;
        auto iterator = resource.begin();
        qi::phrase_parse(
            iterator, resource.end(),
            retrieve_selector,
            boost::spirit::qi::ascii::space, selector_vector
        );
        for (auto const it : selector_vector)
        {
            if(it.first == "studies")
            {
                selector.set_study(it.second);
            }
            else if(it.first == "series")
            {
                selector.set_series(it.second);
            }
            else if(it.first == "instances")
            {
                selector.set_instance(it.second);
            }
            else
            {
                throw Exception("Unrecognize option (" + it.first + ")");
            }
        }
    }

    if (!QIDORSRequest::_is_selector_valid(selector))
    {
        throw Exception("Selector not correctly constructed (" +
                        selector.get_path(false) + ")");
    }

    using boost::spirit::qi::char_;
    using boost::spirit::qi::omit;

    KeyVal key_val;

    // everything but = and &
    qi::rule<Iterator, std::string()> elem = +~char_("=&");

    qi::rule<Iterator, KeyVal()> retrieve_key_val =
            (elem  >> omit["="] >> elem) % "&";

    auto iterator = url.query.begin();
    qi::phrase_parse(
        iterator, url.query.end(),
            (
               retrieve_key_val
            ),
        boost::spirit::qi::ascii::space, key_val
    );

    bool fuzzy = false;
    int limit = -1, offset = 0;
    std::set< std::vector<odil::Tag> > includefields;
    bool include_all = true;
    odil::DataSet data_set;
    for (auto const pair : key_val)
    {
        if (pair.first == "fuzzymatching")
        {
            if (pair.second == "true")
            {
                fuzzy = true;
            }
            else if (pair.second == "false")
            {
                fuzzy = false;
            }
            else
            {
                throw Exception("Fuzzymatching is not a bool (" + pair.second + ")\n");
            }
        }
        else if (pair.first == "limit")
        {
            try
            {
                limit = boost::lexical_cast<int>(pair.second);
            }
            catch (boost::bad_lexical_cast& e)
            {
                std::cerr << "Limit value is not an integer (" << pair.second << ")\n";
            }
        }
        else if (pair.first == "offset")
        {
            try
            {
                offset = boost::lexical_cast<int>(pair.second);
            }
            catch (boost::bad_lexical_cast& e)
            {
                std::cerr << "Offset value is not an integer (" << pair.second << ")\n";
            }
        }
        else
        {
            std::vector< std::string > dicom_tag_vec;
            qi::rule<Iterator, std::string()> dicom_tags = +~char_("."); // simplified
            qi::rule<Iterator, std::vector<std::string>() > retrieve_attribute_id =
                    (dicom_tags) % ".";
            if (pair.first == "includefield")
            {
                if (pair.second == "all")
                {
                    include_all = true;
                }
                else
                {
                    // retrive AttributeId
                    qi::phrase_parse(
                        pair.second.begin(), pair.second.end(),
                                retrieve_attribute_id,
                        boost::spirit::qi::ascii::space, dicom_tag_vec
                    );
                    std::vector<odil::Tag> current_dicom_tags;
                    // retrieve corresponding dicomTag
                    for (auto const dicom_tag : dicom_tag_vec)
                    {
                        current_dicom_tags.push_back(odil::Tag(dicom_tag));
                    }
                    if (!current_dicom_tags.empty())
                    {
                        includefields.insert(current_dicom_tags);
                        include_all = false;
                    }
                }
            }
            else
            {// {AttributeID} = {value}
                // retrive AttributeId
                qi::phrase_parse(
                    pair.first.begin(), pair.first.end(),
                            retrieve_attribute_id,
                    boost::spirit::qi::ascii::space, dicom_tag_vec
                );
                DataSet* top_seq = &data_set;
                Tag current_tag;
                size_t dicom_tag_vec_size = dicom_tag_vec.size();
                for (int i = 0; i < dicom_tag_vec_size; ++i)
                {
                    current_tag = odil::Tag(dicom_tag_vec[i]);

                    if (i < dicom_tag_vec_size - 1)
                    {
                        top_seq->add(current_tag, {odil::DataSet()}, VR::SQ);
                        top_seq = &top_seq->as_data_set(current_tag)[0];
                    }
                    else
                    {
                        VR current_vr;
                        try
                        {
                            current_vr = odil::as_vr(current_tag);
                        }
                        catch (Exception const &)
                        {
                            current_vr = VR::UN;
                        }
                        if (is_int(current_vr))
                        {
                            try
                            {
                                top_seq->add(current_tag, {boost::lexical_cast<int>(pair.second)});
                            }
                            catch (boost::bad_lexical_cast& e)
                            {
                                throw Exception(current_tag.get_name() + "Should be an integer (" + pair.second + ")");
                            }
                        }
                        else if (is_real(current_vr))
                        {
                            try
                            {
                                top_seq->add(current_tag, {boost::lexical_cast<double>(pair.second)});
                            }
                            catch (boost::bad_lexical_cast& e)
                            {
                                throw Exception(current_tag.get_name() + "Should be a real (" + pair.second + ")");
                            }
                        }
                        else if (is_string(current_vr))
                        {
                            top_seq->add(current_tag, {pair.second});
                        }
                        else
                        {
                            throw Exception("unrecognize VR for " + _tag_to_string(current_tag, true));
                        }
                    }
                }
            }
        }
    }

    if (include_all)
    {
        includefields.clear();
    }

    URL full_url = QIDORSRequest::_generate_url(base_url, selector, data_set,
                                           includefields, fuzzy,
                                           limit, offset, false);

    return std::make_tuple(base_url, full_url, selector, data_set, includefields,
                           fuzzy, limit, offset
                           );
}


HTTPRequest
QIDORSRequest
::get_http_request() const
{
    ItemWithParameters accept;
    if (this->_representation == Representation::DICOM_JSON)
    {
        accept.name = "application/dicom+json";
    }
    else
    {
        accept.name = "multipart/related";
        accept.name_parameters["type"] = "application/dicom+xml";
    }

    HTTPRequest::Headers const headers{
        {"Accept", boost::lexical_cast<std::string>(accept) }
    };

    return HTTPRequest("GET", this->_url, "HTTP/1.0", headers);
}

bool
QIDORSRequest
::_is_selector_valid(Selector const & selector)
{
    bool valid = false;

    if (selector.is_study_present())
    {
        valid = true;
    }
    else if (!selector.is_study_present() || !selector.get_study().empty())
    {
        if (selector.is_series_present())
        {
            valid = true;
        }
        else if (!selector.is_series_present() || !selector.get_series().empty())
        {
            if (selector.is_instance_present())
            {
                valid = true;
            }
            else if (!selector.is_study_present() &&
                     !selector.is_series_present() &&
                     !selector.is_instance_present())
            {
                valid = false;
            }
        }
        else
        {
            valid = false;
        }
    }
    else
    {
        valid = false;
    }

    if (!selector.get_frames().empty())
    {
        if (!selector.get_instance().empty() && selector.is_instance_present())
        {
            valid = true;
        }
        else
        {
            valid = false;
        }
    }

    return valid;
}

std::string
QIDORSRequest
::_tag_to_string(Tag const & tag, bool numerical_tag)
{
    if(numerical_tag)
    {
        return std::string(tag);
    }
    else
    {
        try
        {
            return tag.get_name();
        }
        catch (Exception const &)
        {
            return std::string(tag);
        }
    }
}

URL
QIDORSRequest
::_generate_url(URL const & base_url, Selector const & selector, DataSet const & query_data_set,
                std::set< std::vector < odil::Tag > > const & includefields,
                bool fuzzymatching, int limit, int offset, bool numerical_tags)
{
    auto path = base_url.path + selector.get_path(false);
    std::stringstream ss_query;

    // ----- QUERY (DATASET ELEMENTS)

    int query_element_count  = 0, query_nb_elements = query_data_set.size(); // use to add the "&" char between query elements
    odil::Tag const * current_tag;
    odil::Element const * current_element;
    odil::DataSet const * current_ds;
    for (auto const & tag_elem : query_data_set)
    {
        current_tag = &tag_elem.first;
        current_element = &tag_elem.second;

        ss_query << QIDORSRequest::_tag_to_string(*current_tag, numerical_tags) ;

        while (current_element->is_data_set())
        {
            if (current_element->size() > 1)
            {
                throw Exception("Query doesn't allow the use of multidimensional element ("+
                                QIDORSRequest::_tag_to_string(*current_tag, numerical_tags) +")");
            }
            current_ds = &current_element->as_data_set()[0];
            current_tag = &current_ds->begin()->first;
            current_element = &current_ds->begin()->second;
            ss_query << "." << QIDORSRequest::_tag_to_string(*current_tag, numerical_tags)  ;
        }

        if (current_element->size() > 1)
        {
            throw Exception("Query doesn't allow the use of multidimensional element ("+
                            QIDORSRequest::_tag_to_string(*current_tag, numerical_tags) +")");
        }

        // here we get the "final" element
        if (current_element->is_int())
        {
            ss_query << "=" << boost::lexical_cast<std::string>(current_element->as_int()[0]);
        }
        else if (current_element->is_real())
        {
            ss_query << "=" << boost::lexical_cast<std::string>(current_element->as_real()[0]);
        }
        else if (current_element->is_string())
        {
            ss_query << "=" << current_element->as_string()[0];
        }
        else
        {
            throw Exception("Invalid query tag (" +
                            QIDORSRequest::_tag_to_string(*current_tag, numerical_tags) +")");
        }
        if (query_element_count++ < query_nb_elements - 1)
        {
            ss_query << "&" ;
        }
    }

    // ----- INCLUDEFIELD

    query_element_count = 0;
    query_nb_elements = includefields.size();
    int field_count = 0, field_nb_elements = 0;

    ss_query << "&includefield=";
    if (query_nb_elements == 0)
    {
        ss_query << "all";
    }
    else
    {
        for (auto const & includefield : includefields)
        {
            field_nb_elements = includefield.size();
            field_count = 0;
            for(auto const & fields : includefield)
            {
                ss_query << QIDORSRequest::_tag_to_string(fields, numerical_tags) ;
                if(field_count++ < field_nb_elements -1)
                {
                    ss_query << ".";
                }
            }
            if (query_element_count++ < query_nb_elements -1)
            {
                ss_query << "&includefield=";
            }
        }
    }


    // ----- FUZZYMATCHING

    ss_query << "&fuzzymatching=";
    if(fuzzymatching)
    {
        ss_query << "true";
    }
    else
    {
        ss_query << "false";
    }


    // ----- LIMIT & OFFSET

    if (limit != -1)
    {
        ss_query << "&limit=" << limit;
        if (offset != 0)
        {
            ss_query << "&offset=" << offset;
        }
    }

    std::string query = ss_query.str();

    return {
        base_url.scheme, base_url.authority, path, query, ""
    };
}

void
QIDORSRequest
::request_datasets(
    Representation representation, Selector const & selector,
    DataSet const & query_data_set,
    std::set< std::vector < odil::Tag > > const & includefields,
    bool fuzzymatching, int limit, int offset, bool numerical_tags)
{
    if (representation != Representation::DICOM_JSON &&
            representation != Representation::DICOM_XML)
    {
        throw Exception("Given representation is not available for QIDO-RS");
    }
    this->_representation = representation;
    this->_selector = selector;
    this->_query_data_set = query_data_set;
    this->_includefields = includefields;
    this->_fuzzymatching = fuzzymatching;
    this->_limit = limit;
    this->_offset = offset;

    if (!QIDORSRequest::_is_selector_valid(selector))
    {
        throw Exception("Selector not correctly constructed (" +
                        selector.get_path(false) + ")");
    }

    this->_url = QIDORSRequest::_generate_url(this->_base_url, selector,
                                              query_data_set, includefields, fuzzymatching,
                                              limit, offset, numerical_tags);
}

}

}
