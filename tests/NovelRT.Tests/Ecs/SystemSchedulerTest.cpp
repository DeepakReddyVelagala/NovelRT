// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include <atomic>

using namespace NovelRT;
using namespace NovelRT::Ecs;
using namespace NovelRT::Timing;

class SystemSchedulerTest : public testing::Test
{
    public:
    SystemScheduler* scheduler = nullptr;
    bool sysOneBool = true;
    bool sysTwoBool = true;
    bool sysThreeBool = true;
    std::function<void(Timestamp)> sysOne;
    std::function<void(Timestamp)> sysTwo;
    std::function<void(Timestamp)> sysThree;
    
    protected:
    void SetUp() override
    {
        sysOneBool = true;
        sysTwoBool = true;
        sysThreeBool = true;

        if (scheduler == nullptr)
        {
            delete scheduler;
            scheduler = new SystemScheduler();
        

            scheduler->SpinThreads();

            sysOne = [&](Timestamp delta) {sysOneBool = false;};
            sysTwo = [&](Timestamp delta) {sysTwoBool = false;};
            sysThree = [&](Timestamp delta) {sysThreeBool = false;};

            scheduler->RegisterSystemForComponent<int>(sysOne);
            scheduler->RegisterSystemForComponent<bool>(sysTwo);
            scheduler->RegisterSystemForComponent<char>(sysThree);
        }
    }

    void TearDown() override
    {
        if (scheduler != nullptr)
        {
            delete scheduler;
            scheduler = nullptr;
        }
    }
};

TEST_F(SystemSchedulerTest, IndependentSystemsCanRun)
{
    EXPECT_NO_THROW(scheduler->ExecuteIteration(Timestamp(0)));
}

TEST_F(SystemSchedulerTest, IndependentSystemsCanModifyValues)
{
    scheduler->ExecuteIteration(Timestamp(0));
    
    EXPECT_FALSE(sysOneBool);
    EXPECT_FALSE(sysTwoBool);
    EXPECT_FALSE(sysThreeBool);
}