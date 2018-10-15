#ifndef _AUXILIARYCLASSES_THEN_COPYEXECUTEVOIDRESOLVETREJECTUNDEFINED_HPP_
#define _AUXILIARYCLASSES_THEN_COPYEXECUTEVOIDRESOLVETREJECTUNDEFINED_HPP_

#include "Promise.hpp"

class CopyExecuteVoidResolveTRejectUndefined
{
public:
    explicit CopyExecuteVoidResolveTRejectUndefined()
    {}

    void operator()(prm::Resolver<char> resolve)
    {
        return resolve('w');
    }
};

#endif  // _AUXILIARYCLASSES_THEN_COPYEXECUTEVOIDRESOLVETREJECTUNDEFINED_HPP_
