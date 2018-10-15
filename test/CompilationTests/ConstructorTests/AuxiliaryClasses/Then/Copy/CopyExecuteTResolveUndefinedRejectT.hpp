#ifndef _AUXILIARYCLASSES_THEN_COPYEXECUTETRESOLVEUNDEFINEDREJECTT_HPP_
#define _AUXILIARYCLASSES_THEN_COPYEXECUTETRESOLVEUNDEFINEDREJECTT_HPP_

#include "Promise.hpp"

class CopyExecuteTResolveUndefinedRejectT
{
public:
    explicit CopyExecuteTResolveUndefinedRejectT()
    {}

    void operator()(int e, prm::Rejector<double> reject) {
        return reject(5.3);
    }
};

#endif  // _AUXILIARYCLASSES_THEN_COPYEXECUTETRESOLVEUNDEFINEDREJECTT_HPP_
