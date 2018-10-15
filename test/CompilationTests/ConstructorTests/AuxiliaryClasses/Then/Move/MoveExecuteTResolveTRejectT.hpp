#ifndef _AUXILIARYCLASSES_THEN_MOVEEXECUTETRESOLVETREJECTT_HPP_
#define _AUXILIARYCLASSES_THEN_MOVEEXECUTETRESOLVETREJECTT_HPP_

#include "Promise.hpp"

class MoveExecuteTResolveTRejectT
{
public:
    MoveExecuteTResolveTRejectT(const MoveExecuteTResolveTRejectT&) = delete;

    explicit MoveExecuteTResolveTRejectT(bool isResolved)
        : isResolved_(isResolved)
    {}

    MoveExecuteTResolveTRejectT(MoveExecuteTResolveTRejectT&& m)
    {
        isResolved_ = m.isResolved_;
    }

    void operator()(int e, prm::Resolver<char> resolve, prm::Rejector<double> reject)
    {
        return isResolved_ ? resolve('w') : reject(5.3);
    }

private:
    bool isResolved_;
};

#endif  // _AUXILIARYCLASSES_THEN_MOVEEXECUTETRESOLVETREJECTT_HPP_
