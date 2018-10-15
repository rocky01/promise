#ifndef _AUXILIARYCLASSES_THEN_COPYEXECUTETRESOLVEVOIDREJECTVOID_HPP_
#define _AUXILIARYCLASSES_THEN_COPYEXECUTETRESOLVEVOIDREJECTVOID_HPP_

#include "Promise.hpp"

class CopyExecuteTResolveVoidRejectVoid
{
public:
    explicit CopyExecuteTResolveVoidRejectVoid(bool isResolved)
        : isResolved_(isResolved)
    {}

    void operator()(int e, prm::Resolver<void> resolve, prm::Rejector<void> reject)
    {
        return isResolved_ ? resolve() : reject();
    }

private:
    bool isResolved_;
};

#endif  // _AUXILIARYCLASSES_THEN_COPYEXECUTETRESOLVEVOIDREJECTVOID_HPP_
