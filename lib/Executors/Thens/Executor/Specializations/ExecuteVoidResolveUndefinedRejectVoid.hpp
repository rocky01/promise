#ifndef _THENEXECUTOR_EXECUTEVOIDRESOLVEUNDEFINEDREJECTVOID_HPP_
#define _THENEXECUTOR_EXECUTEVOIDRESOLVEUNDEFINEDREJECTVOID_HPP_

#include "Executors/Thens/Executor/ExecuteTResolveTRejectT.hpp"

namespace prm
{

template <
    typename PerformerT,
    bool IsEmplace,
    typename... PerformerArgsT
>
class ThenExecutor<PerformerT, void, ResolveArgTypeUndefined, void, IsEmplace, PerformerArgsT...>
    : public IExecutorAndRejector<void, void>,
      public PromiseExecutor<ResolveArgTypeUndefined, void>
{
    using pe = PromiseExecutor<ResolveArgTypeUndefined, void>;
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

    void execute() override
    {
        pe::state_ = State::InProgress;
        executeImpl(getOperatorTypeCounterpartForExecutor(&PerformerT::operator()));
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
    void executeImpl(RejectorOnly)
    {
        Rejector<void> rejector(this);
        performer_(rejector);
    }

    PerformerT performer_;
};

}  // namespace prm

#endif  // _THENEXECUTOR_EXECUTEVOIDRESOLVEUNDEFINEDREJECTVOID_HPP_
