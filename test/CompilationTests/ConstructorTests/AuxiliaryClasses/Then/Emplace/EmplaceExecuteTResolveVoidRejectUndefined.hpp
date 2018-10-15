#ifndef _AUXILIARYCLASSES_THEN_EMPLACEEXECUTETRESOLVEVOIDREJECTUNDEFINED_HPP_
#define _AUXILIARYCLASSES_THEN_EMPLACEEXECUTETRESOLVEVOIDREJECTUNDEFINED_HPP_

#include "Promise.hpp"

class EmplaceExecuteTResolveVoidRejectUndefined
{
public:
    EmplaceExecuteTResolveVoidRejectUndefined(const EmplaceExecuteTResolveVoidRejectUndefined&) = delete;
    EmplaceExecuteTResolveVoidRejectUndefined(const EmplaceExecuteTResolveVoidRejectUndefined&&) = delete;

    explicit EmplaceExecuteTResolveVoidRejectUndefined()
    {}

    void operator()(int e, prm::Resolver<void> resolve)
    {
        return resolve();
    }
};

#endif  // _AUXILIARYCLASSES_THEN_EMPLACEEXECUTETRESOLVEVOIDREJECTUNDEFINED_HPP_
