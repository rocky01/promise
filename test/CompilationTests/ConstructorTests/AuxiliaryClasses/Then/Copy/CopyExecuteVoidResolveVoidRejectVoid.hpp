#ifndef _AUXILIARYCLASSES_THEN_COPYEXECUTEVOIDRESOLVEVOIDREJECTVOID_HPP_
#define _AUXILIARYCLASSES_THEN_COPYEXECUTEVOIDRESOLVEVOIDREJECTVOID_HPP_

#include "Promise.hpp"

class CopyExecuteVoidResolveVoidRejectVoid
{
public:
    explicit CopyExecuteVoidResolveVoidRejectVoid(bool isResolved)
        : isResolved_(isResolved)
    {}

    void operator()(prm::Resolver<void> resolve, prm::Rejector<void> reject)
    {
        return isResolved_ ? resolve() : reject();
    }

private:
    bool isResolved_;
};

#endif  // _AUXILIARYCLASSES_THEN_COPYEXECUTEVOIDRESOLVEVOIDREJECTVOID_HPP_
