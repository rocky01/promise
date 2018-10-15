#ifndef _EVEREXECUTOR_RESOLVETERRORVOID_HPP_
#define _EVEREXECUTOR_RESOLVETERRORVOID_HPP_

#include "Executors/Evers/Executor/ResolveTErrorT.hpp"

namespace prm
{

template <
    typename PerformerT,
    typename ResolveArgT,
    bool IsEmplace,
    typename... PerformerArgsT
>
class EverExecutor<PerformerT, ResolveArgT, void, IsEmplace, PerformerArgsT...>
    : public IExecutorAndRejector<ResolveArgT, void>,
      public IFinisher,
      public PromiseExecutor<ResolveArgT, void>
{
    using pe = PromiseExecutor<ResolveArgT, void>;
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

    void execute(ResolveArgT executeArg) override
    {
        pe::state_ = State::InProgress;
        reporter_ = std::make_unique<Reporter<ResolveArgT, void>>(executeArg);
        impl(getOperatorTypeCounterpartForEver(&PerformerT::operator()));
    }

    void reject() override
    {
        pe::state_ = State::InProgress;
        reporter_ = std::make_unique<Reporter<ResolveArgT, void>>();
        impl(getOperatorTypeCounterpartForEver(&PerformerT::operator()));
    }

    void finish() override
    {
        if (reporter_->isResolved())
        {
            pe::state_ = State::Resolved;
            if (pe::nextPromiseExecutor_)
            {
               pe::nextPromiseExecutor_->execute(reporter_->getResolveArg());
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

    std::unique_ptr<Reporter<ResolveArgT, void>> reporter_;
    PerformerT performer_;
};

}  // namespace prm

#endif  // _EVEREXECUTOR_RESOLVETERRORVOID_HPP_
