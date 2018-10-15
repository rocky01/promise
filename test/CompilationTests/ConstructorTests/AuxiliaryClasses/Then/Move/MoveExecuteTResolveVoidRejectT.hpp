#ifndef _AUXILIARYCLASSES_THEN_MOVEEXECUTETRESOLVEVOIDREJECTT_HPP_
#define _AUXILIARYCLASSES_THEN_MOVEEXECUTETRESOLVEVOIDREJECTT_HPP_

#include "Promise.hpp"

class MoveExecuteTResolveVoidRejectT
{
public:
    MoveExecuteTResolveVoidRejectT(const MoveExecuteTResolveVoidRejectT&) = delete;

    explicit MoveExecuteTResolveVoidRejectT(bool isResolved)
        : isResolved_(isResolved)
    {}

    MoveExecuteTResolveVoidRejectT(MoveExecuteTResolveVoidRejectT&& m)
    {
        isResolved_ = m.isResolved_;
    }

    void operator()(int e, prm::Resolver<void> resolve, prm::Rejector<double> reject)
    {
        return isResolved_ ? resolve() : reject(5.3);
    }

private:
    bool isResolved_;
};

#endif  // _AUXILIARYCLASSES_THEN_MOVEEXECUTETRESOLVEVOIDREJECTT_HPP_
