#ifndef _AUXILIARYCLASSES_THEN_EMPLACEEXECUTETRESOLVEVOIDREJECTVOID_HPP_
#define _AUXILIARYCLASSES_THEN_EMPLACEEXECUTETRESOLVEVOIDREJECTVOID_HPP_

#include "Promise.hpp"

class EmplaceExecuteTResolveVoidRejectVoid
{
public:
    EmplaceExecuteTResolveVoidRejectVoid(const EmplaceExecuteTResolveVoidRejectVoid&) = delete;
    EmplaceExecuteTResolveVoidRejectVoid(const EmplaceExecuteTResolveVoidRejectVoid&&) = delete;

    explicit EmplaceExecuteTResolveVoidRejectVoid(bool isResolved)
        : isResolved_(isResolved)
    {}

    void operator()(int e, prm::Resolver<void> resolve, prm::Rejector<void> reject)
    {
        return isResolved_ ? resolve() : reject();
    }

private:
    bool isResolved_;
};

#endif  // _AUXILIARYCLASSES_THEN_EMPLACEEXECUTETRESOLVEVOIDREJECTVOID_HPP_
