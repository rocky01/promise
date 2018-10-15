#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Promise.hpp"

using namespace prm;

struct Bools
{
    bool first;
    bool second;
};

class CatcherLambdaResolveRejectLValue: public ::testing::TestWithParam<Bools>
{ };

INSTANTIATE_TEST_CASE_P(
  TestWithParameters, CatcherLambdaResolveRejectLValue, testing::Values(
    Bools{false, false},
    Bools{false, true},
    Bools{true, false},
    Bools{true, true}
  ));

// ExeVoid, ResolveT, RejectT
// ExeT, ResolveT, RejectT
TEST_P(CatcherLambdaResolveRejectLValue, ERRErrorResolveRethrow)
{
    auto lv = [this](double e, Resolver<char> resolve, Rethrower<int> rethrow) {
        ASSERT_TRUE(3.0 == e);
        return GetParam().second ? resolve('w') : rethrow(5);
    };

    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve('w') : reject(3.0);
    })
    .catcher(lv)
    .startExecution(10);
}
