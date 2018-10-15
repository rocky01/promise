#ifndef _AUXILIARYCLASSES_CATCHER_MOVEERRORRESOLVETRETHROWT_HPP_
#define _AUXILIARYCLASSES_CATCHER_MOVEERRORRESOLVETRETHROWT_HPP_

#include "Promise.hpp"

class MoveErrorTResolveTRethrowT
{
public:
    MoveErrorTResolveTRethrowT(const MoveErrorTResolveTRethrowT&) = delete;

    explicit MoveErrorTResolveTRethrowT(bool isResolved)
        : isResolved_(isResolved)
    {}

    MoveErrorTResolveTRethrowT(MoveErrorTResolveTRethrowT&& m)
    {
        isResolved_ = m.isResolved_;
    }

    void operator()(int e, prm::Resolver<char> resolve, prm::Rethrower<double> rethrow)
    {
        return isResolved_ ? resolve('w') : rethrow(5.3);
    }

private:
    bool isResolved_;
};

#endif  // _AUXILIARYCLASSES_CATCHER_MOVEERRORRESOLVETRETHROWT_HPP_
