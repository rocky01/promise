#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Promise.hpp"

using namespace prm;
/***
 *
 * 1. Catcher function.
 *
 * We have types:
 * ErrorT
 * ErrorVoid
 *
 * ResolveT
 * ResolveVoid
 * ResolveUndefined
 *
 * RethrowT
 * RethrowVoid
 * ErrorTypeUndefined
 *
 * There are the following combinations availiable:
 * ErrorT, ResolveT, RethrowT
 * ErrorT, ResolveT, RethrowVoid
 * ErrorT, ResolveT, ErrorTypeUndefined
 *
 * ErrorT, ResolveVoid, RethrowT
 * ErrorT, ResolveVoid, RethrowVoid
 * ErrorT, ResolveVoid, ErrorTypeUndefined
 *
 * ErrorT, ResolveUndefined, RethrowT
 * ErrorT, ResolveUndefined, RethrowVoid
 * ErrorT, ResolveUndefined, ErrorTypeUndefined <- Not supported
 *
 * ErrorVoid, ResolveT, RethrowT
 * ErrorVoid, ResolveT, RethrowVoid
 * ErrorVoid, ResolveT, ErrorTypeUndefined
 *
 * ErrorVoid, ResolveVoid, RethrowT
 * ErrorVoid, ResolveVoid, RethrowVoid
 * ErrorVoid, ResolveVoid, ErrorTypeUndefined
 *
 * ErrorVoid, ResolveUndefined, RethrowT
 * ErrorVoid, ResolveUndefined, RethrowVoid
 * ErrorVoid, ResolveUndefined, ErrorTypeUndefined <- Not supported
 *
 * There are the following combinations with make_promise availiable:
 * -----------------------------
 * ExeT, ResolveT, RejectT
 * ErrorT, ResolveT, RethrowT
 *
 * ExeT, ResolveT, RejectT
 * ErrorT, ResolveT
 *
 * ExeT, ResolveT, RejectT
 * ErrorT, RethrowT
 *
 * ExeT, ResolveT, RejectT
 * ResolveT, RethrowT
 *
 * ExeT, ResolveT, RejectT
 * ResolveT
 *
 * ExeT, ResolveT, RejectT
 * RethrowT
 *
 * ExeT, ResolveT, RejectT
 * ErrorT, ResolveT, RethrowVoid
 *
 * ExeT, ResolveT, RejectT
 * ErrorT, RethrowVoid
 *
 * ExeT, ResolveT, RejectT
 * ResolveT, RethrowVoid
 *
 * ExeT, ResolveT, RejectT
 * RethrowVoid
 * -----------------------------
 * ExeT, ResolveT, RejectVoid
 * ResolveT, RethrowT
 *
 * ExeT, ResolveT, RejectVoid
 * ResolveT
 *
 * ExeT, ResolveT, RejectVoid
 * RethrowT
 *
 * ExeT, ResolveT, RejectVoid
 * ResolveT, RethrowVoid
 *
 * ExeT, ResolveT, RejectVoid
 * RethrowVoid
 * -----------------------------
 * ExeT, ResolveT, RejectUndefined
 * ExeT, ResolveT, RejectT
 * ErrorT, ResolveT
 * -----------------------------
 * ExeT, ResolveVoid, RejectT
 * ErrorT, ResolveVoid, RethrowT
 *
 * ExeT, ResolveVoid, RejectT
 * ErrorT, ResolveVoid
 *
 * ExeT, ResolveVoid, RejectT
 * ErrorT, RethrowT
 *
 * ExeT, ResolveVoid, RejectT
 * ResolveVoid, RethrowT
 *
 * ExeT, ResolveVoid, RejectT
 * ResolveVoid
 *
 * ExeT, ResolveVoid, RejectT
 * RethrowT
 *
 * ExeT, ResolveVoid, RejectT
 * ErrorT, ResolveVoid, RethrowVoid
 *
 * ExeT, ResolveVoid, RejectT
 * ErrorT, RethrowVoid
 *
 * ExeT, ResolveVoid, RejectT
 * ResolveVoid, RethrowVoid
 *
 * ExeT, ResolveVoid, RejectT
 * RethrowVoid
 * -----------------------------
 * ExeT, ResolveVoid, RejectVoid
 * ResolveVoid, RethrowT
 *
 * ExeT, ResolveVoid, RejectVoid
 * ResolveVoid
 *
 * ExeT, ResolveVoid, RejectVoid
 * RethrowT
 *
 * ExeT, ResolveVoid, RejectVoid
 * ResolveVoid, RethrowVoid
 *
 * ExeT, ResolveVoid, RejectVoid
 * RethrowVoid
 * -----------------------------
 * ExeT, ResolveVoid, RejectUndefined
 * ExeT, ResolveVoid, RejectT
 * ErrorT, ResolveVoid, RethrowT
 * -----------------------------
 * ExeT, ResolveUndefined, RejectT
 * ErrorT, ResolveVoid, RethrowT
 *
 * ExeT, ResolveUndefined, RejectT
 * ErrorT, ResolveVoid
 *
 * ExeT, ResolveUndefined, RejectT
 * ErrorT, RethrowT
 *
 * ExeT, ResolveUndefined, RejectT
 * ResolveVoid, RethrowT
 *
 * ExeT, ResolveUndefined, RejectT
 * ResolveVoid
 *
 * ExeT, ResolveUndefined, RejectT
 * RethrowT
 *
 * ExeT, ResolveUndefined, RejectT
 * ErrorT, ResolveVoid, RethrowVoid
 *
 * ExeT, ResolveUndefined, RejectT
 * ErrorT, RethrowVoid
 *
 * ExeT, ResolveUndefined, RejectT
 * ResolveVoid, RethrowVoid
 *
 * ExeT, ResolveUndefined, RejectT
 * RethrowVoid
 * -----------------------------
 * ExeT, ResolveUndefined, RejectVoid
 * ResolveVoid, RethrowT
 *
 * ExeT, ResolveUndefined, RejectVoid
 * ResolveVoid
 *
 * ExeT, ResolveUndefined, RejectVoid
 * RethrowT
 *
 * ExeT, ResolveUndefined, RejectVoid
 * ResolveVoid, RethrowVoid
 *
 * ExeT, ResolveUndefined, RejectVoid
 * RethrowVoid
 ***/

struct Bools
{
    bool first;
    bool second;
};

class CatcherLambdaResolveRejectRValue: public ::testing::TestWithParam<Bools>
{ };

INSTANTIATE_TEST_CASE_P(
  TestWithParameters, CatcherLambdaResolveRejectRValue, testing::Values(
    Bools{false, false},
    Bools{false, true},
    Bools{true, false},
    Bools{true, true}
  ));

class CatcherLambdaRValue: public ::testing::TestWithParam<bool>
{ };

INSTANTIATE_TEST_CASE_P(
  TestWithParameters, CatcherLambdaRValue, testing::Values(
    false,
    true
  ));

// ExeT, ResolveT, RejectT
// ErrorT, ResolveT, RethrowT
TEST_P(CatcherLambdaResolveRejectRValue, ERRErrorResolveRethrow)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve('w') : reject(5.0);
    })
    .catcher([this](double e, Resolver<char> resolve, Rethrower<int> rethrow) {
        ASSERT_TRUE(5.0 == e);
        return GetParam().second ? resolve('w') : rethrow(3);
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectT
// ErrorT, ResolveT
TEST_P(CatcherLambdaRValue, ERRErrorResolve)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject(5.0);
    })
    .catcher([this](double e, Resolver<char> resolve) {
        ASSERT_TRUE(5.0 == e);
        return resolve('w');
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectT
// ErrorT, RethrowT
TEST_P(CatcherLambdaRValue, ERRExeReject)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject(5.0);
    })
    .catcher([this](double e, Rethrower<int> retchrow) {
        ASSERT_TRUE(5.0 == e);
        return retchrow(5);
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectT
// ResolveT, RethrowT
TEST_P(CatcherLambdaResolveRejectRValue, ERRResolveRethrow)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve('w') : reject(5.0);
    })
    .catcher([this](Resolver<char> resolve, Rethrower<int> rethrow) {
        return GetParam().second ? resolve('e') : rethrow(45);
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectT
// ResolveT
TEST_P(CatcherLambdaRValue, ERRResolve)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject(5.0);
    })
    .catcher([this](Resolver<char> resolve) {
        return resolve('w');
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectT
// RethrowT
TEST_P(CatcherLambdaRValue, ERRRetrow)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject(5.0);
    })
    .catcher([this](Rethrower<int> rethrow) {
        return rethrow(45);
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectT
// ErrorT, ResolveT, RethrowVoid
TEST_P(CatcherLambdaResolveRejectRValue, ERRErrorResolveRethrowVoid)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve('w') : reject(5.0);
    })
    .catcher([this](double e, Resolver<char> resolve, Rethrower<void> rethrow) {
        ASSERT_TRUE(5.0 == e);
        return GetParam().second ? resolve('w') : rethrow();
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectT
// ErrorT, RethrowVoid
TEST_P(CatcherLambdaRValue, ERRErrorRethrowVoid)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject(5.0);
    })
    .catcher([this](double e, Rethrower<void> rethrow) {
        ASSERT_TRUE(5.0 == e);
        return rethrow();
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectT
// ResolveT, RethrowVoid
TEST_P(CatcherLambdaResolveRejectRValue, ERRResolveRethrowVoid)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve('w') : reject(5.0);
    })
    .catcher([this](Resolver<char> resolve, Rethrower<void> rethrow) {
        return GetParam().second ? resolve('w') : rethrow();
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectT
// RethrowVoid
TEST_P(CatcherLambdaRValue, ERRRethrowVoid)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject(5.0);
    })
    .catcher([this](Rethrower<void> rethrow) {
        return rethrow();
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectVoid
// ResolveT, RethrowT
TEST_P(CatcherLambdaResolveRejectRValue, ERRVResolveRethrow)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve('w') : reject();
    })
    .catcher([this](Resolver<char> resolve, Rethrower<int> rethrow) {
        return GetParam().second ? resolve('w') : rethrow(12);
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectVoid
// ResolveT
TEST_P(CatcherLambdaRValue, ERRVResolve)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject();
    })
    .catcher([this](Resolver<char> resolve) {
        return resolve('w');
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectVoid
// RethrowT
TEST_P(CatcherLambdaRValue, ERRVRethrow)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject();
    })
    .catcher([this](Rethrower<char> rethtow) {
        return rethtow('w');
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectVoid
// ResolveT, RethrowVoid
TEST_P(CatcherLambdaResolveRejectRValue, ERRVResolveRethrowVoid)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve('w') : reject();
    })
    .catcher([this](Resolver<char> resolve, Rethrower<void> rethrow) {
        return GetParam().second ? resolve('w') : rethrow();
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectVoid
// RethrowVoid
TEST_P(CatcherLambdaRValue, ERRVRethrowVoid)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject();
    })
    .catcher([this](Rethrower<void> rethrow) {
        return rethrow();
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectUndefined
// ExeT, ResolveT, RejectT
// ErrorT, ResolveT
TEST_P(CatcherLambdaResolveRejectRValue, ERRUErrorResolve)
{
    make_promise([](int e, Resolver<char> resolve) {
        ASSERT_TRUE(10 == e);
        return resolve('w');
    })
    .then([this](char e, Resolver<char> resolve, Rejector<int> reject) {
        ASSERT_TRUE('w' == e);
        return GetParam().first ? resolve('w') : reject(89);
    })
    .catcher([](int e, Resolver<char> resolve) {
        ASSERT_TRUE(89 == e);
        return resolve('t');
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectT
// ErrorT, ResolveVoid, RethrowT
TEST_P(CatcherLambdaResolveRejectRValue, ERVRErrorResolveVoidRethrow)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve() : reject(5.0);
    })
    .catcher([this](double e, Resolver<void> resolve, Rethrower<int> rethrow) {
        ASSERT_TRUE(5.0 == e);
        return GetParam().second ? resolve() : rethrow(5);
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectT
// ErrorT, ResolveVoid
TEST_P(CatcherLambdaRValue, ERVRErrorResolveVoid)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve() : reject(5.0);
    })
    .catcher([this](double e, Resolver<void> resolve) {
        ASSERT_TRUE(5.0 == e);
        return resolve();
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectT
// ErrorT, RethrowT
TEST_P(CatcherLambdaRValue, ERVRErrorRethrow)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve() : reject(5.0);
    })
    .catcher([this](double e, Rethrower<int> rethrow) {
        ASSERT_TRUE(5.0 == e);
        return rethrow(1);
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectT
// ResolveVoid, RethrowT
TEST_P(CatcherLambdaResolveRejectRValue, ERVRResolveVoidRethrow)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve() : reject(5.0);
    })
    .catcher([this](Resolver<void> resolve, Rethrower<int> rethrow) {
        return GetParam().second ? resolve() : rethrow(5);
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectT
// ResolveVoid
TEST_P(CatcherLambdaRValue, ERVRResolveVoid)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve() : reject(5.0);
    })
    .catcher([this](Resolver<void> resolve) {
        return resolve();
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectT
// RethrowT
TEST_P(CatcherLambdaRValue, ERVRRethrow)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve() : reject(5.0);
    })
    .catcher([this](Rethrower<int> rethrow) {
        return rethrow(5);
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectT
// ErrorT, ResolveVoid, RethrowVoid
TEST_P(CatcherLambdaResolveRejectRValue, ERVRErrorResolveVoidRethrowVoid)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve() : reject(5.0);
    })
    .catcher([this](double e, Resolver<void> resolve, Rethrower<void> rethrow) {
        ASSERT_TRUE(5.0 == e);
        return GetParam().second ? resolve() : rethrow();
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectT
// ErrorT, RethrowVoid
TEST_P(CatcherLambdaRValue, ERVRErrorRethrowVoid)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve() : reject(5.0);
    })
    .catcher([this](double e, Rethrower<void> rethrow) {
        ASSERT_TRUE(5.0 == e);
        return rethrow();
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectT
// ResolveVoid, RethrowVoid
TEST_P(CatcherLambdaResolveRejectRValue, ERVRResolveVoidRethrowVoid)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve() : reject(5.0);
    })
    .catcher([this](Resolver<void> resolve, Rethrower<void> rethrow) {
        return GetParam().second ? resolve() : rethrow();
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectT
// RethrowVoid
TEST_P(CatcherLambdaRValue, ERVRRethrowVoid)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve() : reject(5.0);
    })
    .catcher([this](Rethrower<void> rethrow) {
        return rethrow();
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectVoid
// ResolveVoid, RethrowT
TEST_P(CatcherLambdaResolveRejectRValue, ERVRVResolveVoidRethrow)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve() : reject();
    })
    .catcher([this](Resolver<void> resolve, Rethrower<int> rethrow) {
        return GetParam().second ? resolve() : rethrow(6);
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectVoid
// ResolveVoid
TEST_P(CatcherLambdaRValue, ERVRVResolveVoid)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve() : reject();
    })
    .catcher([this](Resolver<void> resolve) {
        return resolve();
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectVoid
// RethrowT
TEST_P(CatcherLambdaRValue, ERVRVRthrow)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve() : reject();
    })
    .catcher([this](Rethrower<int> rethrow) {
        return rethrow(8);
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectVoid
// ResolveVoid, RethrowVoid
TEST_P(CatcherLambdaResolveRejectRValue, ERVRVResolveVoidRethrowVoid)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve() : reject();
    })
    .catcher([this](Resolver<void> resolve, Rethrower<void> rethrow) {
        return GetParam().second ? resolve() : rethrow();
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectVoid
// RethrowVoid
TEST_P(CatcherLambdaRValue, ERVRVRthrowVoid)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve() : reject();
    })
    .catcher([this](Rethrower<void> rethrow) {
        return rethrow();
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectUndefined
// ExeT, ResolveVoid, RejectT
// ErrorT, ResolveVoid, RethrowT
TEST_P(CatcherLambdaResolveRejectRValue, ERVRUResolveVoidRrthrow)
{
    make_promise([](int e, Resolver<void> resolve) {
        ASSERT_TRUE(10 == e);
        return resolve();
    })
    .then([this](Resolver<void> resolve, Rejector<double> reject) {
        return GetParam().first ? resolve() : reject(5.0);
    })
    .catcher([this](double e, Resolver<void> resolve, Rethrower<int> rethrow) {
        ASSERT_TRUE(5.0 == e);
        return GetParam().second ? resolve() : rethrow(5);
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectT
// ErrorT, ResolveVoid, RethrowT
TEST_P(CatcherLambdaRValue, ERURErrorResolveVoidRethrow)
{
    make_promise([](int e, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return reject(5.0);
    })
    .catcher([this](double e, Resolver<void> resolve, Rethrower<int> rethrow) {
        ASSERT_TRUE(5.0 == e);
        return GetParam() ? resolve() : rethrow(5);
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectT
// ErrorT, ResolveVoid
TEST(CatcherLambdaRValue, ERURErrorResolveVoid)
{
    make_promise([](int e, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return reject(5.0);
    })
    .catcher([this](double e, Resolver<void> resolve) {
        ASSERT_TRUE(5.0 == e);
        return resolve();
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectT
// ErrorT, RethrowT
TEST(CatcherLambdaRValue, ERURErrorRethrow)
{
    make_promise([](int e, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return reject(5.0);
    })
    .catcher([this](double e, Rethrower<int> rethrow) {
        ASSERT_TRUE(5.0 == e);
        return rethrow(6);
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectT
// ResolveVoid, RethrowT
TEST_P(CatcherLambdaRValue, ERURResolveVoidRethrow)
{
    make_promise([](int e, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return reject(5.0);
    })
    .catcher([this](Resolver<void> resolve, Rethrower<int> rethrow) {
        return GetParam() ? resolve() : rethrow(5);
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectT
// ResolveVoid
TEST(CatcherLambdaRValue, ERURResolveVoid)
{
    make_promise([](int e, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return reject(5.0);
    })
    .catcher([this](Resolver<void> resolve) {
        return resolve();
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectT
// RethrowT
TEST(CatcherLambdaRValue, ERURRethrow)
{
    make_promise([](int e, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return reject(5.0);
    })
    .catcher([this](Rethrower<int> rethrow) {
        return rethrow(4);
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectT
// ErrorT, ResolveVoid, RethrowVoid
TEST_P(CatcherLambdaRValue, ERURErrorResolveVoidRethrowVoid)
{
    make_promise([](int e, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return reject(5.0);
    })
    .catcher([this](double e, Resolver<void> resolve, Rethrower<void> rethrow) {
        ASSERT_TRUE(5.0 == e);
        return GetParam() ? resolve() : rethrow();
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectT
// ErrorT, RethrowVoid
TEST(CatcherLambdaRValue, ERURErrorRethrowVoid)
{
    make_promise([](int e, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return reject(5.0);
    })
    .catcher([this](double e, Rethrower<void> rethrow) {
        ASSERT_TRUE(5.0 == e);
        return rethrow();
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectT
// ResolveVoid, RethrowVoid
TEST_P(CatcherLambdaRValue, ERURResolveVoidRethrowVoid)
{
    make_promise([](int e, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return reject(5.0);
    })
    .catcher([this](Resolver<void> resolve, Rethrower<void> rethrow) {
        return GetParam() ? resolve() : rethrow();
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectT
// RethrowVoid
TEST(CatcherLambdaRValue, ERURRethrowVoid)
{
    make_promise([](int e, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return reject(5.0);
    })
    .catcher([this](Rethrower<void> rethrow) {
        return rethrow();
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectVoid
// ResolveVoid, RethrowT
TEST_P(CatcherLambdaRValue, ERURVResolveVoidRethrow)
{
    make_promise([](int e, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return reject();
    })
    .catcher([this](Resolver<void> resolve, Rethrower<int> rethrow) {
        return GetParam() ? resolve() : rethrow(5);
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectVoid
// ResolveVoid
TEST(CatcherLambdaRValue, ERURVResolveVoid)
{
    make_promise([](int e, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return reject();
    })
    .catcher([this](Resolver<void> resolve) {
        return resolve();
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectVoid
// RethrowT
TEST(CatcherLambdaRValue, ERURVRethrowT)
{
    make_promise([](int e, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return reject();
    })
    .catcher([this](Rethrower<int> rethrow) {
        return rethrow(2);
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectVoid
// ResolveVoid, RethrowVoid
TEST_P(CatcherLambdaRValue, ERURVResolveVoidRethrowVoid)
{
    make_promise([](int e, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return reject();
    })
    .catcher([this](Resolver<void> resolve, Rethrower<void> rethrow) {
        return GetParam() ? resolve() : rethrow();
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectVoid
// RethrowVoid
TEST(CatcherLambdaRValue, ERURVRethrowVoid)
{
    make_promise([](int e, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return reject();
    })
    .catcher([this](Rethrower<void> rethrow) {
        return rethrow();
    })
    .startExecution(10);
}
