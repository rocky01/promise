#ifndef _CATCHEREXECUTOR_EXECUTEVOIDRESOLVEVOIDRETHROWT_HPP_
#define _CATCHEREXECUTOR_EXECUTEVOIDRESOLVEVOIDRETHROWT_HPP_

#include "Executors/Catchers/Executor/ErrorTResolveTRethrowT.hpp"

namespace prm
{

template <
    typename PerformerT,
    typename RethrowErrorT,
    bool IsEmplace,
    typename... PerformerArgsT
>
class CatcherExecutor<PerformerT, void, void, RethrowErrorT, IsEmplace, PerformerArgsT...>
    : public IExecutorAndRejector<void, void>,
      public IResolver<void>,
      public IRethrower<RethrowErrorT>,
      public PromiseExecutor<void, RethrowErrorT>
{
    using pe = PromiseExecutor<void, RethrowErrorT>;
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

    void execute() override
    {
        resolve();
    }

    void resolve() override
    {
        pe::state_ = State::Resolved;
        if (pe::nextPromiseExecutor_)
        {
            pe::nextPromiseExecutor_->execute();
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
        Resolver<void> resolver(this);
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

#endif  // _CATCHEREXECUTOR_EXECUTEVOIDRESOLVEVOIDRETHROWT_HPP_
