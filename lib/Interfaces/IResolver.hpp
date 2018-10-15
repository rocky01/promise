#ifndef _IRESOLVER_HPP_
#define _IRESOLVER_HPP_

#include <memory>

#include "Helpers/TypesDefinitions.hpp"

namespace prm
{

template<typename ResolveArgT>
class IResolver
{
public:
    virtual ~IResolver(){}
    virtual void resolve(ResolveArgT resolveArg) =0;
};

template<>
class IResolver<void>
{
public:
    virtual ~IResolver(){}
    virtual void resolve() =0;
};

template<typename ResolveArgT>
using IResolverUPtr = std::unique_ptr<IResolver<ResolveArgT>>;

}  // namespace prm

#endif  // _IRESOLVER_HPP_

