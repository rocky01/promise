#ifndef _THENEXECUTOR_EXECUTEVOIDRESOLVEVOIDREJECTT_HPP_
#define _THENEXECUTOR_EXECUTEVOIDRESOLVEVOIDREJECTT_HPP_

#include "Executors/Thens/Executor/ExecuteTResolveTRejectT.hpp"

namespace prm
{

template <
    typename PerformerT,
    typename ErrorT,
    bool IsEmplace,
    typename... PerformerArgsT
>
class ThenExecutor<PerformerT, void, void, ErrorT, IsEmplace, PerformerArgsT...>
    : public IExecutorAndRejector<void, ErrorT>, public IResolver<void>,
      public PromiseExecutor<void, ErrorT>
{
    using pe = PromiseExecutor<void, ErrorT>;
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

    void execute() override
    {
        pe::state_ = State::InProgress;
        executeImpl(getOperatorTypeCounterpartForExecutor(&PerformerT::operator()));
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
        pe::state_ = State::Rejected;
        if (pe::nextPromiseExecutor_)
        {
            pe::nextPromiseExecutor_->reject(error);
        }
    }

private:
    void executeImpl(ResolverRejector)
    {
        Resolver<void> resolver(this);
        Rejector<ErrorT> rejector(this);
        performer_(resolver, rejector);
    }

    void executeImpl(ResolverOnly)
    {
        Resolver<void> resolver(this);
        performer_(resolver);
    }

    PerformerT performer_;
};

}  // namespace prm

#endif  // _THENEXECUTOR_EXECUTEVOIDRESOLVEVOIDREJECTT_HPP_
