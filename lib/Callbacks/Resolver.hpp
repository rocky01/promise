#ifndef _RESOLVER_HPP_
#define _RESOLVER_HPP_

#include <utility>

#include "Interfaces/IResolver.hpp"

namespace prm
{

template<typename ResolverArgT>
class Resolver
{
    using IResolverRPtrType = IResolver<ResolverArgT>*;
public:
    Resolver(IResolverRPtrType resolver)
        : resolver_(resolver)
    {}

    void operator()(ResolverArgT resolverArg) const
    {
        resolver_->resolve(resolverArg);
    }

private:
     const IResolverRPtrType resolver_;
};


template<>
class Resolver<void>
{
    using IResolverRPtrType = IResolver<void>*;
public:
    Resolver(IResolverRPtrType resolver)
        : resolver_(resolver)
    {}

    void operator()() const
    {
        resolver_->resolve();
    }

private:
     const IResolverRPtrType resolver_;
};

}  // namespace prm

#endif  // _RESOLVER_HPP_
