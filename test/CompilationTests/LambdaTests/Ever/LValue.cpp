#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Promise.hpp"

using namespace prm;

class EverLValue: public ::testing::TestWithParam<bool>
{ };

INSTANTIATE_TEST_CASE_P(
  TestWithParameters, EverLValue, testing::Values(
    false,
    true
  ));

// ExeT, ResolveT, RejectT
// Finish, ReportT
TEST_P(EverLValue, ERRFinishReportT)
{
    auto lv = [this](Finisher finish, Reporter<char, double> report) {
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
    };

    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('w') : reject(5.3);
    })
    .ever(lv)
    .startExecution(10);
}
