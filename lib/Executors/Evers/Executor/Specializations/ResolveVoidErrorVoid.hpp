#ifndef _EVEREXECUTOR_RESOLVEVOIDERRORVOID_HPP_
#define _EVEREXECUTOR_RESOLVEVOIDERRORVOID_HPP_

#include "Executors/Evers/Executor/ResolveTErrorT.hpp"

namespace prm
{

template <
    typename PerformerT,
    bool IsEmplace,
    typename... PerformerArgsT
>
class EverExecutor<PerformerT, void, void, IsEmplace, PerformerArgsT...>
    : public IExecutorAndRejector<void, void>,
      public IFinisher,
      public PromiseExecutor<void, void>
{
    using pe = PromiseExecutor<void, void>;
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
        reporter_ = std::make_unique<Reporter<void, void>>(Is::Resolved);
        impl(getOperatorTypeCounterpartForEver(&PerformerT::operator()));
    }

    void reject() override
    {
        pe::state_ = State::InProgress;
        reporter_ = std::make_unique<Reporter<void, void>>(Is::Rejected);
        impl(getOperatorTypeCounterpartForEver(&PerformerT::operator()));
    }

    void finish() override
    {
        if (reporter_->isResolved())
        {
            pe::state_ = State::Resolved;
            if (pe::nextPromiseExecutor_)
            {
               pe::nextPromiseExecutor_->execute();
            }
        }
        else
        {
            pe::state_ = State::Rejected;
            if (pe::nextPromiseExecutor_)
            {
                pe::nextPromiseExecutor_->reject();
            }
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

    std::unique_ptr<Reporter<void, void>> reporter_;
    PerformerT performer_;
};


}  // namespace prm

#endif  // _EVEREXECUTOR_RESOLVEVOIDERRORVOID_HPP_
