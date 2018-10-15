#ifndef _AUXILIARYCLASSES_THEN_MOVEEXECUTEVOIDRESOLVETREJECTUNDEFINED_HPP_
#define _AUXILIARYCLASSES_THEN_MOVEEXECUTEVOIDRESOLVETREJECTUNDEFINED_HPP_

#include "Promise.hpp"

class MoveExecuteVoidResolveTRejectUndefined
{
public:
    MoveExecuteVoidResolveTRejectUndefined(const MoveExecuteVoidResolveTRejectUndefined&) = delete;

    explicit MoveExecuteVoidResolveTRejectUndefined()
    {}

    MoveExecuteVoidResolveTRejectUndefined(MoveExecuteVoidResolveTRejectUndefined&& m)
    {}

    void operator()(prm::Resolver<char> resolve)
    {
        return resolve('w');
    }
};

#endif  // _AUXILIARYCLASSES_THEN_MOVEEXECUTEVOIDRESOLVETREJECTUNDEFINED_HPP_
