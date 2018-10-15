#ifndef _REJECTOR_HPP_
#define _REJECTOR_HPP_

#include "Interfaces/IRejector.hpp"

namespace prm
{

template<typename ErrorT>
class Rejector
{
    using IRejectorRPtrType = IRejector<ErrorT>*;
public:
    Rejector(IRejectorRPtrType rejector)
        : rejector_(rejector)
    {}

    void operator()(ErrorT error) const
    {
        rejector_->reject(error);
    }

private:
     const IRejectorRPtrType rejector_;
};


template<>
class Rejector<void>
{
    using IRejectorRPtrType = IRejector<void>*;
public:
    Rejector(IRejectorRPtrType rejector)
        : rejector_(rejector)
    {}

    void operator()() const
    {
        rejector_->reject();
    }

private:
     const IRejectorRPtrType rejector_;
};

}  // namespace prm

#endif  // _REJECTOR_HPP_
