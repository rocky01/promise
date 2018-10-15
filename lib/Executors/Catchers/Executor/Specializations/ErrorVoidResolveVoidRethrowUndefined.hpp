#ifndef _CATCHEREXECUTOR_EXECUTEVOIDRESOLVEVOIDRETHROWUNDEFINED_HPP_
#define _CATCHEREXECUTOR_EXECUTEVOIDRESOLVEVOIDRETHROWUNDEFINED_HPP_

#include "Executors/Catchers/Executor/ErrorTResolveTRethrowT.hpp"

namespace prm
{

template <
    typename PerformerT,
    bool IsEmplace,
    typename... PerformerArgsT
>
class CatcherExecutor<PerformerT, void, void, ErrorTypeUndefined, IsEmplace, PerformerArgsT...>
    : public IExecutorAndRejector<void, void>,
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

    void reject() override
    {
        pe::state_ = State::InProgress;
        rejectImpl(getOperatorTypeCounterpartForCatcher(&PerformerT::operator()));
    }

private:
    void rejectImpl(ResolverOnly)
    {
        Resolver<void> resolver(this);
        performer_(resolver);
    }

    PerformerT performer_;
};

}  // namespace prm

#endif  // _CATCHEREXECUTOR_EXECUTEVOIDRESOLVEVOIDRETHROWUNDEFINED_HPP_
