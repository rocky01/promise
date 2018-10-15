#ifndef _AUXILIARYCLASSES_CATCHER_EMPLACEERRORRESOLVETRETHROWT_HPP_
#define _AUXILIARYCLASSES_CATCHER_EMPLACEERRORRESOLVETRETHROWT_HPP_

#include "Promise.hpp"

class EmplaceErrorTResolveTRethrowT
{
public:
    EmplaceErrorTResolveTRethrowT(const EmplaceErrorTResolveTRethrowT&) = delete;
    EmplaceErrorTResolveTRethrowT(const EmplaceErrorTResolveTRethrowT&&) = delete;

    explicit EmplaceErrorTResolveTRethrowT(bool isResolved)
        : isResolved_(isResolved)
    {}

    void operator()(int e, prm::Resolver<char> resolve, prm::Rethrower<double> rethrow)
    {
        return isResolved_ ? resolve('w') : rethrow(5.3);
    }

private:
    bool isResolved_;
};

#endif  // _AUXILIARYCLASSES_CATCHER_EMPLACEERRORRESOLVETRETHROWT_HPP_
