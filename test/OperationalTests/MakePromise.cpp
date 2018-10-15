#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Promise.hpp"
#include "Scheduler/Scheduler.hpp"

using namespace prm;
using namespace sch;


TEST(MakePromiseOperation, InOneStepWithStart)
{
    Scheduler scheduler;
    Promise<char, float, int> promiseHolder;

    {
        promiseHolder =
        make_promise([&scheduler](int exe, Resolver<char> resolve, Rejector<float> reject) {
            ASSERT_TRUE(10 == exe);
            scheduler.addNextTask(task(resolve, reject, 'w', 12.8));
        })
        .startExecution(10);

        ASSERT_FALSE(promiseHolder.isFinished());
        ASSERT_TRUE(promiseHolder.isInProgress());
    }

    scheduler.executeNextTask(Do::Resolve);
    ASSERT_TRUE(promiseHolder.isFinished());
    ASSERT_TRUE(promiseHolder.isResolved());
    ASSERT_FALSE(promiseHolder.isRejected());
    ASSERT_FALSE(promiseHolder.isInProgress());
}

TEST(MakePromiseOperation, SeparateStart)
{
    Scheduler scheduler;
    Promise<char, float, int> promiseHolder;

    {
        promiseHolder =
        make_promise([&scheduler](int exe, Resolver<char> resolve, Rejector<float> reject) {
            ASSERT_TRUE(10 == exe);
            scheduler.addNextTask(task(resolve, reject, 'w', 12.8));
        });

        ASSERT_FALSE(promiseHolder.isFinished());
        ASSERT_FALSE(promiseHolder.isInProgress());
    }
    {
        promiseHolder = promiseHolder.startExecution(10);
        ASSERT_FALSE(promiseHolder.isFinished());
        ASSERT_TRUE(promiseHolder.isInProgress());
    }

    scheduler.executeNextTask(Do::Resolve);
    ASSERT_TRUE(promiseHolder.isFinished());
    ASSERT_TRUE(promiseHolder.isResolved());
    ASSERT_FALSE(promiseHolder.isRejected());
    ASSERT_FALSE(promiseHolder.isInProgress());
}


