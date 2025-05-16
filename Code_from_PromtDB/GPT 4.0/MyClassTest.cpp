#include "gtest/gtest.h"
#include "MyModule/MyClass.h"
#include "HALMock.h"

class MyClassTest : public ::testing::Test {
protected:
    void SetUp() override {
        HALMock::reset();
    }

    void TearDown() override {
    }

    MyClass myClass;
};

TEST_F(MyClassTest, InitializationWithValidData) {
    bool result = myClass.initialize(42);
    EXPECT_TRUE(result);
}

TEST_F(MyClassTest, InitializationWithInvalidData) {
    bool result = myClass.initialize(-1);
    EXPECT_FALSE(result);
}

TEST_F(MyClassTest, ProcessValidInput) {
    myClass.initialize(10);
    int output = myClass.process(20);
    EXPECT_EQ(output, 30);
}

TEST_F(MyClassTest, ProcessEdgeCaseMaxInt) {
    myClass.initialize(INT_MAX);
    int output = myClass.process(0);
    EXPECT_EQ(output, INT_MAX);
}

TEST_F(MyClassTest, ErrorHandlingInvalidProcessInput) {
    myClass.initialize(0);
    int output = myClass.process(-9999);
    EXPECT_EQ(output, -1);
}

TEST_F(MyClassTest, BenchmarkPerformance) {
    myClass.initialize(1);
    const int iterations = 1000;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        myClass.process(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    EXPECT_LT(duration.count(), 100000);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}