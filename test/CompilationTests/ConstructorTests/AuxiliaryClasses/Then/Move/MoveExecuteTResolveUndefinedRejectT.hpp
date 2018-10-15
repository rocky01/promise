#ifndef _AUXILIARYCLASSES_THEN_MOVEEXECUTETRESOLVEUNDEFINEDREJECTT_HPP_
#define _AUXILIARYCLASSES_THEN_MOVEEXECUTETRESOLVEUNDEFINEDREJECTT_HPP_

#include "Promise.hpp"

class MoveExecuteTResolveUndefinedRejectT
{
public:
    MoveExecuteTResolveUndefinedRejectT(const MoveExecuteTResolveUndefinedRejectT&) = delete;

    explicit MoveExecuteTResolveUndefinedRejectT()
    {}

    MoveExecuteTResolveUndefinedRejectT(MoveExecuteTResolveUndefinedRejectT&& m)
    {}

    void operator()(int e, prm::Rejector<double> reject) {
        return reject(5.3);
    }
};

#endif  // _AUXILIARYCLASSES_THEN_MOVEEXECUTETRESOLVEUNDEFINEDREJECTT_HPP_
