#ifndef _AUXILIARYCLASSES_THEN_MOVEEXECUTEVOIDRESOLVEUNDEFINEDREJECTT_HPP_
#define _AUXILIARYCLASSES_THEN_MOVEEXECUTEVOIDRESOLVEUNDEFINEDREJECTT_HPP_

#include "Promise.hpp"

class MoveExecuteVoidResolveUndefinedRejectT
{
public:
    MoveExecuteVoidResolveUndefinedRejectT(const MoveExecuteVoidResolveUndefinedRejectT&) = delete;

    explicit MoveExecuteVoidResolveUndefinedRejectT()
    {}

    MoveExecuteVoidResolveUndefinedRejectT(MoveExecuteVoidResolveUndefinedRejectT&& m)
    {}

    void operator()(prm::Rejector<double> reject)
    {
        return reject(5.3);
    }
};

#endif  // _AUXILIARYCLASSES_THEN_MOVEEXECUTEVOIDRESOLVEUNDEFINEDREJECTT_HPP_
