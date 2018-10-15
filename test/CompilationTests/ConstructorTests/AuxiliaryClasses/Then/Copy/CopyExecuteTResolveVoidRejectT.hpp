#ifndef _AUXILIARYCLASSES_THEN_COPYEXECUTETRESOLVEVOIDREJECTT_HPP_
#define _AUXILIARYCLASSES_THEN_COPYEXECUTETRESOLVEVOIDREJECTT_HPP_

#include "Promise.hpp"

class CopyExecuteTResolveVoidRejectT
{
public:
    explicit CopyExecuteTResolveVoidRejectT(bool isResolved)
        : isResolved_(isResolved)
    {}

    void operator()(int e, prm::Resolver<void> resolve, prm::Rejector<double> reject)
    {
        return isResolved_ ? resolve() : reject(5.3);
    }

private:
    bool isResolved_;
};

#endif  // _AUXILIARYCLASSES_THEN_COPYEXECUTETRESOLVEVOIDREJECTT_HPP_
