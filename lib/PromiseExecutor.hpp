#ifndef _PROMISEXECUTOR_HPP_
#define _PROMISEXECUTOR_HPP_

#include "Helpers/TypesDefinitions.hpp"
#include "Interfaces/IRejector.hpp"
#include "Interfaces/IExecutorAndRejector.hpp"

namespace prm {

template<typename ResolveArgT, typename ErrorT>
class PromiseExecutor
{
public:
    using ResolveArgType = ResolveArgT;
    using ErrorType = ErrorT;
    using NextPromiseType = IExecutorAndRejectorUPtr<ResolveArgT, ErrorT>;

    void setNextPromise(NextPromiseType&& nextPromiseExecutorAndRejector)
    {
        if (not nextPromiseExecutor_)
            nextPromiseExecutor_ = std::move(nextPromiseExecutorAndRejector);
        else
            throw IllegalAttemptToOverwritePromise();
    }

    State getState()
    {
        return state_;
    }

protected:
    NextPromiseType nextPromiseExecutor_ = nullptr;
    State state_ = State::Unstarted;
};

template<typename ErrorT>
class PromiseExecutor<ResolveArgTypeUndefined, ErrorT>
{
public:
    using ResolveArgType = ResolveArgTypeUndefined;
    using ErrorType = ErrorT;
    using NextPromiseType = IRejectorUPtr<ErrorT>;

    void setNextPromise(NextPromiseType&& nextPromiseExecutorAndRejector)
    {
        if (not nextPromiseExecutor_)
            nextPromiseExecutor_ = std::move(nextPromiseExecutorAndRejector);
        else
            throw IllegalAttemptToOverwritePromise();
    }

    State getState()
    {
        return state_;
    }

protected:
    NextPromiseType nextPromiseExecutor_ = nullptr;
    State state_ = State::Unstarted;
};

template<
typename ResolveArgT
>
class PromiseExecutor<ResolveArgT, ErrorTypeUndefined>
{
public:
    using ResolveArgType = ResolveArgT;
    using ErrorType = ErrorTypeUndefined;
    using NextPromiseType = IExecutorUPtr<ResolveArgT>;

    void setNextPromise(NextPromiseType&& nextPromiseExecutorAndRejector)
    {
        if (not nextPromiseExecutor_)
            nextPromiseExecutor_ = std::move(nextPromiseExecutorAndRejector);
        else
            throw IllegalAttemptToOverwritePromise();
    }

    State getState()
    {
        return state_;
    }

protected:
    NextPromiseType nextPromiseExecutor_ = nullptr;
    State state_ = State::Unstarted;
};

} // namespace prm

#endif // _PROMISEXECUTOR_HPP_
