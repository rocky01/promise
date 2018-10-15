#ifndef _AUXILIARYCLASSES_THEN_MOVEEXECUTETRESOLVETREJECTVOID_HPP_
#define _AUXILIARYCLASSES_THEN_MOVEEXECUTETRESOLVETREJECTVOID_HPP_

#include "Promise.hpp"

class MoveExecuteTResolveTRejectVoid
{
public:
    MoveExecuteTResolveTRejectVoid(const MoveExecuteTResolveTRejectVoid&) = delete;

    explicit MoveExecuteTResolveTRejectVoid(bool isResolved)
        : isResolved_(isResolved)
    {}

    MoveExecuteTResolveTRejectVoid(MoveExecuteTResolveTRejectVoid&& m)
    {
        isResolved_ = m.isResolved_;
    }

    void operator()(int e, prm::Resolver<char> resolve, prm::Rejector<void> reject)
    {
        return isResolved_ ? resolve('w') : reject();
    }

private:
    bool isResolved_;
};

#endif  // _AUXILIARYCLASSES_THEN_MOVEEXECUTETRESOLVETREJECTVOID_HPP_
