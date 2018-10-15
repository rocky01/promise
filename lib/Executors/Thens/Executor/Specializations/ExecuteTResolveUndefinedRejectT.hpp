#ifndef _THENEXECUTOR_EXECUTETRESOLVEUNDEFINEDREJECTT_HPP_
#define _THENEXECUTOR_EXECUTETRESOLVEUNDEFINEDREJECTT_HPP_

#include "Executors/Thens/Executor/ExecuteTResolveTRejectT.hpp"

namespace prm
{

template <
    typename PerformerT,
    typename ExecuteArgT,
    typename ErrorT,
    bool IsEmplace,
    typename... PerformerArgsT
>
class ThenExecutor<PerformerT, ExecuteArgT, ResolveArgTypeUndefined, ErrorT, IsEmplace, PerformerArgsT...>
    : public IExecutorAndRejector<ExecuteArgT, ErrorT>,
      public PromiseExecutor<ResolveArgTypeUndefined, ErrorT>
{
    using pe = PromiseExecutor<ResolveArgTypeUndefined, ErrorT>;
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

    void execute(ExecuteArgT executeArg) override
    {
        pe::state_ = State::InProgress;
        executeImpl(getOperatorTypeCounterpartForExecutor(&PerformerT::operator()), executeArg);
    }

    void reject(ErrorT error) override
    {
        pe::state_ = State::Rejected;
        if (pe::nextPromiseExecutor_)
        {
            pe::nextPromiseExecutor_->reject(error);
        }
    }

private:
    void executeImpl(ExecuteRejector, ExecuteArgT executeArg)
    {
        Rejector<ErrorT> rejector(this);
        performer_(executeArg, rejector);
    }

    void executeImpl(RejectorOnly, ExecuteArgT)
    {
        Rejector<ErrorT> rejector(this);
        performer_(rejector);
    }

    PerformerT performer_;
};

}  // namespace prm

#endif  // _THENEXECUTOR_EXECUTETRESOLVEUNDEFINEDREJECTT_HPP_
