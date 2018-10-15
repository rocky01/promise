#ifndef _THENEXECUTOR_EXECUTETRESOLVETREJECTUNDEFINED_HPP_
#define _THENEXECUTOR_EXECUTETRESOLVETREJECTUNDEFINED_HPP_

#include "Executors/Thens/Executor/ExecuteTResolveTRejectT.hpp"

namespace prm
{

template <
    typename PerformerT,
    typename ExecuteArgT,
    typename ResolveArgT,
    bool IsEmplace,
    typename... PerformerArgsT
>
class ThenExecutor<PerformerT, ExecuteArgT, ResolveArgT, ErrorTypeUndefined, IsEmplace, PerformerArgsT...>
    : public IExecutor<ExecuteArgT>, public IResolver<ResolveArgT>,
      public PromiseExecutor<ResolveArgT, ErrorTypeUndefined>
{
    using pe = PromiseExecutor<ResolveArgT, ErrorTypeUndefined>;
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

    void resolve(ResolveArgT resolveArg) override
    {
        pe::state_ = State::Resolved;
        if (pe::nextPromiseExecutor_)
        {
            pe::nextPromiseExecutor_->execute(resolveArg);
        }
    }

private:
    void executeImpl(ExecuteResolver, ExecuteArgT executeArg)
    {
        Resolver<ResolveArgT> resolver(this);
        performer_(executeArg, resolver);
    }

    void executeImpl(ResolverOnly, ExecuteArgT)
    {
        Resolver<ResolveArgT> resolver(this);
        performer_(resolver);
    }

    PerformerT performer_;
};

}  // namespace prm

#endif  // _THENEXECUTOR_EXECUTETRESOLVETREJECTUNDEFINED_HPP_
