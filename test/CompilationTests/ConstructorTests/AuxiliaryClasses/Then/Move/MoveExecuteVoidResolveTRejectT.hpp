#ifndef _AUXILIARYCLASSES_THEN_MOVEEXECUTEVOIDRESOLVETREJECTT_HPP_
#define _AUXILIARYCLASSES_THEN_MOVEEXECUTEVOIDRESOLVETREJECTT_HPP_

#include "Promise.hpp"

class MoveExecuteVoidResolveTRejectT
{
public:
    MoveExecuteVoidResolveTRejectT(const MoveExecuteVoidResolveTRejectT&) = delete;

    explicit MoveExecuteVoidResolveTRejectT(bool isResolved)
        : isResolved_(isResolved)
    {}

    MoveExecuteVoidResolveTRejectT(MoveExecuteVoidResolveTRejectT&& m)
    {
        isResolved_ = m.isResolved_;
    }

    void operator()(prm::Resolver<char> resolve, prm::Rejector<double> reject)
    {
        return isResolved_ ? resolve('w') : reject(5.3);
    }

private:
    bool isResolved_;
};

#endif  // _AUXILIARYCLASSES_THEN_MOVEEXECUTEVOIDRESOLVETREJECTT_HPP_
