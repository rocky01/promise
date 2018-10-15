#ifndef _EVEREXECUTOR_RESOLVEVOIDERRORT_HPP_
#define _EVEREXECUTOR_RESOLVEVOIDERRORT_HPP_

#include "Executors/Evers/Executor/ResolveTErrorT.hpp"

namespace prm
{

template <
    typename PerformerT,
    typename ErrorT,
    bool IsEmplace,
    typename... PerformerArgsT
>
class EverExecutor<PerformerT, void, ErrorT, IsEmplace, PerformerArgsT...>
    : public IExecutorAndRejector<void, ErrorT>,
      public IFinisher,
      public PromiseExecutor<void, ErrorT>
{
    using pe = PromiseExecutor<void, ErrorT>;
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
        reporter_ = std::make_unique<Reporter<void, ErrorT>>();
        impl(getOperatorTypeCounterpartForEver(&PerformerT::operator()));
    }

    void reject(ErrorT error) override
    {
        pe::state_ = State::InProgress;
        reporter_ = std::make_unique<Reporter<void, ErrorT>>(error);
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
                pe::nextPromiseExecutor_->reject(reporter_->getError());
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

    std::unique_ptr<Reporter<void, ErrorT>> reporter_;
    PerformerT performer_;
};

}  // namespace prm

#endif  // _EVEREXECUTOR_RESOLVEVOIDERRORT_HPP_
