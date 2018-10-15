#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Promise.hpp"

#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Emplace/EmplaceExecuteTResolveTRejectT.hpp"

using namespace prm;

struct Bools
{
    bool first;
    bool second;
};

class ThenEmplaceResolveRejectLValue: public ::testing::TestWithParam<Bools>
{ };

INSTANTIATE_TEST_CASE_P(
  TestWithParameters, ThenEmplaceResolveRejectLValue, testing::Values(
    Bools{false, false},
    Bools{false, true},
    Bools{true, false},
    Bools{true, true}
  ));

// ExeVoid, ResolveT, RejectT
// ExeT, ResolveT, RejectT
// just one test because rest was check during make_promise tests
TEST_P(ThenEmplaceResolveRejectLValue, ERRExeResolveReject)
{
    make_promise([this](int e, Resolver<int> resolve, Rejector<double> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve(25) : reject(5.3);
    })
    .then<EmplaceExecuteTResolveTRejectT>(GetParam().second)
    .startExecution(10);
}
