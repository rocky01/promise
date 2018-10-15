#ifndef _AUXILIARYCLASSES_THEN_COPYEXECUTEVOIDRESOLVEUNDEFINEDREJECTT_HPP_
#define _AUXILIARYCLASSES_THEN_COPYEXECUTEVOIDRESOLVEUNDEFINEDREJECTT_HPP_

#include "Promise.hpp"

class CopyExecuteVoidResolveUndefinedRejectT
{
public:
    explicit CopyExecuteVoidResolveUndefinedRejectT()
    {}

    void operator()(prm::Rejector<double> reject)
    {
        return reject(5.3);
    }
};

#endif  // _AUXILIARYCLASSES_THEN_COPYEXECUTEVOIDRESOLVEUNDEFINEDREJECTT_HPP_
