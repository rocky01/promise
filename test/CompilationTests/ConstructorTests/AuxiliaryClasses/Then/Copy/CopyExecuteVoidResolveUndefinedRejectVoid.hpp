#ifndef _AUXILIARYCLASSES_THEN_COPYEXECUTEVOIDRESOLVEUNDEFINEDREJECTVOID_HPP_
#define _AUXILIARYCLASSES_THEN_COPYEXECUTEVOIDRESOLVEUNDEFINEDREJECTVOID_HPP_

#include "Promise.hpp"

class CopyExecuteVoidResolveUndefinedRejectVoid
{
public:
    explicit CopyExecuteVoidResolveUndefinedRejectVoid()
    {}

    void operator()(prm::Rejector<void> reject)
    {
        return reject();
    }
};

#endif  // _AUXILIARYCLASSES_THEN_COPYEXECUTEVOIDRESOLVEUNDEFINEDREJECTVOID_HPP_
