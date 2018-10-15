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

TEST(EverOperation, CatcherAndThenAndEverWithLambdasWithResolveReject)
{
    Scheduler scheduler;
    Promise<int, float, int> promiseHolder;

    {
        promiseHolder =
        make_promise([&scheduler](int exe, Resolver<char> resolve, Rejector<int> reject) {
            ASSERT_TRUE(10 == exe);
            scheduler.addNextTask(task(resolve, reject, 'w', 12));
        })
        .then([&scheduler](char exe, Resolver<ArgForResolve> resolve, Rejector<int> reject) {
            ASSERT_TRUE('w' == exe);
            ArgForResolve argForResolve{12, 'd', {4.3, "some text"}};
            scheduler.addNextTask(task(resolve, reject, argForResolve, 92));
        })
        .ever([&scheduler](Finisher finish, Reporter<ArgForResolve, int> report) {
            ASSERT_TRUE(report.isRejected());
            ASSERT_FALSE(report.isResolved());
            scheduler.addNextTask(task(finish));
        })
        .then([](ArgForResolve exe, Resolver<int> resolve, Rejector<int> reject) {
            ASSERT_TRUE(false);
        })
        .ever([&scheduler](Finisher finish, Reporter<int, int> report) {
            ASSERT_TRUE(report.isRejected());
            ASSERT_FALSE(report.isResolved());
            scheduler.addNextTask(task(finish));
        })
        .catcher([&scheduler](int e, Resolver<int> resolve, Rethrower<char> rethrew) {
            ASSERT_TRUE(92 == e);
            scheduler.addNextTask(task(resolve, rethrew, 65, 'r'));
        })
        .ever([&scheduler](Finisher finish, Reporter<int, char> report) {
            ASSERT_FALSE(report.isRejected());
            ASSERT_TRUE(report.isResolved());
            scheduler.addNextTask(task(finish));
        })
        .ever([&scheduler](Finisher finish, Reporter<int, char> report) {
            ASSERT_FALSE(report.isRejected());
            ASSERT_TRUE(report.isResolved());
            scheduler.addNextTask(task(finish));
        })
        .then([&scheduler](int exe, Resolver<int> resolve, Rejector<char> reject) {
            ASSERT_TRUE(exe == 65);
            scheduler.addNextTask(task(resolve, reject, 45, 't'));
        })
        .catcher([&scheduler](char e, Resolver<int> resolve, Rethrower<float> rethrew) {
            ASSERT_TRUE(false);
        })
        .then([&scheduler](int exe, Resolver<char> resolve, Rejector<float> reject) {
            ASSERT_TRUE(exe == 45);
            scheduler.addNextTask(task(resolve, reject, 'c', 10.0));
        })
        .catcher([&scheduler](float e, Resolver<char> resolve, Rethrower<float> rethrew) {
            ASSERT_TRUE(10.0 == e);
            scheduler.addNextTask(task(resolve, rethrew, 65, 'r'));
        })
        .ever([&scheduler](Finisher finish, Reporter<char, float> report) {
            ASSERT_TRUE(report.isRejected());
            ASSERT_FALSE(report.isResolved());
            scheduler.addNextTask(task(finish));
        })
        .then([](char exe, Resolver<int> resolve, Rejector<float> reject) {
            ASSERT_TRUE(false);
        })
        .ever([&scheduler](Finisher finish, Reporter<int, float> report) {
            ASSERT_TRUE(report.isRejected());
            ASSERT_FALSE(report.isResolved());
            scheduler.addNextTask(task(finish));
        })
        .startExecution(10);

        ASSERT_FALSE(promiseHolder.isFinished());
        ASSERT_TRUE(promiseHolder.isInProgress());
    }
    scheduler.executeNextTask(Do::Resolve); //make
    ASSERT_FALSE(promiseHolder.isFinished());
    ASSERT_TRUE(promiseHolder.isInProgress());

    scheduler.executeNextTask(Do::Reject); //then
    ASSERT_FALSE(promiseHolder.isFinished());
    ASSERT_TRUE(promiseHolder.isInProgress());

    scheduler.executeNextTask(Do::Resolve); //ever
    ASSERT_FALSE(promiseHolder.isFinished());
    ASSERT_TRUE(promiseHolder.isInProgress());

    scheduler.executeNextTask(Do::Resolve); //ever
    ASSERT_FALSE(promiseHolder.isFinished());
    ASSERT_TRUE(promiseHolder.isInProgress());

    scheduler.executeNextTask(Do::Resolve); //catcher
    ASSERT_FALSE(promiseHolder.isFinished());
    ASSERT_TRUE(promiseHolder.isInProgress());

    scheduler.executeNextTask(Do::Resolve); //ever
    ASSERT_FALSE(promiseHolder.isFinished());
    ASSERT_TRUE(promiseHolder.isInProgress());

    scheduler.executeNextTask(Do::Resolve); //ever
    ASSERT_FALSE(promiseHolder.isFinished());
    ASSERT_TRUE(promiseHolder.isInProgress());

    scheduler.executeNextTask(Do::Resolve); //then
    ASSERT_FALSE(promiseHolder.isFinished());
    ASSERT_TRUE(promiseHolder.isInProgress());

    scheduler.executeNextTask(Do::Reject); //then
    ASSERT_FALSE(promiseHolder.isFinished());
    ASSERT_TRUE(promiseHolder.isInProgress());

    scheduler.executeNextTask(Do::Reject); //catcher
    ASSERT_FALSE(promiseHolder.isFinished());
    ASSERT_TRUE(promiseHolder.isInProgress());

    scheduler.executeNextTask(Do::Resolve); //ever
    ASSERT_FALSE(promiseHolder.isFinished());
    ASSERT_TRUE(promiseHolder.isInProgress());

    scheduler.executeNextTask(Do::Resolve); //ever
    ASSERT_TRUE(promiseHolder.isFinished());
    ASSERT_FALSE(promiseHolder.isResolved());
    ASSERT_TRUE(promiseHolder.isRejected());
    ASSERT_FALSE(promiseHolder.isInProgress());
}
