#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Promise.hpp"

#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Move/MoveExecuteTResolveUndefinedRejectVoid.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Move/MoveExecuteVoidResolveTRejectUndefined.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Move/MoveExecuteVoidResolveTRejectT.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Move/MoveExecuteTResolveTRejectUndefined.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Move/MoveExecuteTResolveUndefinedRejectT.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Move/MoveExecuteTResolveVoidRejectVoid.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Move/MoveExecuteTResolveVoidRejectUndefined.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Move/MoveExecuteVoidResolveVoidRejectT.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Move/MoveExecuteVoidResolveUndefinedRejectT.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Move/MoveExecuteVoidResolveUndefinedRejectVoid.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Move/MoveExecuteVoidResolveTRejectVoid.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Move/MoveExecuteTResolveTRejectT.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Move/MoveExecuteTResolveTRejectVoid.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Move/MoveExecuteVoidResolveVoidRejectVoid.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Move/MoveExecuteVoidResolveVoidRejectUndefined.hpp"
#include "CompilationTests/ConstructorTests/AuxiliaryClasses/Then/Move/MoveExecuteTResolveVoidRejectT.hpp"


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

class MakePromiseMoveRValue: public ::testing::TestWithParam<bool>
{ };

INSTANTIATE_TEST_CASE_P(
  TestWithParameters, MakePromiseMoveRValue, testing::Values(
    false,
    true
  ));


// ExeT, ResolveT, RejectT
TEST_P(MakePromiseMoveRValue, ExeResolveReject)
{
    make_promise(MoveExecuteTResolveTRejectT(GetParam()))
    .startExecution(10);
}

// ExeT, ResolveT, RejectVoid
TEST_P(MakePromiseMoveRValue, ExeResolveRejectVoid)
{
    make_promise(MoveExecuteTResolveTRejectVoid(GetParam()))
    .startExecution(10);
}

// ExeT, ResolveT, RejectUndefined
TEST(MakePromiseMoveRValue, ExeResolve)
{
    make_promise(MoveExecuteTResolveTRejectUndefined())
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectT
TEST_P(MakePromiseMoveRValue, ExeResolveVoidReject)
{
    make_promise(MoveExecuteTResolveVoidRejectT(GetParam()))
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectVoid
TEST_P(MakePromiseMoveRValue, ExeResolveVoidRejectVoid)
{
    make_promise(MoveExecuteTResolveVoidRejectVoid(GetParam()))
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectUndefined
TEST(MakePromiseMoveRValue, ExeResolveVoid)
{
    make_promise(MoveExecuteTResolveVoidRejectUndefined())
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectT
TEST(MakePromiseMoveRValue, ExeReject)
{
    make_promise(MoveExecuteTResolveUndefinedRejectT())
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectVoid
TEST(MakePromiseMoveRValue, ExeRejectVoid)
{
    make_promise(MoveExecuteTResolveUndefinedRejectVoid())
    .startExecution(10);
}

// ExeVoid, ResolveT, RejectT
TEST_P(MakePromiseMoveRValue, ResolveReject)
{
    make_promise(MoveExecuteVoidResolveVoidRejectT(GetParam()))
    .startExecution();
}

// ExeVoid, ResolveT, RejectVoid
TEST_P(MakePromiseMoveRValue, ResolveRejectVoid)
{
    make_promise(MoveExecuteVoidResolveTRejectT(GetParam()))
    .startExecution();
}

// ExeVoid, ResolveT, RejectUndefined
TEST(MakePromiseMoveRValue, Resolve)
{
    make_promise(MoveExecuteVoidResolveTRejectUndefined())
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectT
TEST_P(MakePromiseMoveRValue, ResolvVoideReject)
{
    make_promise(MoveExecuteVoidResolveTRejectVoid(GetParam()))
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectVoid
TEST_P(MakePromiseMoveRValue, ResolvVoideRejectVoid)
{
    make_promise(MoveExecuteVoidResolveVoidRejectVoid(GetParam()))
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectUndefined
TEST(MakePromiseMoveRValue, ResolvVoide)
{
    make_promise(MoveExecuteVoidResolveVoidRejectUndefined())
    .startExecution();
}

// ExeVoid, ResolveUndefined, RejectT
TEST(MakePromiseMoveRValue, Reject)
{
    make_promise(MoveExecuteVoidResolveUndefinedRejectT())
    .startExecution();
}

// ExeVoid, ResolveUndefined, RejectVoid
TEST(MakePromiseMoveRValue, RejectVoid)
{
    make_promise(MoveExecuteVoidResolveUndefinedRejectVoid())
    .startExecution();
}

//-----------------LValue-----------------
class MakePromiseMoveLValue: public ::testing::TestWithParam<bool>
{ };

INSTANTIATE_TEST_CASE_P(
  TestWithParameters, MakePromiseMoveLValue, testing::Values(
    false,
    true
  ));


// ExeT, ResolveT, RejectT
TEST_P(MakePromiseMoveLValue, ExeResolveReject)
{
    auto lvalue = MoveExecuteTResolveTRejectT(GetParam());

    make_promise(lvalue)
    .startExecution(10);
}

// ExeT, ResolveT, RejectVoid
TEST_P(MakePromiseMoveLValue, ExeResolveRejectVoid)
{
    auto lvalue = MoveExecuteTResolveTRejectVoid(GetParam());

    make_promise(lvalue)
    .startExecution(10);
}

// ExeT, ResolveT, RejectUndefined
TEST(MakePromiseMoveLValue, ExeResolve)
{
    auto lvalue = MoveExecuteTResolveTRejectUndefined();

    make_promise(lvalue)
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectT
TEST_P(MakePromiseMoveLValue, ExeResolveVoidReject)
{
    auto lvalue = MoveExecuteTResolveVoidRejectT(GetParam());

    make_promise(lvalue)
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectVoid
TEST_P(MakePromiseMoveLValue, ExeResolveVoidRejectVoid)
{
    auto lvalue = MoveExecuteTResolveVoidRejectVoid(GetParam());

    make_promise(lvalue)
    .startExecution(10);
}

// ExeT, ResolveVoid, RejectUndefined
TEST(MakePromiseMoveLValue, ExeResolveVoid)
{
    auto lvalue = MoveExecuteTResolveVoidRejectUndefined();

    make_promise(lvalue)
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectT
TEST(MakePromiseMoveLValue, ExeReject)
{
    auto lvalue = MoveExecuteTResolveUndefinedRejectT();

    make_promise(lvalue)
    .startExecution(10);
}

// ExeT, ResolveUndefined, RejectVoid
TEST(MakePromiseMoveLValue, ExeRejectVoid)
{
    auto lvalue = MoveExecuteTResolveUndefinedRejectVoid();

    make_promise(lvalue)
    .startExecution(10);
}

// ExeVoid, ResolveT, RejectT
TEST_P(MakePromiseMoveLValue, ResolveReject)
{
    auto lvalue = MoveExecuteVoidResolveVoidRejectT(GetParam());

    make_promise(lvalue)
    .startExecution();
}

// ExeVoid, ResolveT, RejectVoid
TEST_P(MakePromiseMoveLValue, ResolveRejectVoid)
{
    auto lvalue = MoveExecuteVoidResolveTRejectT(GetParam());

    make_promise(lvalue)
    .startExecution();
}

// ExeVoid, ResolveT, RejectUndefined
TEST(MakePromiseMoveLValue, Resolve)
{
    auto lvalue = MoveExecuteVoidResolveTRejectUndefined();

    make_promise(lvalue)
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectT
TEST_P(MakePromiseMoveLValue, ResolvVoideReject)
{
    auto lvalue = MoveExecuteVoidResolveTRejectVoid(GetParam());

    make_promise(lvalue)
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectVoid
TEST_P(MakePromiseMoveLValue, ResolvVoideRejectVoid)
{
    auto lvalue = MoveExecuteVoidResolveVoidRejectVoid(GetParam());

    make_promise(lvalue)
    .startExecution();
}

// ExeVoid, ResolveVoid, RejectUndefined
TEST(MakePromiseMoveLValue, ResolvVoide)
{
    auto lvalue = MoveExecuteVoidResolveVoidRejectUndefined();

    make_promise(lvalue)
    .startExecution();
}

// ExeVoid, ResolveUndefined, RejectT
TEST(MakePromiseMoveLValue, Reject)
{
    auto lvalue = MoveExecuteVoidResolveUndefinedRejectT();

    make_promise(lvalue)
    .startExecution();
}

// ExeVoid, ResolveUndefined, RejectVoid
TEST(MakePromiseMoveLValue, RejectVoid)
{
    auto lvalue = MoveExecuteVoidResolveUndefinedRejectVoid();

    make_promise(lvalue)
    .startExecution();
}
