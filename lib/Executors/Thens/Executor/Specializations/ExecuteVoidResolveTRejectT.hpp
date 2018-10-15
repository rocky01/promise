#ifndef _THENEXECUTOR_EXECUTEVOIDRESOLVETREJECTT_HPP_
#define _THENEXECUTOR_EXECUTEVOIDRESOLVETREJECTT_HPP_

#include "Executors/Thens/Executor/ExecuteTResolveTRejectT.hpp"

namespace prm
{

template <
    typename PerformerT,
    typename ResolveArgT,
    typename ErrorT,
    bool IsEmplace,
    typename... PerformerArgsT
>
class ThenExecutor<PerformerT, void, ResolveArgT, ErrorT, IsEmplace, PerformerArgsT...>
    : public IExecutorAndRejector<void, ErrorT>, public IResolver<ResolveArgT>,
      public PromiseExecutor<ResolveArgT, ErrorT>
{
    using pe = PromiseExecutor<ResolveArgT, ErrorT>;
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

    void resolve(ResolveArgT resolveArg) override
    {
        pe::state_ = State::Resolved;
        if (pe::nextPromiseExecutor_)
        {
            pe::nextPromiseExecutor_->execute(resolveArg);
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
        Resolver<ResolveArgT> resolver(this);
        Rejector<ErrorT> rejector(this);
        performer_(resolver, rejector);
    }

    void executeImpl(ResolverOnly)
    {
        Resolver<ResolveArgT> resolver(this);
        performer_(resolver);
    }

    PerformerT performer_;
};

}  // namespace prm

#endif  // _THENEXECUTOR_EXECUTEVOIDRESOLVETREJECTT_HPP_
