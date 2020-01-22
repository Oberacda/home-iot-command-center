//
// Created by David Oberacker on 2019-08-02.
//

#include <gtest/gtest.h>
#include <iot/home.hpp>

class HomeTest : public ::testing::Test {
    public:
    HomeTest() {
    }

    ~HomeTest() override {
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
};

TEST_F(HomeTest, Verify) {
    SUCCEED();
}

TEST_F(HomeTest, Invalid) {
    SUCCEED();
}


