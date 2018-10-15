#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Promise.hpp"

#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Copy/CopyExecuteTResolveUndefinedRejectVoid.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Copy/CopyExecuteVoidResolveTRejectUndefined.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Copy/CopyExecuteVoidResolveTRejectT.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Copy/CopyExecuteTResolveTRejectUndefined.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Copy/CopyExecuteTResolveUndefinedRejectT.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Copy/CopyExecuteTResolveVoidRejectVoid.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Copy/CopyExecuteTResolveVoidRejectUndefined.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Copy/CopyExecuteVoidResolveVoidRejectT.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Copy/CopyExecuteVoidResolveUndefinedRejectT.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Copy/CopyExecuteVoidResolveUndefinedRejectVoid.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Copy/CopyExecuteVoidResolveTRejectVoid.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Copy/CopyExecuteTResolveTRejectT.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Copy/CopyExecuteTResolveTRejectVoid.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Copy/CopyExecuteVoidResolveVoidRejectVoid.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Copy/CopyExecuteVoidResolveVoidRejectUndefined.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Copy/CopyExecuteTResolveVoidRejectT.hpp"


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

class MakePromiseCopyRValue: public ::testing::TestWithParam<bool>
{ };

INSTANTIATE_TEST_CASE_P(
  TestWithParameters, MakePromiseCopyRValue, testing::Values(
    false,
    true
  ));


// ExeT, ResolveT, RejectT
TEST_P(MakePromiseCopyRValue, ExeResolveReject)
{
    make_promise(CopyExecuteTResolveTRejectT(GetParam()))
    .startExecution(10);
}

// ExeT, ResolveT, RejectVoid
TEST_P(MakePromiseCopyRValue, ExeResolveRejectVoid)
{
    make_promise(CopyExecuteTResolveTRejectVoid(GetParam()))
    .startExecution(10);
}

// ExeT, ResolveT, RejectUndefined
TEST(MakePromiseCopyRValue, ExeResolve)
{
    make_promise(CopyExecuteTResolveTRejectUndefined())
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectT
TEST_P(MakePromiseCopyRValue, ExeResolveVoidReject)
{
    make_promise(CopyExecuteTResolveVoidRejectT(GetParam()))
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectVoid
TEST_P(MakePromiseCopyRValue, ExeResolveVoidRejectVoid)
{
    make_promise(CopyExecuteTResolveVoidRejectVoid(GetParam()))
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectUndefined
TEST(MakePromiseCopyRValue, ExeResolveVoid)
{
    make_promise(CopyExecuteTResolveVoidRejectUndefined())
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectT
TEST(MakePromiseCopyRValue, ExeReject)
{
    make_promise(CopyExecuteTResolveUndefinedRejectT())
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectVoid
TEST(MakePromiseCopyRValue, ExeRejectVoid)
{
    make_promise(CopyExecuteTResolveUndefinedRejectVoid())
    .startExecution(10);
}

// ExeVoid, ResolveT, RejectT
TEST_P(MakePromiseCopyRValue, ResolveReject)
{
    make_promise(CopyExecuteVoidResolveVoidRejectT(GetParam()))
    .startExecution();
}

// ExeVoid, ResolveT, RejectVoid
TEST_P(MakePromiseCopyRValue, ResolveRejectVoid)
{
    make_promise(CopyExecuteVoidResolveTRejectT(GetParam()))
    .startExecution();
}

// ExeVoid, ResolveT, RejectUndefined
TEST(MakePromiseCopyRValue, Resolve)
{
    make_promise(CopyExecuteVoidResolveTRejectUndefined())
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectT
TEST_P(MakePromiseCopyRValue, ResolvVoideReject)
{
    make_promise(CopyExecuteVoidResolveTRejectVoid(GetParam()))
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectVoid
TEST_P(MakePromiseCopyRValue, ResolvVoideRejectVoid)
{
    make_promise(CopyExecuteVoidResolveVoidRejectVoid(GetParam()))
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectUndefined
TEST(MakePromiseCopyRValue, ResolvVoide)
{
    make_promise(CopyExecuteVoidResolveVoidRejectUndefined())
    .startExecution();
}

// ExeVoid, ResolveUndefined, RejectT
TEST(MakePromiseCopyRValue, Reject)
{
    make_promise(CopyExecuteVoidResolveUndefinedRejectT())
    .startExecution();
}

// ExeVoid, ResolveUndefined, RejectVoid
TEST(MakePromiseCopyRValue, RejectVoid)
{
    make_promise(CopyExecuteVoidResolveUndefinedRejectVoid())
    .startExecution();
}

//-----------------LValue-----------------
class MakePromiseCopyLValue: public ::testing::TestWithParam<bool>
{ };

INSTANTIATE_TEST_CASE_P(
  TestWithParameters, MakePromiseCopyLValue, testing::Values(
    false,
    true
  ));


// ExeT, ResolveT, RejectT
TEST_P(MakePromiseCopyLValue, ExeResolveReject)
{
    auto lvalue = CopyExecuteTResolveTRejectT(GetParam());

    make_promise(lvalue)
    .startExecution(10);
}

// ExeT, ResolveT, RejectVoid
TEST_P(MakePromiseCopyLValue, ExeResolveRejectVoid)
{
    auto lvalue = CopyExecuteTResolveTRejectVoid(GetParam());

    make_promise(lvalue)
    .startExecution(10);
}

// ExeT, ResolveT, RejectUndefined
TEST(MakePromiseCopyLValue, ExeResolve)
{
    auto lvalue = CopyExecuteTResolveTRejectUndefined();

    make_promise(lvalue)
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectT
TEST_P(MakePromiseCopyLValue, ExeResolveVoidReject)
{
    auto lvalue = CopyExecuteTResolveVoidRejectT(GetParam());

    make_promise(lvalue)
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectVoid
TEST_P(MakePromiseCopyLValue, ExeResolveVoidRejectVoid)
{
    auto lvalue = CopyExecuteTResolveVoidRejectVoid(GetParam());

    make_promise(lvalue)
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectUndefined
TEST(MakePromiseCopyLValue, ExeResolveVoid)
{
    auto lvalue = CopyExecuteTResolveVoidRejectUndefined();

    make_promise(lvalue)
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectT
TEST(MakePromiseCopyLValue, ExeReject)
{
    auto lvalue = CopyExecuteTResolveUndefinedRejectT();

    make_promise(lvalue)
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectVoid
TEST(MakePromiseCopyLValue, ExeRejectVoid)
{
    auto lvalue = CopyExecuteTResolveUndefinedRejectVoid();

    make_promise(lvalue)
    .startExecution(10);
}

// ExeVoid, ResolveT, RejectT
TEST_P(MakePromiseCopyLValue, ResolveReject)
{
    auto lvalue = CopyExecuteVoidResolveVoidRejectT(GetParam());

    make_promise(lvalue)
    .startExecution();
}

// ExeVoid, ResolveT, RejectVoid
TEST_P(MakePromiseCopyLValue, ResolveRejectVoid)
{
    auto lvalue = CopyExecuteVoidResolveTRejectT(GetParam());

    make_promise(lvalue)
    .startExecution();
}

// ExeVoid, ResolveT, RejectUndefined
TEST(MakePromiseCopyLValue, Resolve)
{
    auto lvalue = CopyExecuteVoidResolveTRejectUndefined();

    make_promise(lvalue)
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectT
TEST_P(MakePromiseCopyLValue, ResolvVoideReject)
{
    auto lvalue = CopyExecuteVoidResolveTRejectVoid(GetParam());

    make_promise(lvalue)
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectVoid
TEST_P(MakePromiseCopyLValue, ResolvVoideRejectVoid)
{
    auto lvalue = CopyExecuteVoidResolveVoidRejectVoid(GetParam());

    make_promise(lvalue)
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectUndefined
TEST(MakePromiseCopyLValue, ResolvVoide)
{
    auto lvalue = CopyExecuteVoidResolveVoidRejectUndefined();

    make_promise(lvalue)
    .startExecution();
}

// ExeVoid, ResolveUndefined, RejectT
TEST(MakePromiseCopyLValue, Reject)
{
    auto lvalue = CopyExecuteVoidResolveUndefinedRejectT();

    make_promise(lvalue)
    .startExecution();
}

// ExeVoid, ResolveUndefined, RejectVoid
TEST(MakePromiseCopyLValue, RejectVoid)
{
    auto lvalue = CopyExecuteVoidResolveUndefinedRejectVoid();

    make_promise(lvalue)
    .startExecution();
}
