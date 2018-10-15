#ifndef _AUXILIARYCLASSES_THEN_MOVEEXECUTEVOIDRESOLVEUNDEFINEDREJECTVOID_HPP_
#define _AUXILIARYCLASSES_THEN_MOVEEXECUTEVOIDRESOLVEUNDEFINEDREJECTVOID_HPP_

#include "Promise.hpp"

class MoveExecuteVoidResolveUndefinedRejectVoid
{
public:
    MoveExecuteVoidResolveUndefinedRejectVoid(const MoveExecuteVoidResolveUndefinedRejectVoid&) = delete;

    explicit MoveExecuteVoidResolveUndefinedRejectVoid()
    {}

    MoveExecuteVoidResolveUndefinedRejectVoid(MoveExecuteVoidResolveUndefinedRejectVoid&& m)
    {}

    void operator()(prm::Rejector<void> reject)
    {
        return reject();
    }
};

#endif  // _AUXILIARYCLASSES_THEN_MOVEEXECUTEVOIDRESOLVEUNDEFINEDREJECTVOID_HPP_
