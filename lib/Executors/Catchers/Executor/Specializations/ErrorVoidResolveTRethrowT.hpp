#ifndef _CATCHEREXECUTOR_EXECUTEVOIDRESOLVETRETHROWT_HPP_
#define _CATCHEREXECUTOR_EXECUTEVOIDRESOLVETRETHROWT_HPP_

#include "Executors/Catchers/Executor/ErrorTResolveTRethrowT.hpp"

namespace prm
{

template <
    typename PerformerT,
    typename ExecuteResolveArgT,
    typename RethrowErrorT,
    bool IsEmplace,
    typename... PerformerArgsT
>
class CatcherExecutor<PerformerT, void, ExecuteResolveArgT, RethrowErrorT, IsEmplace, PerformerArgsT...>
    : public IExecutorAndRejector<ExecuteResolveArgT, void>,
      public IResolver<ExecuteResolveArgT>,
      public IRethrower<RethrowErrorT>,
      public PromiseExecutor<ExecuteResolveArgT, RethrowErrorT>
{
    using pe = PromiseExecutor<ExecuteResolveArgT, RethrowErrorT>;
    using PerformerType = PerformerT; // only for enable if
public:
    ENABLE_IF_IS_NOT_EMPLACE(PerformerType, IsEmplace)
    CatcherExecutor(PerformerT&& performer)
        : performer_(std::forward<PerformerT>(performer))
    {}

    ENABLE_IF_IS_EMPLACE(PerformerType, IsEmplace)
    CatcherExecutor(PerformerArgsT&&... performerArgs)
        : performer_(std::forward<PerformerArgsT>(performerArgs)...)
    {}

    void execute(ExecuteResolveArgT executeArg) override
    {
        resolve(executeArg);
    }

    void resolve(ExecuteResolveArgT resolveArg) override
    {
        pe::state_ = State::Resolved;
        if (pe::nextPromiseExecutor_)
        {
            pe::nextPromiseExecutor_->execute(resolveArg);
        }
    }

    void reject() override
    {
        pe::state_ = State::InProgress;
        rejectImpl(getOperatorTypeCounterpartForCatcher(&PerformerT::operator()));
    }

    void rethrow(RethrowErrorT rethrowArg) override
    {
        pe::state_ = State::Rejected;
        if (pe::nextPromiseExecutor_)
        {
            pe::nextPromiseExecutor_->reject(rethrowArg);
        }
    }

private:
    void rejectImpl(ResolverRethrower)
    {
        Resolver<ExecuteResolveArgT> resolver(this);
        Rethrower<RethrowErrorT> rethrower(this);
        performer_(resolver, rethrower);
    }

    void rejectImpl(RethrowerOnly)
    {
        Rethrower<RethrowErrorT> rethrower(this);
        performer_(rethrower);
    }

    PerformerT performer_;
};

}  // namespace prm

#endif  // _CATCHEREXECUTOR_EXECUTEVOIDRESOLVETRETHROWT_HPP_
