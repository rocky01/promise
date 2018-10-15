#ifndef _AUXILIARYCLASSES_THEN_COPYEXECUTEVOIDRESOLVETREJECTVOID_HPP_
#define _AUXILIARYCLASSES_THEN_COPYEXECUTEVOIDRESOLVETREJECTVOID_HPP_

#include "Promise.hpp"

class CopyExecuteVoidResolveTRejectVoid
{
public:
    explicit CopyExecuteVoidResolveTRejectVoid(bool isResolved)
        : isResolved_(isResolved)
    {}

    void operator()(prm::Resolver<char> resolve, prm::Rejector<void> reject)
    {
        return isResolved_ ? resolve('w') : reject();
    }

private:
    bool isResolved_;
};

#endif  // _AUXILIARYCLASSES_THEN_COPYEXECUTEVOIDRESOLVETREJECTVOID_HPP_
