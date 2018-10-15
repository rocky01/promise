#ifndef _AUXILIARYCLASSES_THEN_MOVEEXECUTETRESOLVEVOIDREJECTVOID_HPP_
#define _AUXILIARYCLASSES_THEN_MOVEEXECUTETRESOLVEVOIDREJECTVOID_HPP_

#include "Promise.hpp"

class MoveExecuteTResolveVoidRejectVoid
{
public:
    MoveExecuteTResolveVoidRejectVoid(const MoveExecuteTResolveVoidRejectVoid&) = delete;

    explicit MoveExecuteTResolveVoidRejectVoid(bool isResolved)
        : isResolved_(isResolved)
    {}

    MoveExecuteTResolveVoidRejectVoid(MoveExecuteTResolveVoidRejectVoid&& m)
    {
        isResolved_ = m.isResolved_;
    }

    void operator()(int e, prm::Resolver<void> resolve, prm::Rejector<void> reject)
    {
        return isResolved_ ? resolve() : reject();
    }

private:
    bool isResolved_;
};

#endif  // _AUXILIARYCLASSES_THEN_MOVEEXECUTETRESOLVEVOIDREJECTVOID_HPP_
