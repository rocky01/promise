#ifndef _AUXILIARYCLASSES_THEN_MOVEEXECUTEVOIDRESOLVEVOIDREJECTUNDEFINED_HPP_
#define _AUXILIARYCLASSES_THEN_MOVEEXECUTEVOIDRESOLVEVOIDREJECTUNDEFINED_HPP_

#include "Promise.hpp"

class MoveExecuteVoidResolveVoidRejectUndefined
{
public:
    MoveExecuteVoidResolveVoidRejectUndefined(const MoveExecuteVoidResolveVoidRejectUndefined&) = delete;

    explicit MoveExecuteVoidResolveVoidRejectUndefined()
    {}

    MoveExecuteVoidResolveVoidRejectUndefined(MoveExecuteVoidResolveVoidRejectUndefined&& m)
    {}

    void operator()(prm::Resolver<void> resolve)
    {
        return resolve();
    }
};

#endif  // _AUXILIARYCLASSES_THEN_MOVEEXECUTEVOIDRESOLVEVOIDREJECTUNDEFINED_HPP_
