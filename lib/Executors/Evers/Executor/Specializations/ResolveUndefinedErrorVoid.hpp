#ifndef _EVEREXECUTOR_EXECUTEVOIDRESOLVEUNDEFINEDERRORVOID_HPP_
#define _EVEREXECUTOR_EXECUTEVOIDRESOLVEUNDEFINEDERRORVOID_HPP_

#include "Executors/Evers/Executor/ResolveTErrorT.hpp"

namespace prm
{

template <
    typename PerformerT,
    bool IsEmplace,
    typename... PerformerArgsT
>
class EverExecutor<PerformerT, ResolveArgTypeUndefined, void, IsEmplace, PerformerArgsT...>
    : public IRejector<void>,
      public IFinisher,
      public PromiseExecutor<ResolveArgTypeUndefined, void>
{
    using pe = PromiseExecutor<ResolveArgTypeUndefined, void>;
    using PerformerType = PerformerT; // only for enable if
public:
    ENABLE_IF_IS_NOT_EMPLACE(PerformerType, IsEmplace)
    EverExecutor(PerformerT&& performer)
        : performer_(std::forward<PerformerT>(performer))
    {}

    ENABLE_IF_IS_EMPLACE(PerformerType, IsEmplace)
    EverExecutor(PerformerArgsT&&... performerArgs)
        : performer_(std::forward<PerformerArgsT>(performerArgs)...)
    {}

    void reject() override
    {
        pe::state_ = State::InProgress;
        reporter_ = std::make_unique<Reporter<ResolveArgTypeUndefined, void>>();
        impl(getOperatorTypeCounterpartForEver(&PerformerT::operator()));
    }

    void finish() override
    {
        pe::state_ = State::Rejected;
        if (pe::nextPromiseExecutor_)
        {
            pe::nextPromiseExecutor_->reject();
        }
    }

private:
    void impl(FinisherReporter)
    {
        Finisher finisher(this);
        performer_(finisher, *reporter_);
    }

    void impl(FinisherOnly)
    {
        Finisher finisher(this);
        performer_(finisher);
    }

    std::unique_ptr<Reporter<ResolveArgTypeUndefined, void>> reporter_;
    PerformerT performer_;
};

}  // namespace prm

#endif  // _EVEREXECUTOR_EXECUTEVOIDRESOLVEUNDEFINEDERRORVOID_HPP_
