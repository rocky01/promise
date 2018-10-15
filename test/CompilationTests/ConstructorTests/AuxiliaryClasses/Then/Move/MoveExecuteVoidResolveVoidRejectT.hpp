#ifndef _AUXILIARYCLASSES_THEN_MOVEEXECUTEVOIDRESOLVEVOIDREJECTT_HPP_
#define _AUXILIARYCLASSES_THEN_MOVEEXECUTEVOIDRESOLVEVOIDREJECTT_HPP_

#include "Promise.hpp"

class MoveExecuteVoidResolveVoidRejectT
{
public:
    MoveExecuteVoidResolveVoidRejectT(const MoveExecuteVoidResolveVoidRejectT&) = delete;

    explicit MoveExecuteVoidResolveVoidRejectT(bool isResolved)
        : isResolved_(isResolved)
    {}

    MoveExecuteVoidResolveVoidRejectT(MoveExecuteVoidResolveVoidRejectT&& m)
    {
        isResolved_ = m.isResolved_;
    }

    void operator()(prm::Resolver<void> resolve, prm::Rejector<double> reject)
    {
        return isResolved_ ? resolve() : reject(5.3);
    }

private:
    bool isResolved_;
};

#endif  // _AUXILIARYCLASSES_THEN_MOVEEXECUTEVOIDRESOLVEVOIDREJECTT_HPP_
