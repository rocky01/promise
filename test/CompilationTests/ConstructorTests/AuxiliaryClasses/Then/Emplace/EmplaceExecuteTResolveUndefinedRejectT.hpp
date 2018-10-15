#ifndef _AUXILIARYCLASSES_THEN_EMPLACEEXECUTETRESOLVEUNDEFINEDREJECTT_HPP_
#define _AUXILIARYCLASSES_THEN_EMPLACEEXECUTETRESOLVEUNDEFINEDREJECTT_HPP_

#include "Promise.hpp"

class EmplaceExecuteTResolveUndefinedRejectT
{
public:
    EmplaceExecuteTResolveUndefinedRejectT(const EmplaceExecuteTResolveUndefinedRejectT&) = delete;
    EmplaceExecuteTResolveUndefinedRejectT(const EmplaceExecuteTResolveUndefinedRejectT&&) = delete;

    explicit EmplaceExecuteTResolveUndefinedRejectT()
    {}

    void operator()(int e, prm::Rejector<double> reject) {
        return reject(5.3);
    }
};

#endif  // _AUXILIARYCLASSES_THEN_EMPLACEEXECUTETRESOLVEUNDEFINEDREJECTT_HPP_
