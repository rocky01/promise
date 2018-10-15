#ifndef _AUXILIARYCLASSES_THEN_COPYEXECUTETRESOLVETREJECTVOID_HPP_
#define _AUXILIARYCLASSES_THEN_COPYEXECUTETRESOLVETREJECTVOID_HPP_

#include "Promise.hpp"

class CopyExecuteTResolveTRejectVoid
{
public:
    explicit CopyExecuteTResolveTRejectVoid(bool isResolved)
        : isResolved_(isResolved)
    {}

    void operator()(int e, prm::Resolver<char> resolve, prm::Rejector<void> reject)
    {
        return isResolved_ ? resolve('w') : reject();
    }

private:
    bool isResolved_;
};

#endif  // _AUXILIARYCLASSES_THEN_COPYEXECUTETRESOLVETREJECTVOID_HPP_
