#ifndef _CATCHEREXECUTOR_EXECUTETRESOLVETREJECTT_HPP_
#define _CATCHEREXECUTOR_EXECUTETRESOLVETREJECTT_HPP_

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>
#include <type_traits>

#include "Helpers/TypesDefinitions.hpp"
#include "Helpers/CallOperatorTypeDeduction.hpp"
#include "Callbacks/Resolver.hpp"
#include "Callbacks/Rethrower.hpp"
#include "Interfaces/IResolver.hpp"
#include "Interfaces/IRethrower.hpp"
#include "Interfaces/IExecutorAndRejector.hpp"
#include "PromiseExecutor.hpp"


namespace prm
{

template <
    typename PerformerT,
    typename ErrorT,
    typename ExecuteResolveArgT,
    typename RethrowErrorT,
    bool IsEmplace = false,
    typename... PerformerArgsT
>
class CatcherExecutor
    : public IExecutorAndRejector<ExecuteResolveArgT, ErrorT>,
      public IResolver<ExecuteResolveArgT>,
      public IRethrower<RethrowErrorT>,
      public PromiseExecutor<ExecuteResolveArgT, RethrowErrorT>
{
    using pe = PromiseExecutor<ExecuteResolveArgT, RethrowErrorT>;
    using PerformerType = PerformerT; // only for enable if
public:
    ENABLE_IF_IS_NOT_EMPLACE(PerformerType, IsEmplace)
    CatcherExecutor(PerformerT&& performer)
        : performer_(std::forward<PerformerT>(performer))
    {}

    ENABLE_IF_IS_EMPLACE(PerformerType, IsEmplace)
    CatcherExecutor(PerformerArgsT&&... performerArgs)
        : performer_(std::forward<PerformerArgsT>(performerArgs)...)
    {}

    void execute(ExecuteResolveArgT executeArg) override
    {
        resolve(executeArg);
    }

    void resolve(ExecuteResolveArgT resolveArg) override
    {
        pe::state_ = State::Resolved;
        if (pe::nextPromiseExecutor_)
        {
            pe::nextPromiseExecutor_->execute(resolveArg);
        }
    }

    void reject(ErrorT error) override
    {
        pe::state_ = State::InProgress;
        rejectImpl(getOperatorTypeCounterpartForCatcher(&PerformerT::operator()), error);
    }

    void rethrow(RethrowErrorT rethrowArg) override
    {
        pe::state_ = State::Rejected;
        if (pe::nextPromiseExecutor_)
        {
            pe::nextPromiseExecutor_->reject(rethrowArg);
        }
    }

private:
    void rejectImpl(ErrorResolverRethrower, ErrorT error)
    {
        Resolver<ExecuteResolveArgT> resolver(this);
        Rethrower<RethrowErrorT> rethrower(this);
        performer_(error, resolver, rethrower);
    }

    void rejectImpl(ErrorRethrower, ErrorT error)
    {
        Rethrower<RethrowErrorT> rethrower(this);
        performer_(error, rethrower);
    }

    void rejectImpl(ResolverRethrower, ErrorT)
    {
        Resolver<ExecuteResolveArgT> resolver(this);
        Rethrower<RethrowErrorT> rethrower(this);
        performer_(resolver, rethrower);
    }

    void rejectImpl(RethrowerOnly, ErrorT)
    {
        Rethrower<RethrowErrorT> rethrower(this);
        performer_(rethrower);
    }

    PerformerT performer_;
};

}  // namespace prm

#endif  // _CATCHEREXECUTOR_EXECUTETRESOLVETREJECTT_HPP_
