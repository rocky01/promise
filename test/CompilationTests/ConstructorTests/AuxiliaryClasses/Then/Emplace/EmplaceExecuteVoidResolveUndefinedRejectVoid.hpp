#ifndef _AUXILIARYCLASSES_THEN_EMPLACEEXECUTEVOIDRESOLVEUNDEFINEDREJECTVOID_HPP_
#define _AUXILIARYCLASSES_THEN_EMPLACEEXECUTEVOIDRESOLVEUNDEFINEDREJECTVOID_HPP_

#include "Promise.hpp"

class EmplaceExecuteVoidResolveUndefinedRejectVoid
{
public:
    EmplaceExecuteVoidResolveUndefinedRejectVoid(const EmplaceExecuteVoidResolveUndefinedRejectVoid&) = delete;
    EmplaceExecuteVoidResolveUndefinedRejectVoid(const EmplaceExecuteVoidResolveUndefinedRejectVoid&&) = delete;

    explicit EmplaceExecuteVoidResolveUndefinedRejectVoid()
    {}

    void operator()(prm::Rejector<void> reject)
    {
        return reject();
    }
};

#endif  // _AUXILIARYCLASSES_THEN_EMPLACEEXECUTEVOIDRESOLVEUNDEFINEDREJECTVOID_HPP_
