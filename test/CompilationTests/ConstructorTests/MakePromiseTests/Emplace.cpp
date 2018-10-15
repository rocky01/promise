#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Promise.hpp"

#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Emplace/EmplaceExecuteTResolveUndefinedRejectVoid.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Emplace/EmplaceExecuteVoidResolveTRejectUndefined.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Emplace/EmplaceExecuteVoidResolveTRejectT.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Emplace/EmplaceExecuteTResolveTRejectUndefined.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Emplace/EmplaceExecuteTResolveUndefinedRejectT.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Emplace/EmplaceExecuteTResolveVoidRejectVoid.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Emplace/EmplaceExecuteTResolveVoidRejectUndefined.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Emplace/EmplaceExecuteVoidResolveVoidRejectT.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Emplace/EmplaceExecuteVoidResolveUndefinedRejectT.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Emplace/EmplaceExecuteVoidResolveUndefinedRejectVoid.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Emplace/EmplaceExecuteVoidResolveTRejectVoid.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Emplace/EmplaceExecuteTResolveTRejectT.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Emplace/EmplaceExecuteTResolveTRejectVoid.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Emplace/EmplaceExecuteVoidResolveVoidRejectVoid.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Emplace/EmplaceExecuteVoidResolveVoidRejectUndefined.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Emplace/EmplaceExecuteTResolveVoidRejectT.hpp"


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

class MakePromiseEmplace: public ::testing::TestWithParam<bool>
{ };

INSTANTIATE_TEST_CASE_P(
  TestWithParameters, MakePromiseEmplace, testing::Values(
    false,
    true
  ));


// ExeT, ResolveT, RejectT
TEST_P(MakePromiseEmplace, ExeResolveReject)
{
    make_promise<EmplaceExecuteTResolveTRejectT>(GetParam())
    .startExecution(10);
}

// ExeT, ResolveT, RejectVoid
TEST_P(MakePromiseEmplace, ExeResolveRejectVoid)
{
    make_promise<EmplaceExecuteTResolveTRejectVoid>(GetParam())
    .startExecution(10);
}

// ExeT, ResolveT, RejectUndefined
TEST(MakePromiseEmplace, ExeResolve)
{
    make_promise<EmplaceExecuteTResolveTRejectUndefined>()
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectT
TEST_P(MakePromiseEmplace, ExeResolveVoidReject)
{
    make_promise<EmplaceExecuteTResolveVoidRejectT>(GetParam())
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectVoid
TEST_P(MakePromiseEmplace, ExeResolveVoidRejectVoid)
{
    make_promise<EmplaceExecuteTResolveVoidRejectVoid>(GetParam())
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectUndefined
TEST(MakePromiseEmplace, ExeResolveVoid)
{
    make_promise<EmplaceExecuteTResolveVoidRejectUndefined>()
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectT
TEST(MakePromiseEmplace, ExeReject)
{
    make_promise<EmplaceExecuteTResolveUndefinedRejectT>()
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectVoid
TEST(MakePromiseEmplace, ExeRejectVoid)
{
    make_promise<EmplaceExecuteTResolveUndefinedRejectVoid>()
    .startExecution(10);
}

// ExeVoid, ResolveT, RejectT
TEST_P(MakePromiseEmplace, ResolveReject)
{
    make_promise<EmplaceExecuteVoidResolveVoidRejectT>(GetParam())
    .startExecution();
}

// ExeVoid, ResolveT, RejectVoid
TEST_P(MakePromiseEmplace, ResolveRejectVoid)
{
    make_promise<EmplaceExecuteVoidResolveTRejectT>(GetParam())
    .startExecution();
}

// ExeVoid, ResolveT, RejectUndefined
TEST(MakePromiseEmplace, Resolve)
{
    make_promise<EmplaceExecuteVoidResolveTRejectUndefined>()
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectT
TEST_P(MakePromiseEmplace, ResolvVoideReject)
{
    make_promise<EmplaceExecuteVoidResolveTRejectVoid>(GetParam())
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectVoid
TEST_P(MakePromiseEmplace, ResolvVoideRejectVoid)
{
    make_promise<EmplaceExecuteVoidResolveVoidRejectVoid>(GetParam())
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectUndefined
TEST(MakePromiseEmplace, ResolvVoide)
{
    make_promise<EmplaceExecuteVoidResolveVoidRejectUndefined>()
    .startExecution();
}

// ExeVoid, ResolveUndefined, RejectT
TEST(MakePromiseEmplace, Reject)
{
    make_promise<EmplaceExecuteVoidResolveUndefinedRejectT>()
    .startExecution();
}

// ExeVoid, ResolveUndefined, RejectVoid
TEST(MakePromiseEmplace, RejectVoid)
{
    make_promise<EmplaceExecuteVoidResolveUndefinedRejectVoid>()
    .startExecution();
}
