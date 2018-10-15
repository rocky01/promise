#ifndef _PROMISEIMP_HPP_
#define _PROMISEIMP_HPP_

#include <iostream>
#include <functional>
#include <memory>
#include <utility>
#include <type_traits>

#include "Helpers/CallOperatorTypeDeduction.hpp"
#include "Helpers/TypesDefinitions.hpp"
#include "Helpers/Asserts.hpp"
#include "Interfaces/IExecutor.hpp"
#include "PromiseExecutor.hpp"
#include "Executors/Thens/Then.hpp"
#include "Executors/Catchers/Catcher.hpp"
#include "Executors/Evers/Ever.hpp"

namespace prm
{

template <typename ResolveArgT, typename ErrorT, typename ParentExecuteArgT = void>
class Promise
{
public:    
    Promise& operator=(const Promise&) = delete;
    Promise(const Promise&) = delete;

    using ParentExecuteArgType = ParentExecuteArgT;
    using PromiseExecutorType = PromiseExecutor<ResolveArgT, ErrorT>;
    using PromiseExecutorUPtr = std::unique_ptr<PromiseExecutorType>;
    using ParentIExecutorUPtr = IExecutorUPtr<ParentExecuteArgType>;

    Promise()
        : promiseExecutor_(nullptr)
        , parentPromiseExecutor_(nullptr)
        , isStarted_(false)
    {}

    Promise(ParentIExecutorUPtr&& parentPromiseExecutor, PromiseExecutorType* promiseExecutor)
        : promiseExecutor_(promiseExecutor)
        , parentPromiseExecutor_(std::move(parentPromiseExecutor))
        , isStarted_(false)
    {}

    Promise(Promise&& promise)
        : promiseExecutor_(promise.promiseExecutor_)
        , parentPromiseExecutor_(std::move(promise.parentPromiseExecutor_))
        , isStarted_(promise.isStarted_)
    {}

    Promise& operator=(Promise&& promise)
    {
        if (this == &promise)
            return *this; // take precautions against `Promise = std::move(Promise)`

        promiseExecutor_ = promise.promiseExecutor_;
        parentPromiseExecutor_ = std::move(promise.parentPromiseExecutor_);
        isStarted_ = promise.isStarted_;
        return *this;
    }

    bool isInProgress()
    {
        return isStarted_ && !isFinished();
    }

    bool isFinished()
    {
        return isRejected() || isResolved();
    }

    bool isRejected()
    {
        return promiseExecutor_->getState() == State::Rejected;
    }

    bool isResolved()
    {
        return promiseExecutor_->getState() == State::Resolved;
    }

    ENABLE_IF_TYPE_VOID(ParentExecuteArgType)
    auto startExecution()
    {
        isStarted_ = true;
        if (parentPromiseExecutor_)
            parentPromiseExecutor_->execute();
        else
            throw IllegalAttemptToRunWorkingPromise();
        return std::move(*this);
    }

    ENABLE_IF_TYPE_DEFINED(ParentExecuteArgType)
    auto startExecution(ParentExecuteArgType parentExecuteArg)
    {
        //static assert ParentExecuteArgT != ExecuteArgTypeUndefined
        isStarted_ = true;
        if (parentPromiseExecutor_)
            parentPromiseExecutor_->execute(parentExecuteArg);
        else
            throw IllegalAttemptToRunWorkingPromise();
        return std::move(*this);    //  remove move
    }

    template<typename PerformerT>
    auto then(PerformerT&& performer)
    {
        using PerformerType = typename std::remove_reference<PerformerT>::type;
        thenCheckCallOperator<PerformerType>();
        using InferredExecuteArgType = decltype(getInferredArgType<ResolveArgT>());
        using ExecuteArgType = decltype(getExecuteArgType<InferredExecuteArgType>(&PerformerType::operator()));
        using ResolveArgType = decltype(getResolveArgTypeForExecutor(&PerformerType::operator()));
        using ErrorType = decltype(getErrorTypeForExecutor<ErrorT>(&PerformerType::operator()));
        thenCheckTypes<ResolveArgT, ExecuteArgType, ErrorT, ErrorType>();

        using ExecutorType = ThenExecutor<PerformerType, ExecuteArgType, ResolveArgType, ErrorType>;

        auto promiseExecutorUPtr = std::make_unique<ExecutorType>(std::forward<PerformerType>(performer));
        auto promiseExecutorRPtr = promiseExecutorUPtr.get();
        promiseExecutor_->setNextPromise(std::move(promiseExecutorUPtr));
        return Promise<ResolveArgType, ErrorType, ParentExecuteArgT>(std::move(parentPromiseExecutor_), promiseExecutorRPtr);
    }

    template <typename PerformerT, typename... PerformerArgsT>
    auto then(PerformerArgsT&&... performerArgs)
    {
        using PerformerType = typename std::remove_reference<PerformerT>::type;
        thenCheckCallOperator<PerformerType>();
        using InferredExecuteArgType = decltype(getInferredArgType<ResolveArgT>());
        using ExecuteArgType = decltype(getExecuteArgType<InferredExecuteArgType>(&PerformerType::operator()));
        using ResolveArgType = decltype(getResolveArgTypeForExecutor(&PerformerType::operator()));
        using ErrorType = decltype(getErrorTypeForExecutor<ErrorT>(&PerformerType::operator()));
        thenCheckTypes<ResolveArgT, ExecuteArgType, ErrorT, ErrorType>();

        using ExecutorType = ThenExecutor<PerformerType, ExecuteArgType, ResolveArgType, ErrorType, true, PerformerArgsT...>;

        auto promiseExecutorUPtr = std::make_unique<ExecutorType>(performerArgs...);
        auto promiseExecutorRPtr = promiseExecutorUPtr.get();
        promiseExecutor_->setNextPromise(std::move(promiseExecutorUPtr));
        return Promise<ResolveArgType, ErrorType, ParentExecuteArgT>(std::move(parentPromiseExecutor_), promiseExecutorRPtr);
    }

    template<typename PerformerT>
    auto catcher(PerformerT&& performer)
    {
        using PerformerType = typename std::remove_reference<PerformerT>::type;
        catcherCheckCallOperator<PerformerType>();

        using ErrorType = decltype(getErrorTypeForCatcher<ErrorT>(&PerformerType::operator()));
        using ResolveArgType = decltype(getResolveArgTypeForCatcher<ResolveArgT>(&PerformerType::operator()));
        using RethrowErrorType = decltype(getRethrowErrorType(&PerformerType::operator()));
        catcherCheckTypes<ErrorT, ErrorType, ResolveArgT, ResolveArgType>();

        using ExecutorType = CatcherExecutor<PerformerType, ErrorType, ResolveArgType, RethrowErrorType>;

        auto promiseExecutorUPtr = std::make_unique<ExecutorType>(std::forward<PerformerType>(performer));
        auto promiseExecutorRPtr = promiseExecutorUPtr.get();
        promiseExecutor_->setNextPromise(std::move(promiseExecutorUPtr));
        return Promise<ResolveArgType, RethrowErrorType, ParentExecuteArgT>(std::move(parentPromiseExecutor_), promiseExecutorRPtr);
    }

    template<typename PerformerT, typename... PerformerArgsT>
    auto catcher(PerformerArgsT&&... performerArgs)
    {
        using PerformerType = typename std::remove_reference<PerformerT>::type;
        catcherCheckCallOperator<PerformerType>();

        using ErrorType = decltype(getErrorTypeForCatcher<ErrorT>(&PerformerType::operator()));
        using ResolveArgType = decltype(getResolveArgTypeForCatcher<ResolveArgT>(&PerformerType::operator()));
        using RethrowErrorType = decltype(getRethrowErrorType(&PerformerType::operator()));
        catcherCheckTypes<ErrorT, ErrorType, ResolveArgT, ResolveArgType>();

        using ExecutorType = CatcherExecutor<PerformerType, ErrorType, ResolveArgType, RethrowErrorType, true, PerformerArgsT...>;

        auto promiseExecutorUPtr = std::make_unique<ExecutorType>(performerArgs...);
        auto promiseExecutorRPtr = promiseExecutorUPtr.get();
        promiseExecutor_->setNextPromise(std::move(promiseExecutorUPtr));
        return Promise<ResolveArgType, RethrowErrorType, ParentExecuteArgT>(std::move(parentPromiseExecutor_), promiseExecutorRPtr);
    }

    template<typename PerformerT>
    auto ever(PerformerT&& performer)
    {
        using PerformerType = typename std::remove_reference<PerformerT>::type;
        everCheckCallOperator<PerformerType>();
        using ResolveArgType = decltype(getResolveArgTypeForEver<ResolveArgT>(&PerformerType::operator()));
        using ErrorType = decltype(getErrorTypeForEver<ErrorT>(&PerformerType::operator()));
        everCheckTypes<ResolveArgT, ResolveArgType, ErrorT, ErrorType>();

        using ExecutorType = EverExecutor<PerformerType, ResolveArgType, ErrorType>;

        auto promiseExecutorUPtr = std::make_unique<ExecutorType>(std::forward<PerformerType>(performer));
        auto promiseExecutorRPtr = promiseExecutorUPtr.get();
        promiseExecutor_->setNextPromise(std::move(promiseExecutorUPtr));
        return Promise<ResolveArgType, ErrorType, ParentExecuteArgT>(std::move(parentPromiseExecutor_), promiseExecutorRPtr);
    }

    template<typename PerformerT, typename... PerformerArgsT>
    auto ever(PerformerArgsT&&... performerArgs)
    {
        using PerformerType = typename std::remove_reference<PerformerT>::type;
        everCheckCallOperator<PerformerType>();
        using ResolveArgType = decltype(getResolveArgTypeForEver<ResolveArgT>(&PerformerType::operator()));
        using ErrorType = decltype(getErrorTypeForEver<ErrorT>(&PerformerType::operator()));
        everCheckTypes<ResolveArgT, ResolveArgType, ErrorT, ErrorType>();

        using ExecutorType = EverExecutor<PerformerType, ResolveArgType, ErrorType, true, PerformerArgsT...>;

        auto promiseExecutorUPtr = std::make_unique<ExecutorType>(performerArgs...);
        auto promiseExecutorRPtr = promiseExecutorUPtr.get();
        promiseExecutor_->setNextPromise(std::move(promiseExecutorUPtr));
        return Promise<ResolveArgType, ErrorType, ParentExecuteArgT>(std::move(parentPromiseExecutor_), promiseExecutorRPtr);
    }

private:
    PromiseExecutorType* promiseExecutor_;
    ParentIExecutorUPtr parentPromiseExecutor_;
    bool isStarted_;
};

template<typename PerformerT>
auto make_promise(PerformerT&& performer)
{
    using PerformerType = typename std::remove_reference<PerformerT>::type;//powinien byc typu std function aby nie generowac nadmiarowch specializacji
    thenCheckCallOperator<PerformerType>();
    using ExecuteArgType = decltype(getExecuteArgType<void>(&PerformerType::operator()));
    using ResolveArgType = decltype(getResolveArgTypeForExecutor(&PerformerType::operator()));
    using ErrorType = decltype(getErrorTypeForExecutor<ErrorTypeUndefined>(&PerformerType::operator()));
    using ExecutorType = ThenExecutor<PerformerType, ExecuteArgType, ResolveArgType, ErrorType>;

    auto promiseExecutorUPtr = std::make_unique<ExecutorType>(std::forward<PerformerType>(performer));
    auto promiseExecutorRPtr = promiseExecutorUPtr.get();

    return Promise<ResolveArgType, ErrorType, ExecuteArgType>(std::move(promiseExecutorUPtr), promiseExecutorRPtr);
}

template <typename PerformerT, typename... PerformerArgsT>
auto make_promise(PerformerArgsT&&... performerArgs)
{
    using PerformerType = typename std::remove_reference<PerformerT>::type;
    thenCheckCallOperator<PerformerType>();
    using ExecuteArgType = decltype(getExecuteArgType<void>(&PerformerType::operator()));
    using ResolveArgType = decltype(getResolveArgTypeForExecutor(&PerformerType::operator()));
    using ErrorType = decltype(getErrorTypeForExecutor<ErrorTypeUndefined>(&PerformerType::operator()));
    using ExecutorType = ThenExecutor<PerformerType, ExecuteArgType, ResolveArgType, ErrorType, true, PerformerArgsT...>;

    auto promiseExecutorUPtr = std::make_unique<ExecutorType>(performerArgs...);
    auto promiseExecutorRPtr = promiseExecutorUPtr.get();

    return Promise<ResolveArgType, ErrorType, ExecuteArgType>(std::move(promiseExecutorUPtr), promiseExecutorRPtr);
}

}  // namespace prm

#endif  // _PROMISEIMP_HPP_
