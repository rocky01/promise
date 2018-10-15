#ifndef _AUXILIARYCLASSES_THEN_COPYEXECUTEVOIDRESOLVEVOIDREJECTUNDEFINED_HPP_
#define _AUXILIARYCLASSES_THEN_COPYEXECUTEVOIDRESOLVEVOIDREJECTUNDEFINED_HPP_

#include "Promise.hpp"

class CopyExecuteVoidResolveVoidRejectUndefined
{
public:
    explicit CopyExecuteVoidResolveVoidRejectUndefined()
    {}

    void operator()(prm::Resolver<void> resolve)
    {
        return resolve();
    }
};

#endif  // _AUXILIARYCLASSES_THEN_COPYEXECUTEVOIDRESOLVEVOIDREJECTUNDEFINED_HPP_
