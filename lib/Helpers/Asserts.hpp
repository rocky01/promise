#ifndef _ASSERTS_HPP_
#define _ASSERTS_HPP_

#include <type_traits>

#include "Helpers/TypesDefinitions.hpp"
#include "Helpers/CallOperatorTypeDeduction.hpp"

namespace prm
{
    template<typename PerformerT>
    constexpr void hasCallOperator()
    {
        static_assert(std::is_member_function_pointer<decltype(&PerformerT::operator())>::value,
            "Call operator not available in provided class.");
    }

    template<typename PerformerT>
    constexpr void thenCheckCallOperator()
    {
        hasCallOperator<PerformerT>();
        static_assert(isExeResRej(&PerformerT::operator()) || isExeRes(&PerformerT::operator())
            || isExeRej(&PerformerT::operator()) || isResRej(&PerformerT::operator())
            || isRes(&PerformerT::operator()) || isRej(&PerformerT::operator()),
            "Provided class do not contain proper call operator. "
            "Acceptable operators prototypes \" operator()(T1 e, Resolver<T2>, Rejector<T3>) "
            "or operator()(T1 e, Resolver<T2>) or operator()(T1 e, Rejector<T2>) "
            "or operator()(Resolver<T1>, Rejector<T2>) or operator()(Resolver<T1>) or operator()(Rejector<T1>)\"");
    }

    template<typename ActialResolveArgT, typename NextExecuteArgT, typename ActualErrorT, typename NextErrorT>
    constexpr void thenCheckTypes()
    {
        static_assert(std::is_same<ActialResolveArgT, NextExecuteArgT>::value
            || (std::is_same<ActialResolveArgT, ResolveArgTypeUndefined>::value && std::is_same<NextExecuteArgT, void>::value),
            "Try to create \"then\" with wrong execute type.");

        static_assert(std::is_same<ActualErrorT, NextErrorT>::value
            || std::is_same<ActualErrorT, ErrorTypeUndefined>::value, "Try to create \"then\" with wrong error type.");
    }

    template<typename PerformerT>
    constexpr void catcherCheckCallOperator()
    {
        hasCallOperator<PerformerT>();
        static_assert(isErrResRet(&PerformerT::operator()) || isErrRes(&PerformerT::operator())
            || isErrRet(&PerformerT::operator()) || isResRet(&PerformerT::operator())
            || isRes(&PerformerT::operator()) || isRet(&PerformerT::operator()),
            "Provided class do not contain proper call operator. "
            "Acceptable operators prototypes \" operator()(T1 e, Resolver<T2>, Rethrower<T3>) "
            "or operator()(T1 e, Resolver<T2>) or operator()(T1 e, Rethrower<T2>) "
            "or operator()(Resolver<T1>, Rethrower<T2>) or operator()(Resolver<T1>) or operator()(Rethrower<T1>)\"");
    }

    template<typename ErrorT, typename ErrorType, typename ResolveArgT, typename ResolveArgType>
    constexpr void catcherCheckTypes()
    {
        static_assert(!std::is_same<ErrorT, ErrorTypeUndefined>::value, "\"cather\" can not be created here because previous sub-chain do not define error.");
        static_assert(std::is_same<ErrorT, ErrorType>::value, "Try to create \"catcher\" with wrong error type.");
        static_assert((std::is_same<ResolveArgT, ResolveArgTypeUndefined>::value && (std::is_same<ResolveArgType, void>::value || std::is_same<ResolveArgType, ResolveArgTypeUndefined>::value))
            || (!std::is_same<ResolveArgT, ResolveArgTypeUndefined>::value && std::is_same<ResolveArgT, ResolveArgType>::value),
            "Try to create \"catcher\" with wrong resolve type.");
    }

    template<typename PerformerT>
    constexpr void everCheckCallOperator()
    {
        hasCallOperator<PerformerT>();
        static_assert(isFin(&PerformerT::operator()) || isFinRep(&PerformerT::operator()),
            "Provided class do not contain proper call operator. "
            "Acceptable operators prototypes \" operator()(Finisher) "
            "or operator()(Finisher, Reporter<T1, T2>)\"");
    }

    template<typename ResolveArgT, typename ResolveArgType, typename ErrorT, typename ErrorType>
    constexpr void everCheckTypes()
    {
        static_assert(std::is_same<ResolveArgT, ResolveArgType>::value, "Try to create \"ever\" with wrong resolve type.");
        static_assert(std::is_same<ErrorT, ErrorType>::value, "Try to create \"ever\" with wrong error type.");
    }

}  // namespace prm

#endif  // _ASSERTS_HPP_
