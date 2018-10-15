#ifndef _CATCHEREXECUTOR_EXECUTETRESOLVEVOIDRETHROWVOID_HPP_
#define _CATCHEREXECUTOR_EXECUTETRESOLVEVOIDRETHROWVOID_HPP_

#include "Executors/Catchers/Executor/ErrorTResolveTRethrowT.hpp"

namespace prm
{

template <
    typename PerformerT,
    typename ErrorT,
    bool IsEmplace,
    typename... PerformerArgsT
>
class CatcherExecutor<PerformerT, ErrorT, void, void, IsEmplace, PerformerArgsT...>
    : public IExecutorAndRejector<void, ErrorT>,
      public IResolver<void>,
      public IRethrower<void>,
      public PromiseExecutor<void, void>
{
    using pe = PromiseExecutor<void, void>;
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

    void reject(ErrorT error) override
    {
        pe::state_ = State::InProgress;
        rejectImpl(getOperatorTypeCounterpartForCatcher(&PerformerT::operator()), error);
    }

    void rethrow() override
    {
        pe::state_ = State::Rejected;
        if (pe::nextPromiseExecutor_)
        {
            pe::nextPromiseExecutor_->reject();
        }
    }

private:
    void rejectImpl(ErrorResolverRethrower, ErrorT error)
    {
        Resolver<void> resolver(this);
        Rethrower<void> rethrower(this);
        performer_(error, resolver, rethrower);
    }

    void rejectImpl(ErrorRethrower, ErrorT error)
    {
        Rethrower<void> rethrower(this);
        performer_(error, rethrower);
    }

    void rejectImpl(ResolverRethrower, ErrorT)
    {
        Resolver<void> resolver(this);
        Rethrower<void> rethrower(this);
        performer_(resolver, rethrower);
    }

    void rejectImpl(RethrowerOnly, ErrorT)
    {
        Rethrower<void> rethrower(this);
        performer_(rethrower);
    }

    PerformerT performer_;
};

}  // namespace prm

#endif  // _CATCHEREXECUTOR_EXECUTETRESOLVEVOIDRETHROWVOID_HPP_
