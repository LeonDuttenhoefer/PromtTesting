#include "gtest/gtest.h"
#include "MyRodosModule/MyRodosClass.h"

uint64_t mockedTime = 0;
extern "C" uint64_t NOW() {
    return mockedTime;
}

extern "C" void xprintf(const char* fmt, ...) {
}

class SchedulerStub {
public:
    void advanceTime(uint64_t delta) {
        mockedTime += delta;
    }

    void resetTime() {
        mockedTime = 0;
    }
};

class MyRodosClassTest : public ::testing::Test {
protected:
    SchedulerStub scheduler;
    MyRodosClass myObj;

    void SetUp() override {
        scheduler.resetTime();
    }

    void TearDown() override {
    }
};

TEST_F(MyRodosClassTest, InitializeSetsDefaults) {
    myObj.initialize();
    EXPECT_EQ(myObj.getState(), 0);
}

TEST_F(MyRodosClassTest, PerformActionChangesState) {
    myObj.initialize();
    myObj.performAction(5);
    EXPECT_EQ(myObj.getState(), 5);
}

TEST_F(MyRodosClassTest, PerformNegativeInputIsHandled) {
    myObj.initialize();
    myObj.performAction(-10);
    EXPECT_EQ(myObj.getState(), 0);
}

TEST_F(MyRodosClassTest, TimeBasedTriggerWorks) {
    myObj.initialize();
    scheduler.advanceTime(1000);
    myObj.checkTimedEvent();
    EXPECT_TRUE(myObj.eventTriggered());
}

TEST_F(MyRodosClassTest, EdgeCaseMaxValueInput) {
    myObj.initialize();
    myObj.performAction(0x7FFFFFFF);
    EXPECT_EQ(myObj.getState(), 0x7FFFFFFF);
}

TEST_F(MyRodosClassTest, EdgeCaseOverflowHandled) {
    myObj.initialize();
    myObj.performAction(0xFFFFFFFF);
    EXPECT_LT(myObj.getState(), 0xFFFFFFFF);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}