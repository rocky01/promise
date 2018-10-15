#ifndef _AUXILIARYCLASSES_THEN_EMPLACEEXECUTETRESOLVETREJECTUNDEFINED_HPP_
#define _AUXILIARYCLASSES_THEN_EMPLACEEXECUTETRESOLVETREJECTUNDEFINED_HPP_

#include "Promise.hpp"

class EmplaceExecuteTResolveTRejectUndefined
{
public:
    EmplaceExecuteTResolveTRejectUndefined(const EmplaceExecuteTResolveTRejectUndefined&) = delete;
    EmplaceExecuteTResolveTRejectUndefined(const EmplaceExecuteTResolveTRejectUndefined&&) = delete;

    explicit EmplaceExecuteTResolveTRejectUndefined()
    {}

    void operator()(int e, prm::Resolver<char> resolve)
    {
        return resolve('w');
    }
};

#endif  // _AUXILIARYCLASSES_THEN_EMPLACEEXECUTETRESOLVETREJECTUNDEFINED_HPP_
