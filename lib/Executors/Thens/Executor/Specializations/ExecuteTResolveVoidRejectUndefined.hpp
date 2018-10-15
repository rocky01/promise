#ifndef _THENEXECUTOR_EXECUTETRESOLVEVOIDREJECTUNDEFINED_HPP_
#define _THENEXECUTOR_EXECUTETRESOLVEVOIDREJECTUNDEFINED_HPP_

#include "Executors/Thens/Executor/ExecuteTResolveTRejectT.hpp"

namespace prm
{

template <
    typename PerformerT,
    typename ExecuteArgT,
    bool IsEmplace,
    typename... PerformerArgsT
>
class ThenExecutor<PerformerT, ExecuteArgT, void, ErrorTypeUndefined, IsEmplace, PerformerArgsT...>
    : public IExecutor<ExecuteArgT>, public IResolver<void>,
      public PromiseExecutor<void, ErrorTypeUndefined>
{
    using pe = PromiseExecutor<void, ErrorTypeUndefined>;
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

private:
    void executeImpl(ExecuteResolver, ExecuteArgT executeArg)
    {
        Resolver<void> resolver(this);
        performer_(executeArg, resolver);
    }

    void executeImpl(ResolverOnly, ExecuteArgT)
    {
        Resolver<void> resolver(this);
        performer_(resolver);
    }

    PerformerT performer_;
};

}  // namespace prm

#endif  // _THENEXECUTOR_EXECUTETRESOLVEVOIDREJECTUNDEFINED_HPP_
