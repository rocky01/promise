#ifndef _AUXILIARYCLASSES_THEN_EMPLACEEXECUTEVOIDRESOLVETREJECTUNDEFINED_HPP_
#define _AUXILIARYCLASSES_THEN_EMPLACEEXECUTEVOIDRESOLVETREJECTUNDEFINED_HPP_

#include "Promise.hpp"

class EmplaceExecuteVoidResolveTRejectUndefined
{
public:
    EmplaceExecuteVoidResolveTRejectUndefined(const EmplaceExecuteVoidResolveTRejectUndefined&) = delete;
    EmplaceExecuteVoidResolveTRejectUndefined(const EmplaceExecuteVoidResolveTRejectUndefined&&) = delete;

    explicit EmplaceExecuteVoidResolveTRejectUndefined()
    {}

    void operator()(prm::Resolver<char> resolve)
    {
        return resolve('w');
    }
};

#endif  // _AUXILIARYCLASSES_THEN_EMPLACEEXECUTEVOIDRESOLVETREJECTUNDEFINED_HPP_
