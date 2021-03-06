#ifndef _CATCHEREXECUTOR_EXECUTEVOIDRESOLVEUNDEFINEDRETHROWVOID_HPP_
#define _CATCHEREXECUTOR_EXECUTEVOIDRESOLVEUNDEFINEDRETHROWVOID_HPP_

#include "Executors/Catchers/Executor/ErrorTResolveTRethrowT.hpp"

namespace prm
{

template <
    typename PerformerT,
    bool IsEmplace,
    typename... PerformerArgsT
>
class CatcherExecutor<PerformerT, void, ResolveArgTypeUndefined, void, IsEmplace, PerformerArgsT...>
    : public IRejector<void>,
      public IRethrower<void>,
      public PromiseExecutor<ResolveArgTypeUndefined, void>
{
    using pe = PromiseExecutor<ResolveArgTypeUndefined, void>;
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

    void reject() override
    {
        pe::state_ = State::InProgress;
        rejectImpl(getOperatorTypeCounterpartForCatcher(&PerformerT::operator()));
    }

    void rethrow() override
    {
        pe::state_ = State::Rejected;
        if (pe::nextPromiseExecutor_)
        {
            pe::nextPromiseExecutor_->reject();
        }
    }

private:
    void rejectImpl(RethrowerOnly)
    {
        Rethrower<void> rethrower(this);
        performer_(rethrower);
    }

    PerformerT performer_;
};

}  // namespace prm

#endif  // _CATCHEREXECUTOR_EXECUTEVOIDRESOLVEUNDEFINEDRETHROWVOID_HPP_
