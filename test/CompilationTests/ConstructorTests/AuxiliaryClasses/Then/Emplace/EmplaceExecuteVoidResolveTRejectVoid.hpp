#ifndef _AUXILIARYCLASSES_THEN_EMPLACEEXECUTEVOIDRESOLVETREJECTVOID_HPP_
#define _AUXILIARYCLASSES_THEN_EMPLACEEXECUTEVOIDRESOLVETREJECTVOID_HPP_

#include "Promise.hpp"

class EmplaceExecuteVoidResolveTRejectVoid
{
public:
    EmplaceExecuteVoidResolveTRejectVoid(const EmplaceExecuteVoidResolveTRejectVoid&) = delete;
    EmplaceExecuteVoidResolveTRejectVoid(const EmplaceExecuteVoidResolveTRejectVoid&&) = delete;

    explicit EmplaceExecuteVoidResolveTRejectVoid(bool isResolved)
        : isResolved_(isResolved)
    {}

    void operator()(prm::Resolver<char> resolve, prm::Rejector<void> reject)
    {
        return isResolved_ ? resolve('w') : reject();
    }

private:
    bool isResolved_;
};

#endif  // _AUXILIARYCLASSES_THEN_EMPLACEEXECUTEVOIDRESOLVETREJECTVOID_HPP_
