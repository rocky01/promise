#ifndef _AUXILIARYCLASSES_THEN_EMPLACEEXECUTETRESOLVEUNDEFINEDREJECTVOID_HPP_
#define _AUXILIARYCLASSES_THEN_EMPLACEEXECUTETRESOLVEUNDEFINEDREJECTVOID_HPP_

#include "Promise.hpp"

class EmplaceExecuteTResolveUndefinedRejectVoid
{
public:
    EmplaceExecuteTResolveUndefinedRejectVoid(const EmplaceExecuteTResolveUndefinedRejectVoid&) = delete;
    EmplaceExecuteTResolveUndefinedRejectVoid(const EmplaceExecuteTResolveUndefinedRejectVoid&&) = delete;

    explicit EmplaceExecuteTResolveUndefinedRejectVoid()
    {}

    void operator()(int e, prm::Rejector<void> reject)
    {
        return reject();
    }
};

#endif  // _AUXILIARYCLASSES_THEN_EMPLACEEXECUTETRESOLVEUNDEFINEDREJECTVOID_HPP_
