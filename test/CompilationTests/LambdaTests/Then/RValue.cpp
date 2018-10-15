#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Promise.hpp"

using namespace prm;
/***
 *
 * 1. Then function.
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
 * There are the following combinations with make_promise availiable:
 * -----------------------------
 * ExeT, ResolveT, RejectT
 * ExeT, ResolveT, RejectT
 *
 * ExeT, ResolveT, RejectT
 * ExeT, ResolveT
 *
 * ExeT, ResolveT, RejectT
 * ResolveT, RejectT
 *
 * ExeT, ResolveT, RejectT
 * ResolveT
 *
 * ExeT, ResolveT, RejectT
 * ExeT, RejectT
 *
 * ExeT, ResolveT, RejectT
 * RejectT
 *
 * ExeT, ResolveT, RejectT
 * ExeT, ResolveVoid, RejectT
 *
 * ExeT, ResolveT, RejectT
 * ExeT, ResolveVoid
 *
 * ExeT, ResolveT, RejectT
 * ResolveVoid, RejectT
 *
 * ExeT, ResolveT, RejectT
 * ResolveVoid
 * -----------------------------
 * ExeT, ResolveT, RejectVoid
 * ExeT, ResolveT, RejectVoid
 *
 * ExeT, ResolveT, RejectVoid
 * ExeT, ResolveT
 *
 * ExeT, ResolveT, RejectVoid
 * ResolveT, RejectVoid
 *
 * ExeT, ResolveT, RejectVoid
 * ResolveT
 *
 * ExeT, ResolveT, RejectVoid
 * ExeT, RejectVoid
 *
 * ExeT, ResolveT, RejectVoid
 * RejectVoid
 * -----------------------------
 * ExeT, ResolveT, RejectUndefined
 * ExeT, ResolveT, RejectUndefined
 *
 * ExeT, ResolveT, RejectUndefined
 * ExeT, ResolveT, RejectT
 *
 * ExeT, ResolveT, RejectUndefined
 * ExeT, ResolveT, RejectVoid
 *
 * ExeT, ResolveT, RejectUndefined
 * ResolveT, RejectUndefined
 * -----------------------------
 * ExeT, ResolveVoid, RejectT
 * ResolveVoid, RejectT
 *
 * ExeT, ResolveVoid, RejectT
 * ResolveVoid
 *
 * ExeT, ResolveVoid, RejectT
 * RejectT
 *
 * ExeT, ResolveVoid, RejectT
 * ResolveT, RejectT
 *
 * ExeT, ResolveVoid, RejectT
 * ResolveT
 * -----------------------------
 * ExeT, ResolveVoid, RejectVoid
 * ResolveVoid, RejectVoid
 *
 * ExeT, ResolveVoid, RejectVoid
 * ResolveVoid
 *
 * ExeT, ResolveVoid, RejectVoid
 * RejectVoid
 *
 * ExeT, ResolveVoid, RejectVoid
 * ResolveT, RejectVoid
 *
 * ExeT, ResolveVoid, RejectVoid
 * ResolveT
 * -----------------------------
 * ExeT, ResolveVoid, RejectUndefined
 * ResolveVoid, RejectUndefined
 *
 * ExeT, ResolveVoid, RejectUndefined
 * ResolveVoid, RejectT
 *
 * ExeT, ResolveVoid, RejectUndefined
 * ResolveVoid, RejectVoid
 *
 * ExeT, ResolveVoid, RejectUndefined
 * RejectT
 *
 * ExeT, ResolveVoid, RejectUndefined
 * RejectVoid
 *
 * ExeT, ResolveVoid, RejectUndefined
 * ResolveT, RejectT
 *
 * ExeT, ResolveVoid, RejectUndefined
 * ResolveT, RejectVoid
 *
 * ExeT, ResolveVoid, RejectUndefined
 * ResolveT
 * -----------------------------
 * ExeT, ResolveUndefined, RejectT
 * RejectT
 *
 * ExeT, ResolveUndefined, RejectT
 * ResolveT, RejectT
 *
 * ExeT, ResolveUndefined, RejectT
 * ResolveVoid, RejectT
 *
 * ExeT, ResolveUndefined, RejectT
 * ResolveT
 *
 * ExeT, ResolveUndefined, RejectT
 * ResolveVoid
 * -----------------------------
 * ExeT, ResolveUndefined, RejectVoid
 * RejectVoid
 *
 * ExeT, ResolveUndefined, RejectVoid
 * ResolveT, RejectVoid
 *
 * ExeT, ResolveUndefined, RejectVoid
 * ResolveVoid, RejectVoid
 *
 * ExeT, ResolveUndefined, RejectVoid
 * ResolveT
 *
 * ExeT, ResolveUndefined, RejectVoid
 * ResolveVoid
 * -----------------------------just repit because ExeVoid do not affect next promise-----------------------------
 * ExeVoid, ResolveT, RejectT
 * ExeT, ResolveT, RejectT
 *
 * ExeVoid, ResolveT, RejectT
 * ExeT, ResolveT
 *
 * ExeVoid, ResolveT, RejectT
 * ResolveT, RejectT
 *
 * ExeVoid, ResolveT, RejectT
 * ResolveT
 *
 * ExeVoid, ResolveT, RejectT
 * ExeT, RejectT
 *
 * ExeVoid, ResolveT, RejectT
 * RejectT
 *
 * ExeVoid, ResolveT, RejectT
 * ExeT, ResolveVoid, RejectT
 *
 * ExeVoid, ResolveT, RejectT
 * ExeT, ResolveVoid
 *
 * ExeVoid, ResolveT, RejectT
 * ResolveVoid, RejectT
 *
 * ExeVoid, ResolveT, RejectT
 * ResolveVoid
 * -----------------------------
 * ExeVoid, ResolveT, RejectVoid
 * ExeT, ResolveT, RejectVoid
 *
 * ExeVoid, ResolveT, RejectVoid
 * ExeT, ResolveT
 *
 * ExeVoid, ResolveT, RejectVoid
 * ResolveT, RejectVoid
 *
 * ExeVoid, ResolveT, RejectVoid
 * ResolveT
 *
 * ExeVoid, ResolveT, RejectVoid
 * ExeT, RejectVoid
 *
 * ExeVoid, ResolveT, RejectVoid
 * RejectVoid
 * -----------------------------
 * ExeVoid, ResolveT, RejectUndefined
 * ExeT, ResolveT, RejectUndefined
 *
 * ExeVoid, ResolveT, RejectUndefined
 * ExeT, ResolveT, RejectT
 *
 * ExeVoid, ResolveT, RejectUndefined
 * ExeT, ResolveT, RejectVoid
 *
 * ExeVoid, ResolveT, RejectUndefined
 * ResolveT, RejectUndefined
 * -----------------------------
 * ExeVoid, ResolveVoid, RejectT
 * ResolveVoid, RejectT
 *
 * ExeVoid, ResolveVoid, RejectT
 * ResolveVoid
 *
 * ExeVoid, ResolveVoid, RejectT
 * RejectT
 *
 * ExeVoid, ResolveVoid, RejectT
 * ResolveT, RejectT
 *
 * ExeVoid, ResolveVoid, RejectT
 * ResolveT
 * -----------------------------
 * ExeVoid, ResolveVoid, RejectVoid
 * ResolveVoid, RejectVoid
 *
 * ExeVoid, ResolveVoid, RejectVoid
 * ResolveVoid
 *
 * ExeVoid, ResolveVoid, RejectVoid
 * RejectVoid
 *
 * ExeVoid, ResolveVoid, RejectVoid
 * ResolveT, RejectVoid
 *
 * ExeVoid, ResolveVoid, RejectVoid
 * ResolveT
 * -----------------------------
 * ExeVoid, ResolveVoid, RejectUndefined
 * ResolveVoid, RejectUndefined
 *
 * ExeVoid, ResolveVoid, RejectUndefined
 * ResolveVoid, RejectT
 *
 * ExeVoid, ResolveVoid, RejectUndefined
 * ResolveVoid, RejectVoid
 *
 * ExeVoid, ResolveVoid, RejectUndefined
 * RejectT
 *
 * ExeVoid, ResolveVoid, RejectUndefined
 * RejectVoid
 *
 * ExeVoid, ResolveVoid, RejectUndefined
 * ResolveT, RejectT
 *
 * ExeVoid, ResolveVoid, RejectUndefined
 * ResolveT, RejectVoid
 *
 * ExeVoid, ResolveVoid, RejectUndefined
 * ResolveT
 * -----------------------------
 * ExeVoid, ResolveUndefined, RejectT
 * RejectT
 *
 * ExeVoid, ResolveUndefined, RejectT
 * ResolveT, RejectT
 *
 * ExeVoid, ResolveUndefined, RejectT
 * ResolveVoid, RejectT
 *
 * ExeVoid, ResolveUndefined, RejectT
 * ResolveT
 *
 * ExeVoid, ResolveUndefined, RejectT
 * ResolveVoid
 * -----------------------------
 * ExeVoid, ResolveUndefined, RejectVoid
 * RejectT
 *
 * ExeVoid, ResolveUndefined, RejectVoid
 * ResolveT, RejectT
 *
 * ExeVoid, ResolveUndefined, RejectVoid
 * ResolveVoid, RejectT
 *
 * ExeVoid, ResolveUndefined, RejectVoid
 * ResolveT
 *
 * ExeVoid, ResolveUndefined, RejectVoid
 * ResolveVoid
 ***/

struct Bools
{
    bool first;
    bool second;
};

class ThenLambdaResolveRejectRValue: public ::testing::TestWithParam<Bools>
{ };

INSTANTIATE_TEST_CASE_P(
  TestWithParameters, ThenLambdaResolveRejectRValue, testing::Values(
    Bools{false, false},
    Bools{false, true},
    Bools{true, false},
    Bools{true, true}
  ));

class ThenLambdaRValue: public ::testing::TestWithParam<bool>
{ };

INSTANTIATE_TEST_CASE_P(
  TestWithParameters, ThenLambdaRValue, testing::Values(
    false,
    true
  ));

// ExeVoid, ResolveT, RejectT
// ExeT, ResolveT, RejectT
TEST_P(ThenLambdaResolveRejectRValue, ERRExeResolveReject)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve('w') : reject(5.3);
    })
    .then([this](char e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE('w' == e);
        return GetParam().second ? resolve('w') : reject(5.3);
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectT
// ExeT, ResolveT
TEST_P(ThenLambdaRValue, ERRExeResolve)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject(5.3);
    })
    .then([this](char e, Resolver<char> resolve) {
        ASSERT_TRUE('w' == e);
        return resolve('w');
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectT
// ResolveT, RejectT
TEST_P(ThenLambdaResolveRejectRValue, ERRResolveReject)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve('w') : reject(5.3);
    })
    .then([this](Resolver<char> resolve, Rejector<double> reject) {
        return GetParam().second ? resolve('e') : reject(45.3);
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectT
// ResolveT
TEST_P(ThenLambdaRValue, ERRResolve)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject(5.3);
    })
    .then([this](Resolver<char> resolve) {
        return resolve('w');
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectT
// ExeT, RejectT
TEST_P(ThenLambdaRValue, ERRExeReject)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject(5.3);
    })
    .then([this](char e, Rejector<double> reject) {
        ASSERT_TRUE('w' == e);
        return reject(5.3);
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectT
// RejectT
TEST_P(ThenLambdaRValue, ERRReject)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject(5.3);
    })
    .then([this](Rejector<double> reject) {
        return reject(45.3);
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectT
// ExeT, ResolveVoid, RejectT
TEST_P(ThenLambdaResolveRejectRValue, ERRExeResolveVoidReject)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve('w') : reject(5.3);
    })
    .then([this](char e, Resolver<void> resolve, Rejector<double> reject) {
        ASSERT_TRUE('w' == e);
        return GetParam().second ? resolve() : reject(5.3);
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectT
// ExeT, ResolveVoid
TEST_P(ThenLambdaRValue, ERRExeResolveVoid)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject(5.3);
    })
    .then([this](char e, Resolver<void> resolve) {
        ASSERT_TRUE('w' == e);
        return resolve();
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectT
// ResolveVoid, RejectT
TEST_P(ThenLambdaResolveRejectRValue, ERRResolveVoidReject)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve('w') : reject(5.3);
    })
    .then([this](Resolver<void> resolve, Rejector<double> reject) {
        return GetParam().second ? resolve() : reject(5.3);
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectT
// ResolveVoid
TEST_P(ThenLambdaRValue, ERRResolveVoid)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject(5.3);
    })
    .then([this](Resolver<void> resolve) {
        return resolve();
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectVoid
// ExeT, ResolveT, RejectVoid
TEST_P(ThenLambdaResolveRejectRValue, ERRVExeResolveRejectVoid)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve('w') : reject();
    })
    .then([this](char e, Resolver<char> resolve, Rejector<void> reject) {
        ASSERT_TRUE('w' == e);
        return GetParam().second ? resolve('w') : reject();
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectVoid
// ExeT, ResolveT
TEST_P(ThenLambdaRValue, ERRVExeResolve)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject();
    })
    .then([this](char e, Resolver<char> resolve) {
        ASSERT_TRUE('w' == e);
        return resolve('w');
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectVoid
// ResolveT, RejectVoid
TEST_P(ThenLambdaResolveRejectRValue, ERRVResolveRejectVoid)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve('w') : reject();
    })
    .then([this](Resolver<char> resolve, Rejector<void> reject) {
        return GetParam().second ? resolve('w') : reject();
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectVoid
// ResolveT
TEST_P(ThenLambdaRValue, ERRVResolve)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject();
    })
    .then([this](Resolver<char> resolve) {
        return resolve('w');
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectVoid
// ExeT, RejectVoid
TEST_P(ThenLambdaRValue, ERRVExeRejectVoid)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject();
    })
    .then([this](char e, Rejector<void> reject) {
        ASSERT_TRUE('w' == e);
        return reject();
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectVoid
// RejectVoid
TEST_P(ThenLambdaRValue, ERRVRejectVoid)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject();
    })
    .then([this](Rejector<void> reject) {
        return reject();
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectUndefined
// ExeT, ResolveT, RejectUndefined
TEST(ThenLambdaRValue, ERRUExeResolve)
{
    make_promise([](int e, Resolver<char> resolve) {
        ASSERT_TRUE(10 == e);
        return resolve('w');
    })
    .then([](char e, Resolver<char> resolve) {
        ASSERT_TRUE('w' == e);
        return resolve('w');
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectUndefined
// ExeT, ResolveT, RejectT
TEST_P(ThenLambdaRValue, ERRUExeResolveRject)
{
    make_promise([](int e, Resolver<char> resolve) {
        ASSERT_TRUE(10 == e);
        return resolve('w');
    })
    .then([this](char e, Resolver<char> resolve, Rejector<int> reject) {
        ASSERT_TRUE('w' == e);
        return GetParam() ? resolve('w') : reject(10);
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectUndefined
// ExeT, ResolveT, RejectVoid
TEST_P(ThenLambdaRValue, ERRUExeResolveRjectVoid)
{
    make_promise([](int e, Resolver<char> resolve) {
        ASSERT_TRUE(10 == e);
        return resolve('w');
    })
    .then([this](char e, Resolver<char> resolve, Rejector<void> reject) {
        ASSERT_TRUE('w' == e);
        return GetParam() ? resolve('w') : reject();
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectUndefined
// ResolveT, RejectUndefined
TEST(ThenLambdaRValue, ERRUResolve)
{
    make_promise([](int e, Resolver<char> resolve) {
        ASSERT_TRUE(10 == e);
        return resolve('w');
    })
    .then([this](Resolver<char> resolve) {
        return resolve('w');
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectT
// ResolveVoid, RejectT
TEST_P(ThenLambdaResolveRejectRValue, ERVRResolveVoidReject)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve() : reject(5.3);
    })
    .then([this](Resolver<void> resolve, Rejector<double> reject) {
        return GetParam().second ? resolve() : reject(5.3);
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectT
// ResolveVoid
TEST_P(ThenLambdaRValue, ERVRResolveVoid)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve() : reject(5.3);
    })
    .then([this](Resolver<void> resolve) {
        return resolve();
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectT
// RejectT
TEST_P(ThenLambdaRValue, ERVRReject)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve() : reject(5.3);
    })
    .then([this](Rejector<double> reject) {
        return reject(5.3);
    })
    .startExecution(10);
}
// ExeT, ResolveVoid, RejectT
// ResolveT, RejectT
TEST_P(ThenLambdaResolveRejectRValue, ERVRResolveReject)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve() : reject(5.3);
    })
    .then([this](Resolver<int> resolve, Rejector<double> reject) {
        return GetParam().second ? resolve(12) : reject(5.3);
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectT
// ResolveT
TEST_P(ThenLambdaRValue, ERVRResolve)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve() : reject(5.3);
    })
    .then([this](Resolver<int> resolve) {
        return resolve(12);
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectVoid
// ResolveVoid, RejectVoid
TEST_P(ThenLambdaResolveRejectRValue, ERVRVResolveVoidRejectVoid)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve() : reject();
    })
    .then([this](Resolver<void> resolve, Rejector<void> reject) {
        return GetParam().second ? resolve() : reject();
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectVoid
// ResolveVoid
TEST_P(ThenLambdaRValue, ERVRVResolveVoid)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve() : reject();
    })
    .then([this](Resolver<void> resolve) {
        return resolve();
    })
    .startExecution(10);
}
// ExeT, ResolveVoid, RejectVoid
// RejectVoid
TEST_P(ThenLambdaRValue, ERVRVRejectVoid)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve() : reject();
    })
    .then([this](Rejector<void> reject) {
        return reject();
    })
    .startExecution(10);
}
// ExeT, ResolveVoid, RejectVoid
// ResolveT, RejectVoid
TEST_P(ThenLambdaResolveRejectRValue, ERVRVResolveRejectVoid)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve() : reject();
    })
    .then([this](Resolver<int> resolve, Rejector<void> reject) {
        return GetParam().second ? resolve(45) : reject();
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectVoid
// ResolveT
TEST_P(ThenLambdaRValue, ERVRVResolve)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve() : reject();
    })
    .then([this](Resolver<int> resolve) {
        return resolve(45);
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectUndefined
// ResolveVoid, RejectUndefined
TEST(ThenLambdaRValue, ERVRUResolveVoid)
{
    make_promise([](int e, Resolver<void> resolve) {
        ASSERT_TRUE(10 == e);
        return resolve();
    })
    .then([](Resolver<void> resolve) {
        return resolve();
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectUndefined
// ResolveVoid, RejectT
TEST_P(ThenLambdaRValue, ERVRUResolveVoidReject)
{
    make_promise([](int e, Resolver<void> resolve) {
        ASSERT_TRUE(10 == e);
        return resolve();
    })
    .then([this](Resolver<void> resolve, Rejector<int> reject) {
        return GetParam() ? resolve() : reject(14);
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectUndefined
// ResolveVoid, RejectVoid
TEST_P(ThenLambdaRValue, ERVRUResolveVoidRejectVoid)
{
    make_promise([](int e, Resolver<void> resolve) {
        ASSERT_TRUE(10 == e);
        return resolve();
    })
    .then([this](Resolver<void> resolve, Rejector<void> reject) {
        return GetParam() ? resolve() : reject();
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectUndefined
// RejectT
TEST(ThenLambdaRValue, ERVRUReject)
{
    make_promise([](int e, Resolver<void> resolve) {
        ASSERT_TRUE(10 == e);
        return resolve();
    })
    .then([](Rejector<int> reject) {
        return reject(14);
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectUndefined
// RejectVoid
TEST(ThenLambdaRValue, ERVRURejectVoid)
{
    make_promise([](int e, Resolver<void> resolve) {
        ASSERT_TRUE(10 == e);
        return resolve();
    })
    .then([](Rejector<void> reject) {
        return reject();
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectUndefined
// ResolveT, RejectT
TEST_P(ThenLambdaRValue, ERVRUResolveReject)
{
    make_promise([](int e, Resolver<void> resolve) {
        ASSERT_TRUE(10 == e);
        return resolve();
    })
    .then([this](Resolver<int> resolve, Rejector<int> reject) {
        return GetParam() ? resolve(15) : reject(14);
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectUndefined
// ResolveT, RejectVoid
TEST_P(ThenLambdaRValue, ERVRUResolveRejectVoid)
{
    make_promise([](int e, Resolver<void> resolve) {
        ASSERT_TRUE(10 == e);
        return resolve();
    })
    .then([this](Resolver<int> resolve, Rejector<void> reject) {
        return GetParam() ? resolve(15) : reject();
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectUndefined
// ResolveT
TEST(ThenLambdaRValue, ERVRUResolve)
{
    make_promise([](int e, Resolver<void> resolve) {
        ASSERT_TRUE(10 == e);
        return resolve();
    })
    .then([](Resolver<int> resolve) {
        return resolve(14);
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectT
// RejectT
TEST(ThenLambdaRValue, ERURReject)
{
    make_promise([](int e, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return reject(5.3);
    })
    .then([](Rejector<double> reject) {
        return reject(5.3);
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectT
// ResolveT, RejectT
TEST_P(ThenLambdaRValue, ERURResolveReject)
{
    make_promise([](int e, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return reject(5.3);
    })
    .then([this](Resolver<int> resolve, Rejector<double> reject) {
        return GetParam() ? resolve(43) : reject(5.3);
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectT
// ResolveVoid, RejectT
TEST_P(ThenLambdaRValue, ERURResolveVoidReject)
{
    make_promise([](int e, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return reject(5.3);
    })
    .then([this](Resolver<void> resolve, Rejector<double> reject) {
        return GetParam() ? resolve() : reject(5.3);
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectT
// ResolveT
TEST(ThenLambdaRValue, ERURResolve)
{
    make_promise([](int e, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return reject(5.3);
    })
    .then([](Resolver<int> resolve) {
        return resolve(65);
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectT
// ResolveVoid
TEST(ThenLambdaRValue, ERURResolveVoid)
{
    make_promise([](int e, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return reject(5.3);
    })
    .then([](Resolver<void> resolve) {
        return resolve();
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectVoid
// RejectVoid
TEST(ThenLambdaRValue, ERURVRejectVoid)
{
    make_promise([](int e, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return reject();
    })
    .then([](Rejector<void> reject) {
        return reject();
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectVoid
// ResolveT, RejectVoid
TEST_P(ThenLambdaRValue, ERURVResolveRejectVoid)
{
    make_promise([](int e, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return reject();
    })
    .then([this](Resolver<int> resolve, Rejector<void> reject) {
        return GetParam() ? resolve(12) : reject();
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectVoid
// ResolveVoid, RejectVoid
TEST_P(ThenLambdaRValue, ERURVResolveVoidRejectVoid)
{
    make_promise([](int e, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return reject();
    })
    .then([this](Resolver<void> resolve, Rejector<void> reject) {
        return GetParam() ? resolve() : reject();
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectVoid
// ResolveT
TEST(ThenLambdaRValue, ERURVResolve)
{
    make_promise([](int e, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return reject();
    })
    .then([](Resolver<int> resolve) {
        return resolve(45);
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectVoid
// ResolveVoid
TEST(ThenLambdaRValue, ERURVResolveVoid)
{
    make_promise([](int e, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return reject();
    })
    .then([](Resolver<void> resolve) {
        return resolve();
    })
    .startExecution(10);
}

// -----------------------------just repit because ExeVoid do not affect next promise-----------------------------
// ExeVoid, ResolveT, RejectT
// ExeT, ResolveT, RejectT
TEST_P(ThenLambdaResolveRejectRValue, EVRRExeResolveReject)
{
    make_promise([this](Resolver<char> resolve, Rejector<double> reject) {
        return GetParam().first ? resolve('w') : reject(5.3);
    })
    .then([this](char e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE('w' == e);
        return GetParam().second ? resolve('w') : reject(5.3);
    })
    .startExecution();
}

// ExeVoid, ResolveT, RejectT
// ExeT, ResolveT
TEST_P(ThenLambdaRValue, EVRRExeResolve)
{
    make_promise([this](Resolver<char> resolve, Rejector<double> reject) {
        return GetParam() ? resolve('w') : reject(5.3);
    })
    .then([this](char e, Resolver<char> resolve) {
        ASSERT_TRUE('w' == e);
        return resolve('w');
    })
    .startExecution();
}

// ExeVoid, ResolveT, RejectT
// ResolveT, RejectT
TEST_P(ThenLambdaResolveRejectRValue, EVRRResolveReject)
{
    make_promise([this](Resolver<char> resolve, Rejector<double> reject) {
        return GetParam().first ? resolve('w') : reject(5.3);
    })
    .then([this](Resolver<char> resolve, Rejector<double> reject) {
        return GetParam().second ? resolve('e') : reject(45.3);
    })
    .startExecution();
}

// ExeVoid, ResolveT, RejectT
// ResolveT
TEST_P(ThenLambdaRValue, EVRRResolve)
{
    make_promise([this](Resolver<char> resolve, Rejector<double> reject) {
        return GetParam() ? resolve('w') : reject(5.3);
    })
    .then([this](Resolver<char> resolve) {
        return resolve('w');
    })
    .startExecution();
}

// ExeVoid, ResolveT, RejectT
// ExeT, RejectT
TEST_P(ThenLambdaRValue, EVRRExeReject)
{
    make_promise([this](Resolver<char> resolve, Rejector<double> reject) {
        return GetParam() ? resolve('w') : reject(5.3);
    })
    .then([this](char e, Rejector<double> reject) {
        ASSERT_TRUE('w' == e);
        return reject(5.3);
    })
    .startExecution();
}

// ExeVoid, ResolveT, RejectT
// RejectT
TEST_P(ThenLambdaRValue, EVRRReject)
{
    make_promise([this](Resolver<char> resolve, Rejector<double> reject) {
        return GetParam() ? resolve('w') : reject(5.3);
    })
    .then([this](Rejector<double> reject) {
        return reject(45.3);
    })
    .startExecution();
}

// ExeVoid, ResolveT, RejectT
// ExeT, ResolveVoid, RejectT
TEST_P(ThenLambdaResolveRejectRValue, EVRRExeResolveVoidReject)
{
    make_promise([this](Resolver<char> resolve, Rejector<double> reject) {
        return GetParam().first ? resolve('w') : reject(5.3);
    })
    .then([this](char e, Resolver<void> resolve, Rejector<double> reject) {
        ASSERT_TRUE('w' == e);
        return GetParam().second ? resolve() : reject(5.3);
    })
    .startExecution();
}

// ExeVoid, ResolveT, RejectT
// ExeT, ResolveVoid
TEST_P(ThenLambdaRValue, EVRRExeResolveVoid)
{
    make_promise([this](Resolver<char> resolve, Rejector<double> reject) {
        return GetParam() ? resolve('w') : reject(5.3);
    })
    .then([this](char e, Resolver<void> resolve) {
        ASSERT_TRUE('w' == e);
        return resolve();
    })
    .startExecution();
}

// ExeVoid, ResolveT, RejectT
// ResolveVoid, RejectT
TEST_P(ThenLambdaResolveRejectRValue, EVRRResolveVoidReject)
{
    make_promise([this](Resolver<char> resolve, Rejector<double> reject) {
        return GetParam().first ? resolve('w') : reject(5.3);
    })
    .then([this](Resolver<void> resolve, Rejector<double> reject) {
        return GetParam().second ? resolve() : reject(5.3);
    })
    .startExecution();
}

// ExeVoid, ResolveT, RejectT
// ResolveVoid
TEST_P(ThenLambdaRValue, EVRRResolveVoid)
{
    make_promise([this](Resolver<char> resolve, Rejector<double> reject) {
        return GetParam() ? resolve('w') : reject(5.3);
    })
    .then([this](Resolver<void> resolve) {
        return resolve();
    })
    .startExecution();
}

// ExeVoid, ResolveT, RejectVoid
// ExeT, ResolveT, RejectVoid
TEST_P(ThenLambdaResolveRejectRValue, EVRRVExeResolveRejectVoid)
{
    make_promise([this](Resolver<char> resolve, Rejector<void> reject) {
        return GetParam().first ? resolve('w') : reject();
    })
    .then([this](char e, Resolver<char> resolve, Rejector<void> reject) {
        ASSERT_TRUE('w' == e);
        return GetParam().second ? resolve('w') : reject();
    })
    .startExecution();
}

// ExeVoid, ResolveT, RejectVoid
// ExeT, ResolveT
TEST_P(ThenLambdaRValue, EVRRVExeResolve)
{
    make_promise([this](Resolver<char> resolve, Rejector<void> reject) {
        return GetParam() ? resolve('w') : reject();
    })
    .then([this](char e, Resolver<char> resolve) {
        ASSERT_TRUE('w' == e);
        return resolve('w');
    })
    .startExecution();
}

// ExeVoid, ResolveT, RejectVoid
// ResolveT, RejectVoid
TEST_P(ThenLambdaResolveRejectRValue, EVRRVResolveRejectVoid)
{
    make_promise([this](Resolver<char> resolve, Rejector<void> reject) {
        return GetParam().first ? resolve('w') : reject();
    })
    .then([this](Resolver<char> resolve, Rejector<void> reject) {
        return GetParam().second ? resolve('w') : reject();
    })
    .startExecution();
}

// ExeVoid, ResolveT, RejectVoid
// ResolveT
TEST_P(ThenLambdaRValue, EVRRVResolve)
{
    make_promise([this](Resolver<char> resolve, Rejector<void> reject) {
        return GetParam() ? resolve('w') : reject();
    })
    .then([this](Resolver<char> resolve) {
        return resolve('w');
    })
    .startExecution();
}

// ExeVoid, ResolveT, RejectVoid
// ExeT, RejectVoid
TEST_P(ThenLambdaRValue, EVRRVExeRejectVoid)
{
    make_promise([this](Resolver<char> resolve, Rejector<void> reject) {
        return GetParam() ? resolve('w') : reject();
    })
    .then([this](char e, Rejector<void> reject) {
        ASSERT_TRUE('w' == e);
        return reject();
    })
    .startExecution();
}

// ExeVoid, ResolveT, RejectVoid
// RejectVoid
TEST_P(ThenLambdaRValue, EVRRVRejectVoid)
{
    make_promise([this](Resolver<char> resolve, Rejector<void> reject) {
        return GetParam() ? resolve('w') : reject();
    })
    .then([this](Rejector<void> reject) {
        return reject();
    })
    .startExecution();
}

// ExeVoid, ResolveT, RejectUndefined
// ExeT, ResolveT, RejectUndefined
TEST(ThenLambdaRValue, EVRRUExeResolve)
{
    make_promise([](Resolver<char> resolve) {
        return resolve('w');
    })
    .then([](char e, Resolver<char> resolve) {
        ASSERT_TRUE('w' == e);
        return resolve('w');
    })
    .startExecution();
}

// ExeVoid, ResolveT, RejectUndefined
// ExeT, ResolveT, RejectT
TEST_P(ThenLambdaRValue, EVRRUExeResolveRject)
{
    make_promise([](Resolver<char> resolve) {
        return resolve('w');
    })
    .then([this](char e, Resolver<char> resolve, Rejector<int> reject) {
        ASSERT_TRUE('w' == e);
        return GetParam() ? resolve('w') : reject(10);
    })
    .startExecution();
}

// ExeVoid, ResolveT, RejectUndefined
// ExeT, ResolveT, RejectVoid
TEST_P(ThenLambdaRValue, EVRRUExeResolveRjectVoid)
{
    make_promise([](Resolver<char> resolve) {
        return resolve('w');
    })
    .then([this](char e, Resolver<char> resolve, Rejector<void> reject) {
        ASSERT_TRUE('w' == e);
        return GetParam() ? resolve('w') : reject();
    })
    .startExecution();
}

// ExeVoid, ResolveT, RejectUndefined
// ResolveT, RejectUndefined
TEST(ThenLambdaRValue, EVRRUResolve)
{
    make_promise([](Resolver<char> resolve) {
        return resolve('w');
    })
    .then([this](Resolver<char> resolve) {
        return resolve('w');
    })
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectT
// ResolveVoid, RejectT
TEST_P(ThenLambdaResolveRejectRValue, EVRVRResolveVoidReject)
{
    make_promise([this](Resolver<void> resolve, Rejector<double> reject) {
        return GetParam().first ? resolve() : reject(5.3);
    })
    .then([this](Resolver<void> resolve, Rejector<double> reject) {
        return GetParam().second ? resolve() : reject(5.3);
    })
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectT
// ResolveVoid
TEST_P(ThenLambdaRValue, EVRVRResolveVoid)
{
    make_promise([this](Resolver<void> resolve, Rejector<double> reject) {
        return GetParam() ? resolve() : reject(5.3);
    })
    .then([this](Resolver<void> resolve) {
        return resolve();
    })
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectT
// RejectT
TEST_P(ThenLambdaRValue, EVRVRReject)
{
    make_promise([this](Resolver<void> resolve, Rejector<double> reject) {
        return GetParam() ? resolve() : reject(5.3);
    })
    .then([this](Rejector<double> reject) {
        return reject(5.3);
    })
    .startExecution();
}
// ExeVoid, ResolveVoid, RejectT
// ResolveT, RejectT
TEST_P(ThenLambdaResolveRejectRValue, EVRVRResolveReject)
{
    make_promise([this](Resolver<void> resolve, Rejector<double> reject) {
        return GetParam().first ? resolve() : reject(5.3);
    })
    .then([this](Resolver<int> resolve, Rejector<double> reject) {
        return GetParam().second ? resolve(12) : reject(5.3);
    })
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectT
// ResolveT
TEST_P(ThenLambdaRValue, EVRVRResolve)
{
    make_promise([this](Resolver<void> resolve, Rejector<double> reject) {
        return GetParam() ? resolve() : reject(5.3);
    })
    .then([this](Resolver<int> resolve) {
        return resolve(12);
    })
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectVoid
// ResolveVoid, RejectVoid
TEST_P(ThenLambdaResolveRejectRValue, EVRVRVResolveVoidRejectVoid)
{
    make_promise([this](Resolver<void> resolve, Rejector<void> reject) {
        return GetParam().first ? resolve() : reject();
    })
    .then([this](Resolver<void> resolve, Rejector<void> reject) {
        return GetParam().second ? resolve() : reject();
    })
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectVoid
// ResolveVoid
TEST_P(ThenLambdaRValue, EVRVRVResolveVoid)
{
    make_promise([this](Resolver<void> resolve, Rejector<void> reject) {
        return GetParam() ? resolve() : reject();
    })
    .then([this](Resolver<void> resolve) {
        return resolve();
    })
    .startExecution();
}
// ExeVoid, ResolveVoid, RejectVoid
// RejectVoid
TEST_P(ThenLambdaRValue, EVRVRVRejectVoid)
{
    make_promise([this](Resolver<void> resolve, Rejector<void> reject) {
        return GetParam() ? resolve() : reject();
    })
    .then([this](Rejector<void> reject) {
        return reject();
    })
    .startExecution();
}
// ExeVoid, ResolveVoid, RejectVoid
// ResolveT, RejectVoid
TEST_P(ThenLambdaResolveRejectRValue, EVRVRVResolveRejectVoid)
{
    make_promise([this](Resolver<void> resolve, Rejector<void> reject) {
        return GetParam().first ? resolve() : reject();
    })
    .then([this](Resolver<int> resolve, Rejector<void> reject) {
        return GetParam().second ? resolve(45) : reject();
    })
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectVoid
// ResolveT
TEST_P(ThenLambdaRValue, EVRVRVResolve)
{
    make_promise([this](Resolver<void> resolve, Rejector<void> reject) {
        return GetParam() ? resolve() : reject();
    })
    .then([this](Resolver<int> resolve) {
        return resolve(45);
    })
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectUndefined
// ResolveVoid, RejectUndefined
TEST(ThenLambdaRValue, EVRVRUResolveVoid)
{
    make_promise([](Resolver<void> resolve) {
        return resolve();
    })
    .then([](Resolver<void> resolve) {
        return resolve();
    })
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectUndefined
// ResolveVoid, RejectT
TEST_P(ThenLambdaRValue, EVRVRUResolveVoidReject)
{
    make_promise([](Resolver<void> resolve) {
        return resolve();
    })
    .then([this](Resolver<void> resolve, Rejector<int> reject) {
        return GetParam() ? resolve() : reject(14);
    })
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectUndefined
// ResolveVoid, RejectVoid
TEST_P(ThenLambdaRValue, EVRVRUResolveVoidRejectVoid)
{
    make_promise([](Resolver<void> resolve) {
        return resolve();
    })
    .then([this](Resolver<void> resolve, Rejector<void> reject) {
        return GetParam() ? resolve() : reject();
    })
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectUndefined
// RejectT
TEST(ThenLambdaRValue, EVRVRUReject)
{
    make_promise([](Resolver<void> resolve) {
        return resolve();
    })
    .then([](Rejector<int> reject) {
        return reject(14);
    })
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectUndefined
// RejectVoid
TEST(ThenLambdaRValue, EVRVRURejectVoid)
{
    make_promise([](Resolver<void> resolve) {
        return resolve();
    })
    .then([](Rejector<void> reject) {
        return reject();
    })
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectUndefined
// ResolveT, RejectT
TEST_P(ThenLambdaRValue, EVRVRUResolveReject)
{
    make_promise([](Resolver<void> resolve) {
        return resolve();
    })
    .then([this](Resolver<int> resolve, Rejector<int> reject) {
        return GetParam() ? resolve(15) : reject(14);
    })
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectUndefined
// ResolveT, RejectVoid
TEST_P(ThenLambdaRValue, EVRVRUResolveRejectVoid)
{
    make_promise([](Resolver<void> resolve) {
        return resolve();
    })
    .then([this](Resolver<int> resolve, Rejector<void> reject) {
        return GetParam() ? resolve(15) : reject();
    })
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectUndefined
// ResolveT
TEST(ThenLambdaRValue, EVRVRUResolve)
{
    make_promise([](Resolver<void> resolve) {
        return resolve();
    })
    .then([](Resolver<int> resolve) {
        return resolve(14);
    })
    .startExecution();
}

// ExeVoid, ResolveUndefined, RejectT
// RejectT
TEST(ThenLambdaRValue, EVRURReject)
{
    make_promise([](Rejector<double> reject) {
        return reject(5.3);
    })
    .then([](Rejector<double> reject) {
        return reject(5.3);
    })
    .startExecution();
}

// ExeVoid, ResolveUndefined, RejectT
// ResolveT, RejectT
TEST_P(ThenLambdaRValue, EVRURResolveReject)
{
    make_promise([](Rejector<double> reject) {
        return reject(5.3);
    })
    .then([this](Resolver<int> resolve, Rejector<double> reject) {
        return GetParam() ? resolve(43) : reject(5.3);
    })
    .startExecution();
}

// ExeVoid, ResolveUndefined, RejectT
// ResolveVoid, RejectT
TEST_P(ThenLambdaRValue, EVRURResolveVoidReject)
{
    make_promise([](Rejector<double> reject) {
        return reject(5.3);
    })
    .then([this](Resolver<void> resolve, Rejector<double> reject) {
        return GetParam() ? resolve() : reject(5.3);
    })
    .startExecution();
}

// ExeVoid, ResolveUndefined, RejectT
// ResolveT
TEST(ThenLambdaRValue, EVRURResolve)
{
    make_promise([](Rejector<double> reject) {
        return reject(5.3);
    })
    .then([](Resolver<int> resolve) {
        return resolve(65);
    })
    .startExecution();
}

// ExeVoid, ResolveUndefined, RejectT
// ResolveVoid
TEST(ThenLambdaRValue, EVRURResolveVoid)
{
    make_promise([](Rejector<double> reject) {
        return reject(5.3);
    })
    .then([](Resolver<void> resolve) {
        return resolve();
    })
    .startExecution();
}

// ExeVoid, ResolveUndefined, RejectVoid
// RejectVoid
TEST(ThenLambdaRValue, EVRURVRejectVoid)
{
    make_promise([](Rejector<void> reject) {
        return reject();
    })
    .then([](Rejector<void> reject) {
        return reject();
    })
    .startExecution();
}

// ExeVoid, ResolveUndefined, RejectVoid
// ResolveT, RejectVoid
TEST_P(ThenLambdaRValue, EVRURVResolveRejectVoid)
{
    make_promise([](Rejector<void> reject) {
        return reject();
    })
    .then([this](Resolver<int> resolve, Rejector<void> reject) {
        return GetParam() ? resolve(12) : reject();
    })
    .startExecution();
}

// ExeVoid, ResolveUndefined, RejectVoid
// ResolveVoid, RejectVoid
TEST_P(ThenLambdaRValue, EVRURVResolveVoidRejectVoid)
{
    make_promise([](Rejector<void> reject) {
        return reject();
    })
    .then([this](Resolver<void> resolve, Rejector<void> reject) {
        return GetParam() ? resolve() : reject();
    })
    .startExecution();
}

// ExeVoid, ResolveUndefined, RejectVoid
// ResolveT
TEST(ThenLambdaRValue, EVRURVResolve)
{
    make_promise([](Rejector<void> reject) {
        return reject();
    })
    .then([](Resolver<int> resolve) {
        return resolve(45);
    })
    .startExecution();
}

// ExeVoid, ResolveUndefined, RejectVoid
// ResolveVoid
TEST(ThenLambdaRValue, EVRURVResolveVoid)
{
    make_promise([](Rejector<void> reject) {
        return reject();
    })
    .then([](Resolver<void> resolve) {
        return resolve();
    })
    .startExecution();
}
