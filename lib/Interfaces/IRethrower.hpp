#ifndef _IRETHROWER_HPP_
#define _IRETHROWER_HPP_

#include <memory>

namespace prm
{

template<typename ErrorT>
class IRethrower
{
public:
    virtual ~IRethrower(){}
    virtual void rethrow(ErrorT error) =0;
};

template<>
class IRethrower<void>
{
public:
    virtual ~IRethrower(){}
    virtual void rethrow() =0;
};

template<typename ErrorT>
using IRethrowerUPtr = std::unique_ptr<IRethrower<ErrorT>>;

}  // namespace prm

#endif  // _IREJECTOR_HPP_

