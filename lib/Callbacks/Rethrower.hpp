#ifndef _RETHROWER_HPP_
#define _RETHROWER_HPP_

#include "Interfaces/IRethrower.hpp"

namespace prm
{

template<typename ErrorT>
class Rethrower
{
public:
    using IRethrowerRPtrType = IRethrower<ErrorT>*;

    Rethrower(IRethrowerRPtrType rethrower)
        : rethrower_(rethrower)
    {}

    void operator()(ErrorT error) const
    {
        rethrower_->rethrow(error);
    }

private:
     const IRethrowerRPtrType rethrower_;
};


template<>
class Rethrower<void>
{
public:
    using IRethrowerRPtrType = IRethrower<void>*;

    Rethrower(IRethrowerRPtrType rethrower)
        : rethrower_(rethrower)
    {}

    void operator()() const
    {
        rethrower_->rethrow();
    }

private:
     const IRethrowerRPtrType rethrower_;
};

}  // namespace prm

#endif  // _RETHROWER_HPP_
