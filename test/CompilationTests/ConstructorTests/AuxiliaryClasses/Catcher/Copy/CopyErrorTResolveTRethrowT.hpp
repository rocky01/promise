#ifndef _AUXILIARYCLASSES_CATCHER_COPYERRORRESOLVETRETHROWT_HPP_
#define _AUXILIARYCLASSES_CATCHER_COPYERRORRESOLVETRETHROWT_HPP_

#include "Promise.hpp"

class CopyErrorTResolveTRethrowT
{
public:
    explicit CopyErrorTResolveTRethrowT(bool isResolved)
        : isResolved_(isResolved)
    {}

    void operator()(int e, prm::Resolver<char> resolve, prm::Rethrower<double> rethrow)
    {
        return isResolved_ ? resolve('w') : rethrow(5.3);
    }

private:
    bool isResolved_;
};

#endif  // _AUXILIARYCLASSES_CATCHER_COPYERRORRESOLVETRETHROWT_HPP_
