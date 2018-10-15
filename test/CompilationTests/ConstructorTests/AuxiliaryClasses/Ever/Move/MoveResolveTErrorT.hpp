#ifndef _AUXILIARYCLASSES_EVER_MOVERESOLVETERRORT_HPP_
#define _AUXILIARYCLASSES_EVER_MOVERESOLVETERRORT_HPP_

#include "Promise.hpp"

class MoveResolveTErrorT
{
public:
    MoveResolveTErrorT(const MoveResolveTErrorT&) = delete;

    explicit MoveResolveTErrorT()
    {}

    MoveResolveTErrorT(MoveResolveTErrorT&&)
    {}

    void operator()(prm::Finisher finish) const
    {
        return finish();
    }
};

#endif  // _AUXILIARYCLASSES_EVER_MOVERESOLVETERRORT_HPP_
