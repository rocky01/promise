#ifndef _AUXILIARYCLASSES_THEN_EMPLACEEXECUTEVOIDRESOLVEUNDEFINEDREJECTT_HPP_
#define _AUXILIARYCLASSES_THEN_EMPLACEEXECUTEVOIDRESOLVEUNDEFINEDREJECTT_HPP_

#include "Promise.hpp"

class EmplaceExecuteVoidResolveUndefinedRejectT
{
public:
    EmplaceExecuteVoidResolveUndefinedRejectT(const EmplaceExecuteVoidResolveUndefinedRejectT&) = delete;
    EmplaceExecuteVoidResolveUndefinedRejectT(const EmplaceExecuteVoidResolveUndefinedRejectT&&) = delete;

    explicit EmplaceExecuteVoidResolveUndefinedRejectT()
    {}

    void operator()(prm::Rejector<double> reject)
    {
        return reject(5.3);
    }
};

#endif  // _AUXILIARYCLASSES_THEN_EMPLACEEXECUTEVOIDRESOLVEUNDEFINEDREJECTT_HPP_
