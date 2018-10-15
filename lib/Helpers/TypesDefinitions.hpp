#ifndef _TYPESDEFINITIONS_HPP_
#define _TYPESDEFINITIONS_HPP_

#include <type_traits>

namespace prm
{

template <typename...>
class PerformerArgsGroupe;

// Exceptions
struct IllegalAttemptToOverwritePromise {};
struct IllegalAttemptToRunWorkingPromise {};

// Undefined Error, ResolveGroup
struct ResolveArgTypeUndefined
{};
struct ErrorTypeUndefined
{};

// Helper types
struct ResolverOnly
{};
struct RejectorOnly
{};
struct ExecuteResolverRejector
{};
struct ResolverRejector
{};
struct ExecuteResolver
{};
struct ExecuteRejector
{};

struct RethrowerOnly
{};
struct ErrorResolverRethrower
{};
struct ResolverRethrower
{};
struct ErrorResolver
{};
struct ErrorRethrower
{};

struct FinisherOnly
{};
struct FinisherReporter
{};

enum class State : char
{
    Rejected,
    Resolved,
    InProgress,
    Unstarted
};

// Enable if
template<typename T>
struct TypeWrapper
{
    using type = T;
};

#define ENABLE_IF_TYPE_VOID(X) template<typename T = TypeWrapper<X>, typename                                         \
    X = typename std::enable_if<std::is_same<typename T::type, void>::value>::type>

#define ENABLE_IF_TYPE_DEFINED(X) template<typename T = TypeWrapper<X>,                                               \
    typename X = typename std::enable_if<!std::is_same<typename T::type, void>::value, typename T::type>::type>

#define ENABLE_IF_IS_NOT_EMPLACE(X, CONDITION) template<typename T = TypeWrapper<X>,                                  \
    typename X = typename std::enable_if<!CONDITION, typename T::type>::type>

#define ENABLE_IF_IS_EMPLACE(X, CONDITION) template<typename T = TypeWrapper<X>,                                      \
    typename X = typename std::enable_if<CONDITION, typename T::type>::type>


}  // namespace prm

#endif  // _TYPESDEFINITIONS_HPP_
