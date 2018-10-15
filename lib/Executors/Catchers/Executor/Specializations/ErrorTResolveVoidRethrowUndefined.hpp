#ifndef _CATCHEREXECUTOR_EXECUTETRESOLVEVOIDRETHROWUNDEFINED_HPP_
#define _CATCHEREXECUTOR_EXECUTETRESOLVEVOIDRETHROWUNDEFINED_HPP_

#include "Executors/Catchers/Executor/ErrorTResolveTRethrowT.hpp"

namespace prm
{

template <
    typename PerformerT,
    typename ErrorT,
    bool IsEmplace,
    typename... PerformerArgsT
>
class CatcherExecutor<PerformerT, ErrorT, void, ErrorTypeUndefined, IsEmplace, PerformerArgsT...>
    : public IExecutorAndRejector<void, ErrorT>,
      public IResolver<void>,
      public PromiseExecutor<void, ErrorTypeUndefined>
{
    using pe = PromiseExecutor<void, ErrorTypeUndefined>;
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

    void execute() override
    {
        resolve();
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
        pe::state_ = State::InProgress;
        rejectImpl(getOperatorTypeCounterpartForCatcher(&PerformerT::operator()), error);
    }

private:
    void rejectImpl(ErrorResolver, ErrorT error)
    {
        Resolver<void> resolver(this);
        performer_(error, resolver);
    }

    void rejectImpl(ResolverOnly, ErrorT)
    {
        Resolver<void> resolver(this);
        performer_(resolver);
    }

    PerformerT performer_;
};

}  // namespace prm

#endif  // _CATCHEREXECUTOR_EXECUTETRESOLVEVOIDRETHROWUNDEFINED_HPP_
