#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Promise.hpp"

using namespace prm;
/***
 *
 * 1. make_promise function.
 *
 * We have types:
 * ExeT
 * ExeVoid
 *
 * ResolveT
 * ResolveVoid
 * ResolveUndefined
 *
 * RejectT
 * RejectVoid
 * RejectUndefined
 *
 * There are the following combinations availiable:
 * ExeT, ResolveT, RejectT
 * ExeT, ResolveT, RejectVoid
 * ExeT, ResolveT, RejectUndefined
 *
 * ExeT, ResolveVoid, RejectT
 * ExeT, ResolveVoid, RejectVoid
 * ExeT, ResolveVoid, RejectUndefined
 *
 * ExeT, ResolveUndefined, RejectT
 * ExeT, ResolveUndefined, RejectVoid
 * ExeT, ResolveUndefined, RejectUndefined <- Not supported
 *
 * ExeVoid, ResolveT, RejectT
 * ExeVoid, ResolveT, RejectVoid
 * ExeVoid, ResolveT, RejectUndefined
 *
 * ExeVoid, ResolveVoid, RejectT
 * ExeVoid, ResolveVoid, RejectVoid
 * ExeVoid, ResolveVoid, RejectUndefined
 *
 * ExeVoid, ResolveUndefined, RejectT
 * ExeVoid, ResolveUndefined, RejectVoid
 * ExeVoid, ResolveUndefined, RejectUndefined <- Not supported
 *
 ***/

class MakePromiseLambdaLValue: public ::testing::TestWithParam<bool>
{ };

INSTANTIATE_TEST_CASE_P(
  TestWithParameters, MakePromiseLambdaLValue, testing::Values(
    false,
    true
  ));


// ExeT, ResolveT, RejectT
TEST_P(MakePromiseLambdaLValue, ExeResolveReject)
{
    auto lvalue = [this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject(5.3);
    };

    make_promise(lvalue)
    .startExecution(10);
}

// ExeT, ResolveT, RejectVoid
TEST_P(MakePromiseLambdaLValue, ExeResolveRejectVoid)
{
    auto lvalue = [this](int e, Resolver<char> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject();
    };

    make_promise(lvalue)
    .startExecution(10);
}

// ExeT, ResolveT, RejectUndefined
TEST(MakePromiseLambdaLValue, ExeResolve)
{
    auto lvalue = [](int e, Resolver<char> resolve) {
        ASSERT_TRUE(10 == e);
        return resolve('w');
    };

    make_promise(lvalue)
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectT
TEST_P(MakePromiseLambdaLValue, ExeResolveVoidReject)
{
    auto lvalue = [this](int e, Resolver<void> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve() : reject(5.3);
    };

    make_promise(lvalue)
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectVoid
TEST_P(MakePromiseLambdaLValue, ExeResolveVoidRejectVoid)
{
    auto lvalue = [this](int e, Resolver<void> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve() : reject();
    };

    make_promise(lvalue)
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectUndefined
TEST(MakePromiseLambdaLValue, ExeResolveVoid)
{
    auto lvalue = [](int e, Resolver<void> resolve) {
        ASSERT_TRUE(10 == e);
        return resolve();
    };

    make_promise(lvalue)
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectT
TEST(MakePromiseLambdaLValue, ExeReject)
{
    auto lvalue = [](int e, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return reject(5.3);
    };

    make_promise(lvalue)
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectVoid
TEST(MakePromiseLambdaLValue, ExeRejectVoid)
{
    auto lvalue = [](int e, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return reject();
    };

    make_promise(lvalue)
    .startExecution(10);
}

// ExeVoid, ResolveT, RejectT
TEST_P(MakePromiseLambdaLValue, ResolveReject)
{
    auto lvalue = [this](Resolver<char> resolve, Rejector<double> reject) {
        return GetParam() ? resolve('w') : reject(5.3);
    };

    make_promise(lvalue)
    .startExecution();
}

// ExeVoid, ResolveT, RejectVoid
TEST_P(MakePromiseLambdaLValue, ResolveRejectVoid)
{
    auto lvalue = [this](Resolver<char> resolve, Rejector<void> reject) {
        return GetParam() ? resolve('w') : reject();
    };

    make_promise(lvalue)
    .startExecution();
}

// ExeVoid, ResolveT, RejectUndefined
TEST(MakePromiseLambdaLValue, Resolve)
{
    auto lvalue = [](Resolver<char> resolve) {
        return resolve('w');
    };

    make_promise(lvalue)
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectT
TEST_P(MakePromiseLambdaLValue, ResolvVoideReject)
{
    auto lvalue = [this](Resolver<void> resolve, Rejector<double> reject) {
        return GetParam() ? resolve() : reject(5.3);
    };

    make_promise(lvalue)
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectVoid
TEST_P(MakePromiseLambdaLValue, ResolvVoideRejectVoid)
{
    auto lvalue = [this](Resolver<void> resolve, Rejector<void> reject) {
        return GetParam() ? resolve() : reject();
    };

    make_promise(lvalue)
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectUndefined
TEST(MakePromiseLambdaLValue, ResolvVoide)
{
    auto lvalue = [](Resolver<void> resolve) {
        return resolve();
    };

    make_promise(lvalue)
    .startExecution();
}

// ExeVoid, ResolveUndefined, RejectT
TEST(MakePromiseLambdaLValue, Reject)
{
    auto lvalue = [](Rejector<double> reject) {
        return reject(5.3);
    };

    make_promise(lvalue)
    .startExecution();
}

// ExeVoid, ResolveUndefined, RejectVoid
TEST(MakePromiseLambdaLValue, RejectVoid)
{
    auto lvalue = [](Rejector<void> reject) {
        return reject();
    };

    make_promise(lvalue)
    .startExecution();
}
