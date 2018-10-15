#ifndef _THENEXECUTOR_EXECUTETRESOLVETREJECTT_HPP_
#define _THENEXECUTOR_EXECUTETRESOLVETREJECTT_HPP_

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>
#include <type_traits>

#include "Helpers/TypesDefinitions.hpp"
#include "Helpers/CallOperatorTypeDeduction.hpp"
#include "Callbacks/Resolver.hpp"
#include "Callbacks/Rejector.hpp"
#include "Interfaces/IExecutor.hpp"
#include "Interfaces/IExecutorAndRejector.hpp"
#include "PromiseExecutor.hpp"


namespace prm
{

template <
    typename PerformerT,
    typename ExecuteArgT,
    typename ResolveArgT,
    typename ErrorT,
    bool IsEmplace = false,
    typename... PerformerArgsT
>
class ThenExecutor
    : public IExecutorAndRejector<ExecuteArgT, ErrorT>, public IResolver<ResolveArgT>,
      public PromiseExecutor<ResolveArgT, ErrorT>
{
    using pe = PromiseExecutor<ResolveArgT, ErrorT>;
    using PerformerType = PerformerT; // only for enable if
public:
    ENABLE_IF_IS_NOT_EMPLACE(PerformerType, IsEmplace)
    ThenExecutor(PerformerT&& performer)
        : performer_(std::forward<PerformerT>(performer))
    {}

    ENABLE_IF_IS_EMPLACE(PerformerType, IsEmplace)
    ThenExecutor(PerformerArgsT&&... performerArgs)
        : performer_(std::forward<PerformerArgsT>(performerArgs)...)
    {}

    void execute(ExecuteArgT executeArg) override
    {
        pe::state_ = State::InProgress;
        executeImpl(getOperatorTypeCounterpartForExecutor(&PerformerT::operator()), executeArg);
    }

    void resolve(ResolveArgT resolveArg) override
    {
        pe::state_ = State::Resolved;
        if (pe::nextPromiseExecutor_)
        {
            pe::nextPromiseExecutor_->execute(resolveArg);
        }
    }

    void reject(ErrorT error) override
    {
        pe::state_ = State::Rejected;
        if (pe::nextPromiseExecutor_)
        {
            pe::nextPromiseExecutor_->reject(error);
        }
    }

private:
    void executeImpl(ExecuteResolverRejector, ExecuteArgT executeArg)
    {
        Resolver<ResolveArgT> resolver(this);
        Rejector<ErrorT> rejector(this);
        performer_(executeArg, resolver, rejector);
    }

    void executeImpl(ExecuteResolver, ExecuteArgT executeArg)
    {
        Resolver<ResolveArgT> resolver(this);
        performer_(executeArg, resolver);
    }

    void executeImpl(ResolverRejector, ExecuteArgT)
    {
        Resolver<ResolveArgT> resolver(this);
        Rejector<ErrorT> rejector(this);
        performer_(resolver, rejector);
    }

    void executeImpl(ResolverOnly, ExecuteArgT)
    {
        Resolver<ResolveArgT> resolver(this);
        performer_(resolver);
    }

    PerformerT performer_;
};

}  // namespace prm

#endif  // _THENEXECUTOR_EXECUTETRESOLVETREJECTT_HPP_
