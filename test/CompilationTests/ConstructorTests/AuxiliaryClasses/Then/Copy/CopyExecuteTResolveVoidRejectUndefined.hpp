#ifndef _AUXILIARYCLASSES_THEN_COPYEXECUTETRESOLVEVOIDREJECTUNDEFINED_HPP_
#define _AUXILIARYCLASSES_THEN_COPYEXECUTETRESOLVEVOIDREJECTUNDEFINED_HPP_

#include "Promise.hpp"

class CopyExecuteTResolveVoidRejectUndefined
{
public:
    explicit CopyExecuteTResolveVoidRejectUndefined()
    {}

    void operator()(int e, prm::Resolver<void> resolve)
    {
        return resolve();
    }
};

#endif  // _AUXILIARYCLASSES_THEN_COPYEXECUTETRESOLVEVOIDREJECTUNDEFINED_HPP_
