#ifndef _AUXILIARYCLASSES_THEN_EMPLACEEXECUTETRESOLVETREJECTT_HPP_
#define _AUXILIARYCLASSES_THEN_EMPLACEEXECUTETRESOLVETREJECTT_HPP_

#include "Promise.hpp"

class EmplaceExecuteTResolveTRejectT
{
public:
    EmplaceExecuteTResolveTRejectT(const EmplaceExecuteTResolveTRejectT&) = delete;
    EmplaceExecuteTResolveTRejectT(const EmplaceExecuteTResolveTRejectT&&) = delete;

    explicit EmplaceExecuteTResolveTRejectT(bool isResolved)
        : isResolved_(isResolved)
    {}

    void operator()(int e, prm::Resolver<char> resolve, prm::Rejector<double> reject)
    {
        return isResolved_ ? resolve('w') : reject(5.3);
    }

private:
    bool isResolved_;
};

#endif  // _AUXILIARYCLASSES_THEN_EMPLACEEXECUTETRESOLVETREJECTT_HPP_
