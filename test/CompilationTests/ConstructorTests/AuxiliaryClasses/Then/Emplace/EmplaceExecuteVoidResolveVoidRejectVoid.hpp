#ifndef _AUXILIARYCLASSES_THEN_EMPLACEEXECUTEVOIDRESOLVEVOIDREJECTVOID_HPP_
#define _AUXILIARYCLASSES_THEN_EMPLACEEXECUTEVOIDRESOLVEVOIDREJECTVOID_HPP_

#include "Promise.hpp"

class EmplaceExecuteVoidResolveVoidRejectVoid
{
public:
    EmplaceExecuteVoidResolveVoidRejectVoid(const EmplaceExecuteVoidResolveVoidRejectVoid&) = delete;
    EmplaceExecuteVoidResolveVoidRejectVoid(const EmplaceExecuteVoidResolveVoidRejectVoid&&) = delete;

    explicit EmplaceExecuteVoidResolveVoidRejectVoid(bool isResolved)
        : isResolved_(isResolved)
    {}

    void operator()(prm::Resolver<void> resolve, prm::Rejector<void> reject)
    {
        return isResolved_ ? resolve() : reject();
    }

private:
    bool isResolved_;
};

#endif  // _AUXILIARYCLASSES_THEN_EMPLACEEXECUTEVOIDRESOLVEVOIDREJECTVOID_HPP_
