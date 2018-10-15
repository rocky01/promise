#ifndef _EVEREXECUTOR_RESOLVETERRORT_HPP_
#define _EVEREXECUTOR_RESOLVETERRORT_HPP_

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>
#include <type_traits>

#include "Helpers/TypesDefinitions.hpp"
#include "Helpers/CallOperatorTypeDeduction.hpp"
#include "Callbacks/Reporter.hpp"
#include "Callbacks/Finisher.hpp"
#include "Interfaces/IFinisher.hpp"
#include "PromiseExecutor.hpp"


namespace prm
{

template <
    typename PerformerT,
    typename ResolveArgT,
    typename ErrorT,
    bool IsEmplace = false,
    typename... PerformerArgsT
>
class EverExecutor
    : public IExecutorAndRejector<ResolveArgT, ErrorT>,
      public IFinisher,
      public PromiseExecutor<ResolveArgT, ErrorT>
{
    using pe = PromiseExecutor<ResolveArgT, ErrorT>;
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
        reporter_ = std::make_unique<Reporter<ResolveArgT, ErrorT>>(executeArg);
        impl(getOperatorTypeCounterpartForEver(&PerformerT::operator()));
    }

    void reject(ErrorT error) override
    {
        pe::state_ = State::InProgress;
        reporter_ = std::make_unique<Reporter<ResolveArgT, ErrorT>>(error, true);
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

    std::unique_ptr<Reporter<ResolveArgT, ErrorT>> reporter_;
    PerformerT performer_;
};

}  // namespace prm

#endif  // _EVEREXECUTOR_RESOLVETERRORT_HPP_
