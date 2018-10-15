#ifndef _FINISHER_HPP_
#define _FINISHER_HPP_

#include <utility>

#include "Interfaces/IFinisher.hpp"

namespace prm
{

class Finisher
{
    using IFinisherRPtr = IFinisher*;
public:
    Finisher(IFinisherRPtr finisher)
        : finisher_(finisher)
    {}

    void operator()() const
    {
        finisher_->finish();
    }

private:
     const IFinisherRPtr finisher_;
};

}  // namespace prm

#endif  // _FINISHER_HPP_
