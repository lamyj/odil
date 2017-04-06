/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _1cd2d27d_2d97_405b_b9d5_4104210e543a
#define _1cd2d27d_2d97_405b_b9d5_4104210e543a

#include <string>
#include <tuple>

#include "odil/DataSet.h"
#include "odil/odil.h"
#include "odil/Tag.h"
#include "odil/webservices/HTTPRequest.h"
#include "odil/webservices/Utils.h"
#include "odil/webservices/Selector.h"
#include "odil/webservices/URL.h"

namespace odil
{

namespace webservices
{


/// @brief QIDO-RS request generator and parser
class ODIL_API QIDORSRequest
{
public:
    /// @brief Constructor.
    QIDORSRequest(URL const & base_url);

    /// @brief Constructor.
    QIDORSRequest(HTTPRequest const & request);

    /// @brief Destructor.
    ~QIDORSRequest() = default;

    /// @brief Equality operator.
    bool operator==(QIDORSRequest const & other) const;

    /// @brief Difference operator.
    bool operator!=(QIDORSRequest const & other) const;

    /// @brief Return base_url.
    URL const & get_base_url() const;

    /// @brief Set the base URL; the query and fragment must be empty
    void set_base_url(URL const & url);

    /// @brief Return the media type.
    std::string const & get_media_type() const;

    /// @brief Return the representation.
    Representation const & get_representation() const;

    /// @brief Return the url.
    URL const & get_url () const;

    /// brief Return the selector.
    Selector const & get_selector() const;

    /// @brief Return the dataSet containing the wanted attribute values.
    DataSet const & get_query_data_set() const;

    /// @brief Return the wanted fields.
    std::vector< std::vector < odil::Tag> > const & get_includefields() const;

    /// @brief Return whether fuzzymatching is wanted or not.
    bool get_fuzzymatching() const;

    /// @brief Return the wanted limit.
    int get_limit() const;

    /// @brief Return the wanted offset.
    int get_offset() const;

    /// @brief Generete the associated HTTP request.
    HTTPRequest get_http_request() const;

    /// @brief Prepare a qido request
    void request_datasets(
            Representation representation, Selector const & selector,
            DataSet const & query, std::vector<std::vector<Tag> > const & includefields = {},
            bool fuzzymatching = false, int limit = -1, int offset = 0, bool numerical_tags = false);


private:
    URL _base_url;

    // media_type accepted :
    //     -multipart/related; type="application/dicom+xml"
    //     -application/dicom+json (default)
    std::string _media_type;
    Representation _representation;
    URL _url;
    Selector _selector;
    DataSet _query_data_set;
    // include types where at each index :
    // if _includefields[i].size() = 1 -> element at top level (DataSet level)
    // else _includefields[i][0] = top_seq at top_level,
    //      and next elements of _includefields[i] are subsequences until leaf element
    std::vector< std::vector <odil::Tag> >  _includefields;

    bool _fuzzymatching;
    int _limit; // maximum number of results the origin server shall return.
    int _offset; // number of results the origin server shall skip before the first returned result.

    /// @brief Return if the selector is valid or not
    static bool _is_selector_valid (Selector const & selector);

    /// @brief Return the tag as a numerical string or as a "string"
    static std::string _tag_to_string(odil::Tag const & tag, bool numerical_tag);

    /// @brief Split an URL in a pair of base_url and request selector.
    static std::tuple<URL, Selector, DataSet, std::vector<std::vector< odil::Tag> >,
        bool, int /*offset*/, int /*limit*/ >
        _split_full_url(URL const & url);
};

}

}


#endif // _1cd2d27d_2d97_405b_b9d5_4104210e543a
