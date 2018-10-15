#ifndef _THENEXECUTOR_EXECUTETRESOLVEVOIDREJECTT_HPP_
#define _THENEXECUTOR_EXECUTETRESOLVEVOIDREJECTT_HPP_

#include "Executors/Thens/Executor/ExecuteTResolveTRejectT.hpp"

namespace prm
{

template <
    typename PerformerT,
    typename ExecuteArgT,
    typename ErrorT,
    bool IsEmplace,
    typename... PerformerArgsT
>
class ThenExecutor<PerformerT, ExecuteArgT, void, ErrorT, IsEmplace, PerformerArgsT...>
    : public IExecutorAndRejector<ExecuteArgT, ErrorT>, public IResolver<void>,
      public PromiseExecutor<void, ErrorT>
{
    using pe = PromiseExecutor<void, ErrorT>;
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

    void resolve() override
    {
        pe::state_ = State::Resolved;
        if (pe::nextPromiseExecutor_)
        {
            pe::nextPromiseExecutor_->execute();
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
        Resolver<void> resolver(this);
        Rejector<ErrorT> rejector(this);
        performer_(executeArg, resolver, rejector);
    }

    void executeImpl(ExecuteResolver, ExecuteArgT executeArg)
    {
        Resolver<void> resolver(this);
        performer_(executeArg, resolver);
    }

    void executeImpl(ResolverRejector, ExecuteArgT)
    {
        Resolver<void> resolver(this);
        Rejector<ErrorT> rejector(this);
        performer_(resolver, rejector);
    }

    void executeImpl(ResolverOnly, ExecuteArgT)
    {
        Resolver<void> resolver(this);
        performer_(resolver);
    }

    PerformerT performer_;
};

}  // namespace prm

#endif  // _THENEXECUTOR_EXECUTETRESOLVEVOIDREJECTT_HPP_
