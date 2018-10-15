#ifndef _AUXILIARYCLASSES_THEN_COPYEXECUTETRESOLVETREJECTUNDEFINED_HPP_
#define _AUXILIARYCLASSES_THEN_COPYEXECUTETRESOLVETREJECTUNDEFINED_HPP_

#include "Promise.hpp"

class CopyExecuteTResolveTRejectUndefined
{
public:
    explicit CopyExecuteTResolveTRejectUndefined()
    {}

    void operator()(int e, prm::Resolver<char> resolve)
    {
        return resolve('w');
    }
};

#endif  // _AUXILIARYCLASSES_THEN_COPYEXECUTETRESOLVETREJECTUNDEFINED_HPP_
