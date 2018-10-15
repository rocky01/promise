#ifndef _CALLOPERATORTYPEDEDUCTION_HPP_
#define _CALLOPERATORTYPEDEDUCTION_HPP_

#include "TypesDefinitions.hpp"
#include "Callbacks/Resolver.hpp"
#include "Callbacks/Rejector.hpp"
#include "Callbacks/Rethrower.hpp"
#include "Callbacks/Reporter.hpp"
#include "Callbacks/Finisher.hpp"

#include "Interfaces/IExecutorAndRejector.hpp"
#include "Interfaces/IRejector.hpp"
#include "Interfaces/IExecutor.hpp"

namespace prm
{

// Execute call operator types deduction
// Resolve
template<typename Inferred, typename CT, typename ResolveArgT>
Inferred getExecuteArgType(void (CT::*)(Resolver<ResolveArgT>) const);

template<typename CT, typename ResolveArgT>
ResolveArgT getResolveArgTypeForExecutor(void (CT::*)(Resolver<ResolveArgT>) const);

template<typename PreviousErrorT, typename CT, typename ResolveArgT>
PreviousErrorT getErrorTypeForExecutor(void (CT::*)(Resolver<ResolveArgT>) const);

template<typename Inferred, typename CT, typename ResolveArgT>
Inferred getExecuteArgType(void (CT::*)(Resolver<ResolveArgT>));

template<typename CT, typename ResolveArgT>
ResolveArgT getResolveArgTypeForExecutor(void (CT::*)(Resolver<ResolveArgT>));

template<typename PreviousErrorT, typename CT, typename ResolveArgT>
PreviousErrorT getErrorTypeForExecutor(void (CT::*)(Resolver<ResolveArgT>));

// Reject
template<typename Inferred, typename CT, typename ErrorT>
Inferred getExecuteArgType(void (CT::*)(Rejector<ErrorT>) const);

template<typename CT, typename ErrorT>
ResolveArgTypeUndefined getResolveArgTypeForExecutor(void (CT::*)(Rejector<ErrorT>) const);

template<typename PreviousErrorT, typename CT, typename ErrorT>
ErrorT getErrorTypeForExecutor(void (CT::*)(Rejector<ErrorT>) const);

template<typename Inferred, typename CT, typename ErrorT>
Inferred getExecuteArgType(void (CT::*)(Rejector<ErrorT>));

template<typename CT, typename ErrorT>
ResolveArgTypeUndefined getResolveArgTypeForExecutor(void (CT::*)(Rejector<ErrorT>));

template<typename PreviousErrorT, typename CT, typename ErrorT>
ErrorT getErrorTypeForExecutor(void (CT::*)(Rejector<ErrorT>));

// Resolve Reject
template<typename Inferred, typename CT, typename ResolveArgT, typename ErrorT>
Inferred getExecuteArgType(void (CT::*)(Resolver<ResolveArgT>, Rejector<ErrorT>) const);

template<typename CT, typename ResolveArgT, typename ErrorT>
ResolveArgT getResolveArgTypeForExecutor(void (CT::*)(Resolver<ResolveArgT>, Rejector<ErrorT>) const);

template<typename PreviousErrorT, typename CT, typename ResolveArgT, typename ErrorT>
ErrorT getErrorTypeForExecutor(void (CT::*)(Resolver<ResolveArgT>, Rejector<ErrorT>) const);

template<typename Inferred, typename CT, typename ResolveArgT, typename ErrorT>
Inferred getExecuteArgType(void (CT::*)(Resolver<ResolveArgT>, Rejector<ErrorT>));

template<typename CT, typename ResolveArgT, typename ErrorT>
ResolveArgT getResolveArgTypeForExecutor(void (CT::*)(Resolver<ResolveArgT>, Rejector<ErrorT>));

template<typename PreviousErrorT, typename CT, typename ResolveArgT, typename ErrorT>
ErrorT getErrorTypeForExecutor(void (CT::*)(Resolver<ResolveArgT>, Rejector<ErrorT>));

// Execute Resolve
template<typename Inferred, typename CT, typename ExecuteArgT, typename ResolveArgT>
ExecuteArgT getExecuteArgType(void (CT::*)(ExecuteArgT, Resolver<ResolveArgT>) const);

template<typename CT, typename ExecuteArgT, typename ResolveArgT>
ResolveArgT getResolveArgTypeForExecutor(void (CT::*)(ExecuteArgT, Resolver<ResolveArgT>) const);

template<typename PreviousErrorT, typename CT, typename ExecuteArgT, typename ResolveArgT>
PreviousErrorT getErrorTypeForExecutor(void (CT::*)(ExecuteArgT, Resolver<ResolveArgT>) const);

template<typename Inferred, typename CT, typename ExecuteArgT, typename ResolveArgT>
ExecuteArgT getExecuteArgType(void (CT::*)(ExecuteArgT, Resolver<ResolveArgT>));

template<typename CT, typename ExecuteArgT, typename ResolveArgT>
ResolveArgT getResolveArgTypeForExecutor(void (CT::*)(ExecuteArgT, Resolver<ResolveArgT>));

template<typename PreviousErrorT, typename CT, typename ExecuteArgT, typename ResolveArgT>
PreviousErrorT getErrorTypeForExecutor(void (CT::*)(ExecuteArgT, Resolver<ResolveArgT>));

// Execute Reject
template<typename Inferred, typename CT, typename ExecuteArgT, typename ErrorT>
ExecuteArgT getExecuteArgType(void (CT::*)(ExecuteArgT, Rejector<ErrorT>) const);

template<typename CT, typename ExecuteArgT, typename ErrorT>
ResolveArgTypeUndefined getResolveArgTypeForExecutor(void (CT::*)(ExecuteArgT, Rejector<ErrorT>) const);

template<typename PreviousErrorT, typename CT, typename ExecuteArgT, typename ErrorT>
ErrorT getErrorTypeForExecutor(void (CT::*)(ExecuteArgT, Rejector<ErrorT>) const);

template<typename Inferred, typename CT, typename ExecuteArgT, typename ErrorT>
ExecuteArgT getExecuteArgType(void (CT::*)(ExecuteArgT, Rejector<ErrorT>));

template<typename CT, typename ExecuteArgT, typename ErrorT>
ResolveArgTypeUndefined getResolveArgTypeForExecutor(void (CT::*)(ExecuteArgT, Rejector<ErrorT>));

template<typename PreviousErrorT, typename CT, typename ExecuteArgT, typename ErrorT>
ErrorT getErrorTypeForExecutor(void (CT::*)(ExecuteArgT, Rejector<ErrorT>));

// Execute Resolve Reject
template<typename Inferred, typename CT,  typename ExecuteArgT, typename ResolveArgT, typename ErrorT>
ExecuteArgT getExecuteArgType(void (CT::*)(ExecuteArgT, Resolver<ResolveArgT>, Rejector<ErrorT>) const);

template<typename CT,  typename ExecuteArgT, typename ResolveArgT, typename ErrorT>
ResolveArgT getResolveArgTypeForExecutor(void (CT::*)(ExecuteArgT, Resolver<ResolveArgT>, Rejector<ErrorT>) const);

template<typename PreviousErrorT, typename CT,  typename ExecuteArgT, typename ResolveArgT, typename ErrorT>
ErrorT getErrorTypeForExecutor(void (CT::*)(ExecuteArgT, Resolver<ResolveArgT>, Rejector<ErrorT>) const);

template<typename Inferred, typename CT,  typename ExecuteArgT, typename ResolveArgT, typename ErrorT>
ExecuteArgT getExecuteArgType(void (CT::*)(ExecuteArgT, Resolver<ResolveArgT>, Rejector<ErrorT>));

template<typename CT,  typename ExecuteArgT, typename ResolveArgT, typename ErrorT>
ResolveArgT getResolveArgTypeForExecutor(void (CT::*)(ExecuteArgT, Resolver<ResolveArgT>, Rejector<ErrorT>));

template<typename PreviousErrorT, typename CT,  typename ExecuteArgT, typename ResolveArgT, typename ErrorT>
ErrorT getErrorTypeForExecutor(void (CT::*)(ExecuteArgT, Resolver<ResolveArgT>, Rejector<ErrorT>));


// Catcher call operator types deduction
// Resolve
template<typename Inferred, typename CT, typename ResolveArgT>
Inferred getErrorTypeForCatcher(void (CT::*)(Resolver<ResolveArgT>) const);

template<typename Inferred, typename CT, typename ResolveArgT>
ResolveArgT getResolveArgTypeForCatcher(void (CT::*)(Resolver<ResolveArgT>) const);

template<typename CT, typename ResolveArgT>
ErrorTypeUndefined getRethrowErrorType(void (CT::*)(Resolver<ResolveArgT>) const);

template<typename Inferred, typename CT, typename ResolveArgT>
Inferred getErrorTypeForCatcher(void (CT::*)(Resolver<ResolveArgT>));

template<typename Inferred, typename CT, typename ResolveArgT>
ResolveArgT getResolveArgTypeForCatcher(void (CT::*)(Resolver<ResolveArgT>));

template<typename CT, typename ResolveArgT>
ErrorTypeUndefined getRethrowErrorType(void (CT::*)(Resolver<ResolveArgT>));

// Rethrow
template<typename Inferred, typename CT, typename RethrowErrorType>
Inferred getErrorTypeForCatcher(void (CT::*)(Rethrower<RethrowErrorType>) const);

template<typename Inferred, typename CT, typename RethrowErrorType>
Inferred getResolveArgTypeForCatcher(void (CT::*)(Rethrower<RethrowErrorType>) const);

template<typename CT, typename RethrowErrorType>
RethrowErrorType getRethrowErrorType(void (CT::*)(Rethrower<RethrowErrorType>) const);

template<typename Inferred, typename CT, typename RethrowErrorType>
Inferred getErrorTypeForCatcher(void (CT::*)(Rethrower<RethrowErrorType>));

template<typename Inferred, typename CT, typename RethrowErrorType>
Inferred getResolveArgTypeForCatcher(void (CT::*)(Rethrower<RethrowErrorType>));

template<typename CT, typename RethrowErrorType>
RethrowErrorType getRethrowErrorType(void (CT::*)(Rethrower<RethrowErrorType>));

// Resolve Rethrew
template<typename Inferred, typename CT, typename ResolveArgT, typename RethrowErrorType>
Inferred getErrorTypeForCatcher(void (CT::*)(Resolver<ResolveArgT>, Rethrower<RethrowErrorType>) const);

template<typename Inferred, typename CT, typename ResolveArgT, typename RethrowErrorType>
ResolveArgT getResolveArgTypeForCatcher(void (CT::*)(Resolver<ResolveArgT>, Rethrower<RethrowErrorType>) const);

template<typename CT, typename ResolveArgT, typename RethrowErrorType>
RethrowErrorType getRethrowErrorType(void (CT::*)(Resolver<ResolveArgT>, Rethrower<RethrowErrorType>) const);

template<typename Inferred, typename CT, typename ResolveArgT, typename RethrowErrorType>
Inferred getErrorTypeForCatcher(void (CT::*)(Resolver<ResolveArgT>, Rethrower<RethrowErrorType>));

template<typename Inferred, typename CT, typename ResolveArgT, typename RethrowErrorType>
ResolveArgT getResolveArgTypeForCatcher(void (CT::*)(Resolver<ResolveArgT>, Rethrower<RethrowErrorType>));

template<typename CT, typename ResolveArgT, typename RethrowErrorType>
RethrowErrorType getRethrowErrorType(void (CT::*)(Resolver<ResolveArgT>, Rethrower<RethrowErrorType>));

// Error Resolve
template<typename Inferred, typename CT, typename ErrorT, typename ResolveArgT>
ErrorT getErrorTypeForCatcher(void (CT::*)(ErrorT, Resolver<ResolveArgT>) const);

template<typename Inferred, typename CT, typename ErrorT, typename ResolveArgT>
ResolveArgT getResolveArgTypeForCatcher(void (CT::*)(ErrorT, Resolver<ResolveArgT>) const);

template<typename CT, typename ErrorT, typename ResolveArgT>
ErrorTypeUndefined getRethrowErrorType(void (CT::*)(ErrorT, Resolver<ResolveArgT>) const);

template<typename Inferred, typename CT, typename ErrorT, typename ResolveArgT>
ErrorT getErrorTypeForCatcher(void (CT::*)(ErrorT, Resolver<ResolveArgT>));

template<typename Inferred, typename CT, typename ErrorT, typename ResolveArgT>
ResolveArgT getResolveArgTypeForCatcher(void (CT::*)(ErrorT, Resolver<ResolveArgT>));

template<typename CT, typename ErrorT, typename ResolveArgT>
ErrorTypeUndefined getRethrowErrorType(void (CT::*)(ErrorT, Resolver<ResolveArgT>));

// Error Rethrew
template<typename Inferred, typename CT, typename ErrorT, typename RethrowErrorType>
ErrorT getErrorTypeForCatcher(void (CT::*)(ErrorT, Rethrower<RethrowErrorType>) const);

template<typename Inferred, typename CT, typename ErrorT, typename RethrowErrorType>
Inferred getResolveArgTypeForCatcher(void (CT::*)(ErrorT, Rethrower<RethrowErrorType>) const);

template<typename CT, typename ErrorT, typename RethrowErrorType>
RethrowErrorType getRethrowErrorType(void (CT::*)(ErrorT, Rethrower<RethrowErrorType>) const);

template<typename Inferred, typename CT, typename ErrorT, typename RethrowErrorType>
ErrorT getErrorTypeForCatcher(void (CT::*)(ErrorT, Rethrower<RethrowErrorType>) const);

template<typename Inferred, typename CT, typename ErrorT, typename RethrowErrorType>
Inferred getResolveArgTypeForCatcher(void (CT::*)(ErrorT, Rethrower<RethrowErrorType>) const);

template<typename CT, typename ErrorT, typename RethrowErrorType>
RethrowErrorType getRethrowErrorType(void (CT::*)(ErrorT, Rethrower<RethrowErrorType>) const);

// Error Resolve Rethrew
template<typename Inferred, typename CT,  typename ErrorT, typename ResolveArgT, typename RethrowErrorType>
ErrorT getErrorTypeForCatcher(void (CT::*)(ErrorT, Resolver<ResolveArgT>, Rethrower<RethrowErrorType>) const);

template<typename Inferred, typename CT, typename ErrorT, typename ResolveArgT, typename RethrowErrorType>
ResolveArgT getResolveArgTypeForCatcher(void (CT::*)(ErrorT, Resolver<ResolveArgT>, Rethrower<RethrowErrorType>) const);

template<typename CT,  typename ErrorT, typename ResolveArgT, typename RethrowErrorType>
RethrowErrorType getRethrowErrorType(void (CT::*)(ErrorT, Resolver<ResolveArgT>, Rethrower<RethrowErrorType>) const);

template<typename Inferred, typename CT,  typename ErrorT, typename ResolveArgT, typename RethrowErrorType>
ErrorT getErrorTypeForCatcher(void (CT::*)(ErrorT, Resolver<ResolveArgT>, Rethrower<RethrowErrorType>));

template<typename Inferred, typename CT, typename ErrorT, typename ResolveArgT, typename RethrowErrorType>
ResolveArgT getResolveArgTypeForCatcher(void (CT::*)(ErrorT, Resolver<ResolveArgT>, Rethrower<RethrowErrorType>));

template<typename CT,  typename ErrorT, typename ResolveArgT, typename RethrowErrorType>
RethrowErrorType getRethrowErrorType(void (CT::*)(ErrorT, Resolver<ResolveArgT>, Rethrower<RethrowErrorType>));

// Ever call operator types deduction
template<typename Inferred, typename CT>
Inferred getResolveArgTypeForEver(void (CT::*)(Finisher));

template<typename Inferred, typename CT>
Inferred getErrorTypeForEver(void (CT::*)(Finisher));

template<typename Inferred, typename CT>
Inferred getResolveArgTypeForEver(void (CT::*)(Finisher) const);

template<typename Inferred, typename CT>
Inferred getErrorTypeForEver(void (CT::*)(Finisher) const);

template<typename Inferred, typename CT, typename ResolveArgT, typename ErrorT>
ResolveArgT getResolveArgTypeForEver(void (CT::*)(Finisher, Reporter<ResolveArgT, ErrorT>));

template<typename Inferred, typename CT, typename ResolveArgT, typename ErrorT>
ErrorT getErrorTypeForEver(void (CT::*)(Finisher, Reporter<ResolveArgT, ErrorT>));

template<typename Inferred, typename CT, typename ResolveArgT, typename ErrorT>
ResolveArgT getResolveArgTypeForEver(void (CT::*)(Finisher, Reporter<ResolveArgT, ErrorT>) const);

template<typename Inferred, typename CT, typename ResolveArgT, typename ErrorT>
ErrorT getErrorTypeForEver(void (CT::*)(Finisher, Reporter<ResolveArgT, ErrorT>) const);

// For 'execute' method specialization
template<typename CT, typename ExecuteArgT, typename ResolveArgT, typename ErrorT>
constexpr ExecuteResolverRejector getOperatorTypeCounterpartForExecutor(void (CT::*)(ExecuteArgT, Resolver<ResolveArgT>, Rejector<ErrorT>))
{
    return ExecuteResolverRejector();
}

template<typename CT, typename ExecuteArgT, typename ResolveArgT, typename ErrorT>
constexpr ExecuteResolverRejector getOperatorTypeCounterpartForExecutor(void (CT::*)(ExecuteArgT, Resolver<ResolveArgT>, Rejector<ErrorT>) const)
{
    return ExecuteResolverRejector();
}

template<typename CT, typename ExecuteArgT, typename ResolveArgT>
constexpr ExecuteResolver getOperatorTypeCounterpartForExecutor(void (CT::*)(ExecuteArgT, Resolver<ResolveArgT>))
{
    return ExecuteResolver();
}

template<typename CT, typename ExecuteArgT, typename ResolveArgT>
constexpr ExecuteResolver getOperatorTypeCounterpartForExecutor(void (CT::*)(ExecuteArgT, Resolver<ResolveArgT>) const)
{
    return ExecuteResolver();
}

template<typename CT, typename ExecuteArgT, typename ErrorT>
constexpr ExecuteRejector getOperatorTypeCounterpartForExecutor(void (CT::*)(ExecuteArgT, Rejector<ErrorT>))
{
    return ExecuteRejector();
}

template<typename CT, typename ExecuteArgT, typename ErrorT>
constexpr ExecuteRejector getOperatorTypeCounterpartForExecutor(void (CT::*)(ExecuteArgT, Rejector<ErrorT>) const)
{
    return ExecuteRejector();
}

template<typename CT, typename ResolveArgT, typename ErrorT>
constexpr ResolverRejector getOperatorTypeCounterpartForExecutor(void (CT::*)(Resolver<ResolveArgT>, Rejector<ErrorT>))
{
    return ResolverRejector();
}

template<typename CT, typename ResolveArgT, typename ErrorT>
constexpr ResolverRejector getOperatorTypeCounterpartForExecutor(void (CT::*)(Resolver<ResolveArgT>, Rejector<ErrorT>) const)
{
    return ResolverRejector();
}

template<typename CT, typename ResolveArgT>
constexpr ResolverOnly getOperatorTypeCounterpartForExecutor(void (CT::*)(Resolver<ResolveArgT>))
{
    return ResolverOnly();
}

template<typename CT, typename ResolveArgT>
constexpr ResolverOnly getOperatorTypeCounterpartForExecutor(void (CT::*)(Resolver<ResolveArgT>) const)
{
    return ResolverOnly();
}

template<typename CT, typename ErrorT>
constexpr RejectorOnly getOperatorTypeCounterpartForExecutor(void (CT::*)( Rejector<ErrorT>))
{
    return RejectorOnly();
}

template<typename CT, typename ErrorT>
constexpr RejectorOnly getOperatorTypeCounterpartForExecutor(void (CT::*)(Rejector<ErrorT>) const)
{
    return RejectorOnly();
}

// For 'reject' method specialization
template<typename CT, typename ErrorT, typename ResolveArgT, typename NewErrorT>
constexpr ErrorResolverRethrower getOperatorTypeCounterpartForCatcher(void (CT::*)(ErrorT, Resolver<ResolveArgT>, Rethrower<NewErrorT>))
{
    return ErrorResolverRethrower();
}

template<typename CT, typename ErrorT, typename ResolveArgT, typename NewErrorT>
constexpr ErrorResolverRethrower getOperatorTypeCounterpartForCatcher(void (CT::*)(ErrorT, Resolver<ResolveArgT>, Rethrower<NewErrorT>) const)
{
    return ErrorResolverRethrower();
}

template<typename CT, typename ErrorT, typename ResolveArgT>
constexpr ErrorResolver getOperatorTypeCounterpartForCatcher(void (CT::*)(ErrorT, Resolver<ResolveArgT>))
{
    return ErrorResolver();
}

template<typename CT, typename ErrorT, typename ResolveArgT>
constexpr ErrorResolver getOperatorTypeCounterpartForCatcher(void (CT::*)(ErrorT, Resolver<ResolveArgT>) const)
{
    return ErrorResolver();
}

template<typename CT, typename ErrorT, typename NewErrorT>
constexpr ErrorRethrower getOperatorTypeCounterpartForCatcher(void (CT::*)(ErrorT, Rethrower<NewErrorT>))
{
    return ErrorRethrower();
}

template<typename CT, typename ErrorT, typename NewErrorT>
constexpr ErrorRethrower getOperatorTypeCounterpartForCatcher(void (CT::*)(ErrorT, Rethrower<NewErrorT>) const)
{
    return ErrorRethrower();
}

template<typename CT, typename ResolveArgT, typename NewErrorT>
constexpr ResolverRethrower getOperatorTypeCounterpartForCatcher(void (CT::*)(Resolver<ResolveArgT>, Rethrower<NewErrorT>))
{
    return ResolverRethrower();
}

template<typename CT, typename ResolveArgT, typename NewErrorT>
constexpr ResolverRethrower getOperatorTypeCounterpartForCatcher(void (CT::*)(Resolver<ResolveArgT>, Rethrower<NewErrorT>) const)
{
    return ResolverRethrower();
}

template<typename CT, typename ResolveArgT>
constexpr ResolverOnly getOperatorTypeCounterpartForCatcher(void (CT::*)(Resolver<ResolveArgT>))
{
    return ResolverOnly();
}

template<typename CT, typename ResolveArgT>
constexpr ResolverOnly getOperatorTypeCounterpartForCatcher(void (CT::*)(Resolver<ResolveArgT>) const)
{
    return ResolverOnly();
}

template<typename CT, typename NewErrorT>
constexpr RethrowerOnly getOperatorTypeCounterpartForCatcher(void (CT::*)(Rethrower<NewErrorT>))
{
    return RethrowerOnly();
}

template<typename CT, typename NewErrorT>
constexpr RethrowerOnly getOperatorTypeCounterpartForCatcher(void (CT::*)(Rethrower<NewErrorT>) const)
{
    return RethrowerOnly();
}

// For 'EverExecutor' 'execute' and 'reject' method specialization
template<typename CT>
constexpr FinisherOnly getOperatorTypeCounterpartForEver(void (CT::*)(Finisher))
{
    return FinisherOnly();
}

template<typename CT>
constexpr FinisherOnly getOperatorTypeCounterpartForEver(void (CT::*)(Finisher) const)
{
    return FinisherOnly();
}

template<typename CT, typename ResolveArgT, typename ErrorT>
constexpr FinisherReporter getOperatorTypeCounterpartForEver(void (CT::*)(Finisher, Reporter<ResolveArgT, ErrorT>))
{
    return FinisherReporter();
}

template<typename CT, typename ResolveArgT, typename ErrorT>
constexpr FinisherReporter getOperatorTypeCounterpartForEver(void (CT::*)(Finisher, Reporter<ResolveArgT, ErrorT>) const)
{
    return FinisherReporter();
}

//For next promise type
template<typename ResolveArgT, typename ErrorT>
IExecutorAndRejectorUPtr<ResolveArgT, ErrorT> getNextPromiseType(ResolveArgT, ErrorT);

template<typename ErrorT>
IRejectorUPtr<ErrorT> getNextPromiseType(ResolveArgTypeUndefined, ErrorT);

template<typename ResolveArgT>
IExecutorUPtr<ResolveArgT> getNextPromiseType(ResolveArgT, ErrorTypeUndefined);

// resolve inference
template<typename ResolveArgT>
typename std::conditional<std::is_same<ResolveArgT, ResolveArgTypeUndefined>::value, void, ResolveArgT>::type
getInferredArgType();


//static assert then
template<typename CT, typename... Args>
constexpr bool isExeResRej(void (CT::*)(Args...))
{
    return false;
}

template<typename CT, typename ExecuteArgT, typename ResolveArgT, typename ErrorT>
constexpr bool isExeResRej(void (CT::*)(ExecuteArgT, Resolver<ResolveArgT>, Rejector<ErrorT>))
{
    return true;
}

template<typename CT, typename... Args>
constexpr bool isExeResRej(void (CT::*)(Args...) const)
{
    return false;
}

template<typename CT, typename ExecuteArgT, typename ResolveArgT, typename ErrorT>
constexpr bool isExeResRej(void (CT::*)(ExecuteArgT, Resolver<ResolveArgT>, Rejector<ErrorT>) const)
{
    return true;
}

template<typename CT, typename... Args>
constexpr bool isExeRes(void (CT::*)(Args...))
{
    return false;
}

template<typename CT, typename ExecuteArgT, typename ResolveArgT>
constexpr bool isExeRes(void (CT::*)(ExecuteArgT, Resolver<ResolveArgT>))
{
    return true;
}

template<typename CT, typename... Args>
constexpr bool isExeRes(void (CT::*)(Args...) const)
{
    return false;
}

template<typename CT, typename ExecuteArgT, typename ResolveArgT>
constexpr bool isExeRes(void (CT::*)(ExecuteArgT, Resolver<ResolveArgT>) const)
{
    return true;
}

template<typename CT, typename... Args>
constexpr bool isExeRej(void (CT::*)(Args...))
{
    return false;
}

template<typename CT, typename ExecuteArgT, typename ErrorT>
constexpr bool isExeRej(void (CT::*)(ExecuteArgT, Rejector<ErrorT>))
{
    return true;
}

template<typename CT, typename... Args>
constexpr bool isExeRej(void (CT::*)(Args...) const)
{
    return false;
}

template<typename CT, typename ExecuteArgT, typename ErrorT>
constexpr bool isExeRej(void (CT::*)(ExecuteArgT, Rejector<ErrorT>) const)
{
    return true;
}

template<typename CT, typename... Args>
constexpr bool isResRej(void (CT::*)(Args...))
{
    return false;
}

template<typename CT, typename ResolveArgT, typename ErrorT>
constexpr bool isResRej(void (CT::*)(Resolver<ResolveArgT>, Rejector<ErrorT>))
{
    return true;
}

template<typename CT, typename... Args>
constexpr bool isResRej(void (CT::*)(Args...) const)
{
    return false;
}

template<typename CT, typename ResolveArgT, typename ErrorT>
constexpr bool isResRej(void (CT::*)(Resolver<ResolveArgT>, Rejector<ErrorT>) const)
{
    return true;
}

template<typename CT, typename... Args>
constexpr bool isRes(void (CT::*)(Args...))
{
    return false;
}

template<typename CT, typename ResolveArgT>
constexpr bool isRes(void (CT::*)(Resolver<ResolveArgT>))
{
    return true;
}

template<typename CT, typename... Args>
constexpr bool isRes(void (CT::*)(Args...) const)
{
    return false;
}

template<typename CT, typename ResolveArgT>
constexpr bool isRes(void (CT::*)(Resolver<ResolveArgT>) const)
{
    return true;
}

template<typename CT, typename... Args>
constexpr bool isRej(void (CT::*)(Args...))
{
    return false;
}

template<typename CT, typename ErrorT>
constexpr bool isRej(void (CT::*)(Rejector<ErrorT>))
{
    return true;
}

template<typename CT, typename... Args>
constexpr bool isRej(void (CT::*)(Args...) const)
{
    return false;
}

template<typename CT, typename ErrorT>
constexpr bool isRej(void (CT::*)(Rejector<ErrorT>) const)
{
    return true;
}


//static assert catcher
template<typename CT, typename... Args>
constexpr bool isErrResRet(void (CT::*)(Args...))
{
    return false;
}

template<typename CT, typename ErrorT, typename ResolveArgT, typename NewErrorT>
constexpr bool isErrResRet(void (CT::*)(ErrorT, Resolver<ResolveArgT>, Rethrower<NewErrorT>))
{
    return true;
}

template<typename CT, typename... Args>
constexpr bool isErrResRet(void (CT::*)(Args...) const)
{
    return false;
}

template<typename CT, typename ErrorT, typename ResolveArgT, typename NewErrorT>
constexpr bool isErrResRet(void (CT::*)(ErrorT, Resolver<ResolveArgT>, Rethrower<NewErrorT>) const)
{
    return true;
}

template<typename CT, typename... Args>
constexpr bool isErrRes(void (CT::*)(Args...))
{
    return false;
}

template<typename CT, typename ErrorT, typename ResolveArgT>
constexpr bool isErrRes(void (CT::*)(ErrorT, Resolver<ResolveArgT>))
{
    return true;
}

template<typename CT, typename... Args>
constexpr bool isErrRes(void (CT::*)(Args...) const)
{
    return false;
}

template<typename CT, typename ErrorT, typename ResolveArgT>
constexpr bool isErrRes(void (CT::*)(ErrorT, Resolver<ResolveArgT>) const)
{
    return true;
}

template<typename CT, typename... Args>
constexpr bool isErrRet(void (CT::*)(Args...))
{
    return false;
}

template<typename CT, typename ErrorT, typename NewErrorT>
constexpr bool isErrRet(void (CT::*)(ErrorT, Rethrower<NewErrorT>))
{
    return true;
}

template<typename CT, typename... Args>
constexpr bool isErrRet(void (CT::*)(Args...) const)
{
    return false;
}

template<typename CT, typename ErrorT, typename NewErrorT>
constexpr bool isErrRet(void (CT::*)(ErrorT, Rethrower<NewErrorT>) const)
{
    return true;
}

template<typename CT, typename... Args>
constexpr bool isResRet(void (CT::*)(Args...))
{
    return false;
}

template<typename CT, typename ResolveArgT, typename NewErrorT>
constexpr bool isResRet(void (CT::*)(Resolver<ResolveArgT>, Rethrower<NewErrorT>))
{
    return true;
}

template<typename CT, typename... Args>
constexpr bool isResRet(void (CT::*)(Args...) const)
{
    return false;
}

template<typename CT, typename ResolveArgT, typename NewErrorT>
constexpr bool isResRet(void (CT::*)(Resolver<ResolveArgT>, Rethrower<NewErrorT>) const)
{
    return true;
}

// isRes the same like for then

template<typename CT, typename... Args>
constexpr bool isRet(void (CT::*)(Args...))
{
    return false;
}

template<typename CT, typename NewErrorT>
constexpr bool isRet(void (CT::*)(Rethrower<NewErrorT>))
{
    return true;
}

template<typename CT, typename... Args>
constexpr bool isRet(void (CT::*)(Args...) const)
{
    return false;
}

template<typename CT, typename NewErrorT>
constexpr bool isRet(void (CT::*)(Rethrower<NewErrorT>) const)
{
    return true;
}

// static assert ever
template<typename CT, typename... Args>
constexpr bool isFin(void (CT::*)(Args...))
{
    return false;
}

template<typename CT>
constexpr bool isFin(void (CT::*)(Finisher))
{
    return true;
}

template<typename CT, typename... Args>
constexpr bool isFin(void (CT::*)(Args...) const)
{
    return false;
}

template<typename CT>
constexpr bool isFin(void (CT::*)(Finisher) const)
{
    return true;
}

template<typename CT, typename... Args>
constexpr bool isFinRep(void (CT::*)(Args...))
{
    return false;
}

template<typename CT, typename ResolveArgT, typename ErrorT>
constexpr bool isFinRep(void (CT::*)(Finisher, Reporter<ResolveArgT, ErrorT>))
{
    return true;
}

template<typename CT, typename... Args>
constexpr bool isFinRep(void (CT::*)(Args...) const)
{
    return false;
}

template<typename CT, typename ResolveArgT, typename ErrorT>
constexpr bool isFinRep(void (CT::*)(Finisher, Reporter<ResolveArgT, ErrorT>) const)
{
    return true;
}

}  // namespace prm

#endif  // _CALLOPERATORTYPEDEDUCTION_HPP_

