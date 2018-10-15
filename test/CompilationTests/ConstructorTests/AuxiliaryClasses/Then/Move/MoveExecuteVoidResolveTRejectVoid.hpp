#ifndef _AUXILIARYCLASSES_THEN_MOVEEXECUTEVOIDRESOLVETREJECTVOID_HPP_
#define _AUXILIARYCLASSES_THEN_MOVEEXECUTEVOIDRESOLVETREJECTVOID_HPP_

#include "Promise.hpp"

class MoveExecuteVoidResolveTRejectVoid
{
public:
    MoveExecuteVoidResolveTRejectVoid(const MoveExecuteVoidResolveTRejectVoid&) = delete;

    explicit MoveExecuteVoidResolveTRejectVoid(bool isResolved)
        : isResolved_(isResolved)
    {}

    MoveExecuteVoidResolveTRejectVoid(MoveExecuteVoidResolveTRejectVoid&& m)
    {
        isResolved_ = m.isResolved_;
    }

    void operator()(prm::Resolver<char> resolve, prm::Rejector<void> reject)
    {
        return isResolved_ ? resolve('w') : reject();
    }

private:
    bool isResolved_;
};

#endif  // _AUXILIARYCLASSES_THEN_MOVEEXECUTEVOIDRESOLVETREJECTVOID_HPP_
