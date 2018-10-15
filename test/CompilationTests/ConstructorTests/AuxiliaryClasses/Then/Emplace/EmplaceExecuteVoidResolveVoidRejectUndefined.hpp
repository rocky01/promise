#ifndef _AUXILIARYCLASSES_THEN_EMPLACEEXECUTEVOIDRESOLVEVOIDREJECTUNDEFINED_HPP_
#define _AUXILIARYCLASSES_THEN_EMPLACEEXECUTEVOIDRESOLVEVOIDREJECTUNDEFINED_HPP_

#include "Promise.hpp"

class EmplaceExecuteVoidResolveVoidRejectUndefined
{
public:
    EmplaceExecuteVoidResolveVoidRejectUndefined(const EmplaceExecuteVoidResolveVoidRejectUndefined&) = delete;
    EmplaceExecuteVoidResolveVoidRejectUndefined(const EmplaceExecuteVoidResolveVoidRejectUndefined&&) = delete;

    explicit EmplaceExecuteVoidResolveVoidRejectUndefined()
    {}

    void operator()(prm::Resolver<void> resolve)
    {
        return resolve();
    }
};

#endif  // _AUXILIARYCLASSES_THEN_EMPLACEEXECUTEVOIDRESOLVEVOIDREJECTUNDEFINED_HPP_
