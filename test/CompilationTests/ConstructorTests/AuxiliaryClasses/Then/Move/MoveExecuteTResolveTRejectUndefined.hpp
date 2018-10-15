#ifndef _AUXILIARYCLASSES_THEN_MOVEEXECUTETRESOLVETREJECTUNDEFINED_HPP_
#define _AUXILIARYCLASSES_THEN_MOVEEXECUTETRESOLVETREJECTUNDEFINED_HPP_

#include "Promise.hpp"

class MoveExecuteTResolveTRejectUndefined
{
public:
    MoveExecuteTResolveTRejectUndefined(const MoveExecuteTResolveTRejectUndefined&) = delete;

    explicit MoveExecuteTResolveTRejectUndefined()
    {}

    MoveExecuteTResolveTRejectUndefined(MoveExecuteTResolveTRejectUndefined&& m)
    {}

    void operator()(int e, prm::Resolver<char> resolve)
    {
        return resolve('w');
    }
};

#endif  // _AUXILIARYCLASSES_THEN_MOVEEXECUTETRESOLVETREJECTUNDEFINED_HPP_
