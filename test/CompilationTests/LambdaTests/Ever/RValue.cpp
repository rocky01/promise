#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Promise.hpp"

using namespace prm;
/***
 *
 * 1. Ever function.
 *
 * We have types:
 * Finish
 *
 * ReportT
 *
 * There are the following combinations availiable:
 * Finish, ReportT
 * Finish
 *
 * There are the following combinations with make_promise availiable:
 * -----------------------------
 * ExeT, ResolveT, RejectT
 * Finish, ReportT
 *
 * ExeT, ResolveT, RejectT
 * Finish
 * -----------------------------
 * ExeT, ResolveT, RejectVoid
 * Finish, ReportT
 *
 * ExeT, ResolveT, RejectVoid
 * Finish
 * -----------------------------
 * ExeT, ResolveT, RejectUndefined
 * Finish, ReportT
 *
 * ExeT, ResolveT, RejectUndefined
 * Finish
 * -----------------------------
 * ExeT, ResolveVoid, RejectT
 * Finish, ReportT
 *
 * ExeT, ResolveVoid, RejectT
 * Finish
 * -----------------------------
 * ExeT, ResolveVoid, RejectVoid
 * Finish, ReportT
 *
 * ExeT, ResolveVoid, RejectVoid
 * Finish
 * -----------------------------
 * ExeT, ResolveVoid, RejectUndefined
 * Finish, ReportT
 *
 * ExeT, ResolveVoid, RejectUndefined
 * Finish
 * -----------------------------
 * ExeT, ResolveUndefined, RejectT
 * Finish, ReportT
 *
 * ExeT, ResolveUndefined, RejectT
 * Finish
 * -----------------------------
 * ExeT, ResolveUndefined, RejectVoid
 * Finish, ReportT
 *
 * ExeT, ResolveUndefined, RejectVoid
 * Finish
 ***/

class EverLambdaRValue: public ::testing::TestWithParam<bool>
{ };

INSTANTIATE_TEST_CASE_P(
  TestWithParameters, EverLambdaRValue, testing::Values(
    false,
    true
  ));

// ExeT, ResolveT, RejectT
// Finish, ReportT
TEST_P(EverLambdaRValue, ERRFinishReportT)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject(5.3);
    })
    .ever([this](Finisher finish, Reporter<char, double> report) {
        if (GetParam())
        {
            ASSERT_TRUE(report.isResolved());
            ASSERT_FALSE(report.isRejected());
        }
        else
        {
            ASSERT_TRUE(report.isRejected());
            ASSERT_FALSE(report.isResolved());
        }
        return finish();
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectT : ResolveT == RejectT
// Finish, ReportT
TEST_P(EverLambdaRValue, ERRFinishReportTTheSameResolveTAndRejectT)
{
    make_promise([this](int e, Resolver<int> resolve, Rejector<int> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve(3) : reject(7);
    })
    .ever([this](Finisher finish, Reporter<int, int> report) {
        if (GetParam())
        {
            ASSERT_TRUE(report.isResolved());
            ASSERT_FALSE(report.isRejected());
        }
        else
        {
            ASSERT_TRUE(report.isRejected());
            ASSERT_FALSE(report.isResolved());
        }
        return finish();
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectT
// Finish
TEST_P(EverLambdaRValue, ERRFinish)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject(5.3);
    })
    .ever([](Finisher finish) {
        return finish();
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectVoid
// Finish, ReportT
TEST_P(EverLambdaRValue, ERRVFinishReportT)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject();
    })
    .ever([this](Finisher finish, Reporter<char, void> report) {
        if (GetParam())
        {
            ASSERT_TRUE(report.isResolved());
            ASSERT_FALSE(report.isRejected());
        }
        else
        {
            ASSERT_TRUE(report.isRejected());
            ASSERT_FALSE(report.isResolved());
        }
        return finish();
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectVoid
// Finish
TEST_P(EverLambdaRValue, ERRVFinish)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject();
    })
    .ever([](Finisher finish) {
        return finish();
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectUndefined
// Finish, ReportT
TEST(EverLambdaRValue, ERRUFinishReportT)
{
    make_promise([](int e, Resolver<char> resolve) {
        ASSERT_TRUE(10 == e);
        return resolve('w');
    })
    .ever([this](Finisher finish, Reporter<char, ErrorTypeUndefined> report) {
        ASSERT_TRUE(report.isResolved());
        ASSERT_FALSE(report.isRejected());
        return finish();
    })
    .startExecution(10);
}

// ExeT, ResolveT, RejectUndefined
// Finish
TEST(EverLambdaRValue, ERRUFinish)
{
    make_promise([](int e, Resolver<char> resolve) {
        ASSERT_TRUE(10 == e);
        return resolve('w');
    })
    .ever([](Finisher finish) {
        return finish();
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectT
// Finish, ReportT
TEST_P(EverLambdaRValue, ERVRFinishReportT)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve() : reject(5.3);
    })
    .ever([this](Finisher finish, Reporter<void, double> report) {
        if (GetParam())
        {
            ASSERT_TRUE(report.isResolved());
            ASSERT_FALSE(report.isRejected());
        }
        else
        {
            ASSERT_TRUE(report.isRejected());
            ASSERT_FALSE(report.isResolved());
        }
        return finish();
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectT
// Finish
TEST_P(EverLambdaRValue, ERVRFinish)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve() : reject(5.3);
    })
    .ever([](Finisher finish) {
        return finish();
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectVoid
// Finish, ReportT
TEST_P(EverLambdaRValue, ERVRVFinishReportT)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve() : reject();
    })
    .ever([this](Finisher finish, Reporter<void, void> report) {
        if (GetParam())
        {
            ASSERT_TRUE(report.isResolved());
            ASSERT_FALSE(report.isRejected());
        }
        else
        {
            ASSERT_TRUE(report.isRejected());
            ASSERT_FALSE(report.isResolved());
        }
        return finish();
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectVoid
// Finish
TEST_P(EverLambdaRValue, ERVRVFinish)
{
    make_promise([this](int e, Resolver<void> resolve, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve() : reject();
    })
    .ever([](Finisher finish) {
        return finish();
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectUndefined
// Finish, ReportT
TEST(EverLambdaRValue, ERVRUFinishReportT)
{
    make_promise([](int e, Resolver<void> resolve) {
        ASSERT_TRUE(10 == e);
        return resolve();
    })
    .ever([this](Finisher finish, Reporter<void, ErrorTypeUndefined> report) {
        ASSERT_TRUE(report.isResolved());
        ASSERT_FALSE(report.isRejected());
        return finish();
    })
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectUndefined
// Finish
TEST(EverLambdaRValue, ERVRUFinish)
{
    make_promise([](int e, Resolver<void> resolve) {
        ASSERT_TRUE(10 == e);
        return resolve();
    })
    .ever([](Finisher finish) {
        return finish();
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectT
// Finish, ReportT
TEST(EverLambdaRValue, ERURFinishReportT)
{
    make_promise([](int e, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return reject(5.3);
    })
    .ever([this](Finisher finish, Reporter<ResolveArgTypeUndefined, double> report) {
        ASSERT_FALSE(report.isResolved());
        ASSERT_TRUE(report.isRejected());
        return finish();
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectT
// Finish
TEST(EverLambdaRValue, ERURFinish)
{
    make_promise([](int e, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return reject(5.3);
    })
    .ever([](Finisher finish) {
        return finish();
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectVoid
// Finish, ReportT
TEST(EverLambdaRValue, ERURVFinishReportT)
{
    make_promise([](int e, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return reject();
    })
    .ever([this](Finisher finish, Reporter<ResolveArgTypeUndefined, void> report) {
        ASSERT_FALSE(report.isResolved());
        ASSERT_TRUE(report.isRejected());
        return finish();
    })
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectVoid
// Finish
TEST(EverLambdaRValue, ERURVFinish)
{
    make_promise([](int e, Rejector<void> reject) {
        ASSERT_TRUE(10 == e);
        return reject();
    })
    .ever([](Finisher finish) {
        return finish();
    })
    .startExecution(10);
}
