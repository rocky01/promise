#ifndef _AUXILIARYCLASSES_THEN_EMPLACEEXECUTEVOIDRESOLVEVOIDREJECTT_HPP_
#define _AUXILIARYCLASSES_THEN_EMPLACEEXECUTEVOIDRESOLVEVOIDREJECTT_HPP_

#include "Promise.hpp"

class EmplaceExecuteVoidResolveVoidRejectT
{
public:
    EmplaceExecuteVoidResolveVoidRejectT(const EmplaceExecuteVoidResolveVoidRejectT&) = delete;
    EmplaceExecuteVoidResolveVoidRejectT(const EmplaceExecuteVoidResolveVoidRejectT&&) = delete;

    explicit EmplaceExecuteVoidResolveVoidRejectT(bool isResolved)
        : isResolved_(isResolved)
    {}

    void operator()(prm::Resolver<void> resolve, prm::Rejector<double> reject)
    {
        return isResolved_ ? resolve() : reject(5.3);
    }

private:
    bool isResolved_;
};

#endif  // _AUXILIARYCLASSES_THEN_EMPLACEEXECUTEVOIDRESOLVEVOIDREJECTT_HPP_
