#ifndef _AUXILIARYCLASSES_THEN_MOVEEXECUTETRESOLVEVOIDREJECTUNDEFINED_HPP_
#define _AUXILIARYCLASSES_THEN_MOVEEXECUTETRESOLVEVOIDREJECTUNDEFINED_HPP_

#include "Promise.hpp"

class MoveExecuteTResolveVoidRejectUndefined
{
public:
    MoveExecuteTResolveVoidRejectUndefined(const MoveExecuteTResolveVoidRejectUndefined&) = delete;

    explicit MoveExecuteTResolveVoidRejectUndefined()
    {}

    MoveExecuteTResolveVoidRejectUndefined(MoveExecuteTResolveVoidRejectUndefined&& m)
    {}

    void operator()(int e, prm::Resolver<void> resolve)
    {
        return resolve();
    }
};

#endif  // _AUXILIARYCLASSES_THEN_MOVEEXECUTETRESOLVEVOIDREJECTUNDEFINED_HPP_
