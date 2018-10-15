#ifndef _AUXILIARYCLASSES_THEN_COPYEXECUTETRESOLVEUNDEFINEDREJECTVOID_HPP_
#define _AUXILIARYCLASSES_THEN_COPYEXECUTETRESOLVEUNDEFINEDREJECTVOID_HPP_

#include "Promise.hpp"

class CopyExecuteTResolveUndefinedRejectVoid
{
public:
    explicit CopyExecuteTResolveUndefinedRejectVoid()
    {}

    void operator()(int e, prm::Rejector<void> reject)
    {
        return reject();
    }
};

#endif  // _AUXILIARYCLASSES_THEN_COPYEXECUTETRESOLVEUNDEFINEDREJECTVOID_HPP_
