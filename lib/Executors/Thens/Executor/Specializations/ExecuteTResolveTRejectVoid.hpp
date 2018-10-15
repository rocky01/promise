#ifndef _THENEXECUTOR_EXECUTETRESOLVETREJECTVOID_HPP_
#define _THENEXECUTOR_EXECUTETRESOLVETREJECTVOID_HPP_

#include "Executors/Thens/Executor/ExecuteTResolveTRejectT.hpp"

namespace prm
{

template <
    typename PerformerT,
    typename ExecuteArgT,
    typename ResolveArgT,
    bool IsEmplace,
    typename... PerformerArgsT
>
class ThenExecutor<PerformerT, ExecuteArgT, ResolveArgT, void, IsEmplace, PerformerArgsT...>
    : public IExecutorAndRejector<ExecuteArgT, void>, public IResolver<ResolveArgT>,
      public PromiseExecutor<ResolveArgT, void>
{
    using pe = PromiseExecutor<ResolveArgT, void>;
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

    void reject() override
    {
        pe::state_ = State::Rejected;
        if (pe::nextPromiseExecutor_)
        {
            pe::nextPromiseExecutor_->reject();
        }
    }

private:
    void executeImpl(ExecuteResolverRejector, ExecuteArgT executeArg)
    {
        Resolver<ResolveArgT> resolver(this);
        Rejector<void> rejector(this);
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
        Rejector<void> rejector(this);
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

#endif  // _THENEXECUTOR_EXECUTETRESOLVETREJECTVOID_HPP_
