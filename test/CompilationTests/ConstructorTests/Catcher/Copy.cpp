#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Promise.hpp"

#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Catcher/Copy/CopyErrorTResolveTRethrowT.hpp"

using namespace prm;

struct Bools
{
    bool first;
    bool second;
};

class CatcherCopyResolveRethrowLValue: public ::testing::TestWithParam<Bools>
{ };

INSTANTIATE_TEST_CASE_P(
  TestWithParameters, CatcherCopyResolveRethrowLValue, testing::Values(
    Bools{false, false},
    Bools{false, true},
    Bools{true, false},
    Bools{true, true}
  ));

// ExeT, ResolveT, RejectT
// ErrorT, ResolveT, RethrowT
TEST_P(CatcherCopyResolveRethrowLValue, ERRExeResolveReject)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<int> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam().first ? resolve('a') : reject(5);
    })
    .catcher(CopyErrorTResolveTRethrowT(GetParam().second))
    .startExecution(10);
}
