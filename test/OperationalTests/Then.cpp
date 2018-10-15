#include <string>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Promise.hpp"
#include "Scheduler/Scheduler.hpp"

using namespace prm;
using namespace sch;

struct SubArgForResolve
{
    double d;
    const std::string cc;
    bool operator==(SubArgForResolve toComp)
    {
        return
            toComp.d == d &&
            toComp.cc == cc;
    }
};

struct ArgForResolve
{
    int i;
    char c;
    SubArgForResolve subArgForResolve;
    bool operator==(ArgForResolve toComp)
    {
        return
            toComp.i == i &&
            toComp.c == c &&
            toComp.subArgForResolve == subArgForResolve;
    }
};

TEST(ThenOperation, ThenWithLambdasWithResolveReject)
{
    Scheduler scheduler;
    Promise<int, float, int> promiseHolder;

    {
        promiseHolder =
        make_promise([&scheduler](int exe, Resolver<char> resolve, Rejector<float> reject) {
            ASSERT_TRUE(10 == exe);
            scheduler.addNextTask(task(resolve, reject, 'w', 12.8));
        })
        .then([&scheduler](char exe, Resolver<ArgForResolve> resolve, Rejector<float> reject) {
            ASSERT_TRUE('w' == exe);
            ArgForResolve argForResolve{12, 'd', {4.3, "some text"}};
            scheduler.addNextTask(task(resolve, reject, argForResolve, 92.1));
        })
        .then([&scheduler](ArgForResolve exe, Resolver<int> resolve, Rejector<float> reject) {
            ASSERT_TRUE(ArgForResolve({12, 'd', {4.3, "some text"}}) == exe);
            scheduler.addNextTask(task(resolve, reject, 23, 2.1));
        })
        .startExecution(10);

        ASSERT_FALSE(promiseHolder.isFinished());
        ASSERT_TRUE(promiseHolder.isInProgress());
    }
    scheduler.executeNextTask(Do::Resolve);
    ASSERT_FALSE(promiseHolder.isFinished());
    ASSERT_TRUE(promiseHolder.isInProgress());

    scheduler.executeNextTask(Do::Resolve);
    ASSERT_FALSE(promiseHolder.isFinished());
    ASSERT_TRUE(promiseHolder.isInProgress());

    scheduler.executeNextTask(Do::Resolve);
    ASSERT_TRUE(promiseHolder.isFinished());
    ASSERT_TRUE(promiseHolder.isResolved());
    ASSERT_FALSE(promiseHolder.isRejected());
    ASSERT_FALSE(promiseHolder.isInProgress());
}
