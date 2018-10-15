#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Promise.hpp"

#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Ever/Move/MoveResolveTErrorT.hpp"

using namespace prm;

class EverMove: public ::testing::TestWithParam<bool>
{ };

INSTANTIATE_TEST_CASE_P(
  TestWithParameters, EverMove, testing::Values(
    false,
    true
  ));

// ExeT, ResolveT, RejectT
// Finish
TEST_P(EverMove, ERRFinish)
{
    make_promise([this](int e, Resolver<char> resolve, Rejector<int> reject) {
        ASSERT_TRUE(10 == e);
        return GetParam() ? resolve('a') : reject(5);
    })
    .ever(MoveResolveTErrorT())
    .startExecution(10);
}
