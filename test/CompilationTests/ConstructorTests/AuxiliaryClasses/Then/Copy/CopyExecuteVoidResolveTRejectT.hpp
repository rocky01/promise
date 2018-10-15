#ifndef _AUXILIARYCLASSES_THEN_COPYEXECUTEVOIDRESOLVETREJECTT_HPP_
#define _AUXILIARYCLASSES_THEN_COPYEXECUTEVOIDRESOLVETREJECTT_HPP_

#include "Promise.hpp"

class CopyExecuteVoidResolveTRejectT
{
public:
    explicit CopyExecuteVoidResolveTRejectT(bool isResolved)
        : isResolved_(isResolved)
    {}

    void operator()(prm::Resolver<char> resolve, prm::Rejector<double> reject)
    {
        return isResolved_ ? resolve('w') : reject(5.3);
    }

private:
    bool isResolved_;
};

#endif  // _AUXILIARYCLASSES_THEN_COPYEXECUTEVOIDRESOLVETREJECTT_HPP_
