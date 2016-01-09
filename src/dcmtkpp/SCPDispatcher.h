/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _f0b69ac6_7d52_401d_a2f3_d5d3f7d69376
#define _f0b69ac6_7d52_401d_a2f3_d5d3f7d69376

#include <map>
#include <memory>

#include "dcmtkpp/Association.h"
#include "dcmtkpp/SCP.h"
#include "dcmtkpp/Value.h"

namespace dcmtkpp
{

class SCPDispatcher
{
public:
    /// @brief Create a dispatcher with network and association.
    SCPDispatcher(Association & association);

    /// @brief Destructor.
    ~SCPDispatcher();

    bool has_scp(Value::Integer command) const;

    std::shared_ptr<SCP> const & get_scp(Value::Integer command) const;

    void set_scp(Value::Integer command, std::shared_ptr<SCP> const & scp);

    void dispatch();
private:
    typedef std::shared_ptr<SCP> SCPPointer;

    Association & _association;
    std::map<Value::Integer, std::shared_ptr<SCP>> _providers;
};

}

#endif // _f0b69ac6_7d52_401d_a2f3_d5d3f7d69376
