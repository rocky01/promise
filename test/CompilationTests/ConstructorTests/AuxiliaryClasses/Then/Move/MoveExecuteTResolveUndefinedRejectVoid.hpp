#ifndef _AUXILIARYCLASSES_THEN_MOVEEXECUTETRESOLVEUNDEFINEDREJECTVOID_HPP_
#define _AUXILIARYCLASSES_THEN_MOVEEXECUTETRESOLVEUNDEFINEDREJECTVOID_HPP_

#include "Promise.hpp"

class MoveExecuteTResolveUndefinedRejectVoid
{
public:
    MoveExecuteTResolveUndefinedRejectVoid(const MoveExecuteTResolveUndefinedRejectVoid&) = delete;

    explicit MoveExecuteTResolveUndefinedRejectVoid()
    {}

    MoveExecuteTResolveUndefinedRejectVoid(MoveExecuteTResolveUndefinedRejectVoid&& m)
    {}

    void operator()(int e, prm::Rejector<void> reject)
    {
        return reject();
    }
};

#endif  // _AUXILIARYCLASSES_THEN_MOVEEXECUTETRESOLVEUNDEFINEDREJECTVOID_HPP_
