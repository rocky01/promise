#ifndef _EVEREXECUTOR_RESOLVETERRORUNDEFINED_HPP_
#define _EVEREXECUTOR_RESOLVETERRORUNDEFINED_HPP_

#include "Executors/Evers/Executor/ResolveTErrorT.hpp"

namespace prm
{

template <
    typename PerformerT,
    typename ResolveArgT,
    bool IsEmplace,
    typename... PerformerArgsT
>
class EverExecutor<PerformerT, ResolveArgT, ErrorTypeUndefined, IsEmplace, PerformerArgsT...>
    : public IExecutor<ResolveArgT>,
      public IFinisher,
      public PromiseExecutor<ResolveArgT, ErrorTypeUndefined>
{
    using pe = PromiseExecutor<ResolveArgT, ErrorTypeUndefined>;
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
        reporter_ = std::make_unique<Reporter<ResolveArgT, ErrorTypeUndefined>>(executeArg);
        impl(getOperatorTypeCounterpartForEver(&PerformerT::operator()));
    }

    void finish() override
    {
        pe::state_ = State::Resolved;
        if (pe::nextPromiseExecutor_)
        {
           pe::nextPromiseExecutor_->execute(reporter_->getResolveArg());
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

    std::unique_ptr<Reporter<ResolveArgT, ErrorTypeUndefined>> reporter_;
    PerformerT performer_;
};

}  // namespace prm

#endif  // _EVEREXECUTOR_RESOLVETERRORUNDEFINED_HPP_
