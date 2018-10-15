#ifndef _AUXILIARYCLASSES_THEN_COPYEXECUTETRESOLVETREJECTT_HPP_
#define _AUXILIARYCLASSES_THEN_COPYEXECUTETRESOLVETREJECTT_HPP_

#include "Promise.hpp"

class CopyExecuteTResolveTRejectT
{
public:
    explicit CopyExecuteTResolveTRejectT(bool isResolved)
        : isResolved_(isResolved)
    {}

    void operator()(int e, prm::Resolver<char> resolve, prm::Rejector<double> reject)
    {
        return isResolved_ ? resolve('w') : reject(5.3);
    }

private:
    bool isResolved_;
};

#endif  // _AUXILIARYCLASSES_THEN_COPYEXECUTETRESOLVETREJECTT_HPP_
