#ifndef _AUXILIARYCLASSES_THEN_MOVEEXECUTEVOIDRESOLVEVOIDREJECTVOID_HPP_
#define _AUXILIARYCLASSES_THEN_MOVEEXECUTEVOIDRESOLVEVOIDREJECTVOID_HPP_

#include "Promise.hpp"

class MoveExecuteVoidResolveVoidRejectVoid
{
public:
    MoveExecuteVoidResolveVoidRejectVoid(const MoveExecuteVoidResolveVoidRejectVoid&) = delete;

    explicit MoveExecuteVoidResolveVoidRejectVoid(bool isResolved)
        : isResolved_(isResolved)
    {}

    MoveExecuteVoidResolveVoidRejectVoid(MoveExecuteVoidResolveVoidRejectVoid&& m)
    {
        isResolved_ = m.isResolved_;
    }

    void operator()(prm::Resolver<void> resolve, prm::Rejector<void> reject)
    {
        return isResolved_ ? resolve() : reject();
    }

private:
    bool isResolved_;
};

#endif  // _AUXILIARYCLASSES_THEN_MOVEEXECUTEVOIDRESOLVEVOIDREJECTVOID_HPP_
