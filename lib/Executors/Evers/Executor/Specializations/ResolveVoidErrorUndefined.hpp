#ifndef _EVEREXECUTOR_EXECUTEVOIDRESOLVEVOIDERRORUNDEFINED_HPP_
#define _EVEREXECUTOR_EXECUTEVOIDRESOLVEVOIDERRORUNDEFINED_HPP_

#include "Executors/Evers/Executor/ResolveTErrorT.hpp"

namespace prm
{

template <
    typename PerformerT,
    bool IsEmplace,
    typename... PerformerArgsT
>
class EverExecutor<PerformerT, void, ErrorTypeUndefined, IsEmplace, PerformerArgsT...>
    : public IExecutor<void>,
      public IFinisher,
      public PromiseExecutor<void, ErrorTypeUndefined>
{
    using pe = PromiseExecutor<void, ErrorTypeUndefined>;
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

    void execute() override
    {
        pe::state_ = State::InProgress;
        reporter_ = std::make_unique<Reporter<void, ErrorTypeUndefined>>();
        impl(getOperatorTypeCounterpartForEver(&PerformerT::operator()));
    }

    void finish() override
    {
        pe::state_ = State::Resolved;
        if (pe::nextPromiseExecutor_)
        {
           pe::nextPromiseExecutor_->execute();
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

    std::unique_ptr<Reporter<void, ErrorTypeUndefined>> reporter_;
    PerformerT performer_;
};

}  // namespace prm

#endif  // _EVEREXECUTOR_EXECUTEVOIDRESOLVEVOIDERRORUNDEFINED_HPP_
