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

class MakePromiseLambdaRValue: public ::testing::TestWithParam<bool>
{ };

INSTANTIATE_TEST_CASE_P(
  TestWithParameters, MakePromiseLambdaRValue, testing::Values(
    false,
    true
  ));

// ExeT, ResolveT, RejectT
TEST_P(MakePromiseLambdaRValue, ExeResolveReject)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject(5.3);
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectVoid
TEST_P(MakePromiseLambdaRValue, ExeResolveRejectVoid)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject();
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectUndefined
TEST(MakePromiseLambdaRValue, ExeResolve)
{
    make_promise([](int e, Resolver<char> resolve) {
        ASSERT_TRUE(10 == e);
        return resolve('w');
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectT
TEST_P(MakePromiseLambdaRValue, ExeResolveVoidReject)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve() : reject(5.3);
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectVoid
TEST_P(MakePromiseLambdaRValue, ExeResolveVoidRejectVoid)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve() : reject();
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectUndefined
TEST(MakePromiseLambdaRValue, ExeResolveVoid)
{
    make_promise([](int e, Resolver<void> resolve) {
        ASSERT_TRUE(10 == e);
        return resolve();
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectT
TEST(MakePromiseLambdaRValue, ExeReject)
{
    make_promise([](int e, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return reject(5.3);
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectVoid
TEST(MakePromiseLambdaRValue, ExeRejectVoid)
{
    make_promise([](int e, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return reject();
    })
    .startExecution(10);
}

// ExeVoid, ResolveT, RejectT
TEST_P(MakePromiseLambdaRValue, ResolveReject)
{
    make_promise([this](Resolver<char> resolve, Rejector<double> reject) {
        return GetParam() ? resolve('w') : reject(5.3);
    })
    .startExecution();
}

// ExeVoid, ResolveT, RejectVoid
TEST_P(MakePromiseLambdaRValue, ResolveRejectVoid)
{
    make_promise([this](Resolver<char> resolve, Rejector<void> reject) {
        return GetParam() ? resolve('w') : reject();
    })
    .startExecution();
}

// ExeVoid, ResolveT, RejectUndefined
TEST(MakePromiseLambdaRValue, Resolve)
{
    make_promise([](Resolver<char> resolve) {
        return resolve('w');
    })
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectT
TEST_P(MakePromiseLambdaRValue, ResolvVoideReject)
{
    make_promise([this](Resolver<void> resolve, Rejector<double> reject) {
        return GetParam() ? resolve() : reject(5.3);
    })
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectVoid
TEST_P(MakePromiseLambdaRValue, ResolvVoideRejectVoid)
{
    make_promise([this](Resolver<void> resolve, Rejector<void> reject) {
        return GetParam() ? resolve() : reject();
    })
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectUndefined
TEST(MakePromiseLambdaRValue, ResolvVoide)
{
    make_promise([](Resolver<void> resolve) {
        return resolve();
    })
    .startExecution();
}

// ExeVoid, ResolveUndefined, RejectT
TEST(MakePromiseLambdaRValue, Reject)
{
    make_promise([](Rejector<double> reject) {
        return reject(5.3);
    })
    .startExecution();
}

// ExeVoid, ResolveUndefined, RejectVoid
TEST(MakePromiseLambdaRValue, RejectVoid)
{
    make_promise([](Rejector<void> reject) {
        return reject();
    })
    .startExecution();
}
