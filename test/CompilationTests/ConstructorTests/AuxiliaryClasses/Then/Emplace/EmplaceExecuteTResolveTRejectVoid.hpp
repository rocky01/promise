#ifndef _AUXILIARYCLASSES_THEN_EMPLACEEXECUTETRESOLVETREJECTVOID_HPP_
#define _AUXILIARYCLASSES_THEN_EMPLACEEXECUTETRESOLVETREJECTVOID_HPP_

#include "Promise.hpp"

class EmplaceExecuteTResolveTRejectVoid
{
public:
    EmplaceExecuteTResolveTRejectVoid(const EmplaceExecuteTResolveTRejectVoid&) = delete;
    EmplaceExecuteTResolveTRejectVoid(const EmplaceExecuteTResolveTRejectVoid&&) = delete;

    explicit EmplaceExecuteTResolveTRejectVoid(bool isResolved)
        : isResolved_(isResolved)
    {}

    void operator()(int e, prm::Resolver<char> resolve, prm::Rejector<void> reject)
    {
        return isResolved_ ? resolve('w') : reject();
    }

private:
    bool isResolved_;
};

#endif  // _AUXILIARYCLASSES_THEN_EMPLACEEXECUTETRESOLVETREJECTVOID_HPP_
