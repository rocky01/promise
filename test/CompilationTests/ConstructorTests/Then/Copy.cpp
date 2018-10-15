#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Promise.hpp"

#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Copy/CopyExecuteTResolveTRejectT.hpp"

using namespace prm;

struct Bools
{
    bool first;
    bool second;
};

class ThenCopyResolveRejectLValue: public ::testing::TestWithParam<Bools>
{ };

INSTANTIATE_TEST_CASE_P(
  TestWithParameters, ThenCopyResolveRejectLValue, testing::Values(
    Bools{false, false},
    Bools{false, true},
    Bools{true, false},
    Bools{true, true}
  ));

// ExeVoid, ResolveT, RejectT
// ExeT, ResolveT, RejectT
// just one test because rest was check during make_promise tests
TEST_P(ThenCopyResolveRejectLValue, ERRExeResolveReject)
{
    make_promise([this](int e, Resolver<int> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve(20) : reject(5.3);
    })
    .then(CopyExecuteTResolveTRejectT(GetParam().second))
    .startExecution(10);
}
