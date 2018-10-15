#ifndef _AUXILIARYCLASSES_EVER_EMPLACERESOLVETERRORT_HPP_
#define _AUXILIARYCLASSES_EVER_EMPLACERESOLVETERRORT_HPP_

#include "Promise.hpp"

class EmplaceResolveTErrorT
{
public:
    EmplaceResolveTErrorT(const EmplaceResolveTErrorT&) = delete;
    EmplaceResolveTErrorT(const EmplaceResolveTErrorT&&) = delete;

    explicit EmplaceResolveTErrorT()
    {}

    void operator()(prm::Finisher finish) const
    {
        return finish();
    }
};

#endif  // _AUXILIARYCLASSES_EVER_EMPLACERESOLVETERRORT_HPP_
