#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Promise.hpp"

using namespace prm;

struct Bools
{
    bool first;
    bool second;
};

class ThenLambdaResolveRejectLValue: public ::testing::TestWithParam<Bools>
{ };

INSTANTIATE_TEST_CASE_P(
  TestWithParameters, ThenLambdaResolveRejectLValue, testing::Values(
    Bools{false, false},
    Bools{false, true},
    Bools{true, false},
    Bools{true, true}
  ));

// ExeVoid, ResolveT, RejectT
// ExeT, ResolveT, RejectT
// just one test because rest was check during make_promise tests
TEST_P(ThenLambdaResolveRejectLValue, ERRExeResolveReject)
{
    auto lv = [this](char e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE('w' == e);
        return GetParam().second ? resolve('w') : reject(5.3);
    };

    make_promise([this](int e, Resolver<char> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve('w') : reject(5.3);
    })
    .then(lv)
    .startExecution(10);
}
