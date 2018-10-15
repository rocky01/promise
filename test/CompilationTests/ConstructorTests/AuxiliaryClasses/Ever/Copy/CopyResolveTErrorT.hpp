#ifndef _AUXILIARYCLASSES_EVER_COPYRESOLVETERRORT_HPP_
#define _AUXILIARYCLASSES_EVER_COPYRESOLVETERRORT_HPP_

#include "Promise.hpp"

class CopyResolveTErrorT
{
public:
    explicit CopyResolveTErrorT()
    {}

    void operator()(prm::Finisher finish) const
    {
        return finish();
    }
};

#endif  // _AUXILIARYCLASSES_EVER_COPYRESOLVETERRORT_HPP_
