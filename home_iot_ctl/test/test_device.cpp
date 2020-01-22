//
// Created by David Oberacker on 2019-08-02.
//

#include <memory>

#include <gtest/gtest.h>
#include <iot/device.hpp>

class DeviceTest : public ::testing::Test {

public:
    std::unique_ptr<Device> device_hallo_false_ptr;
    std::unique_ptr<Device> device_hallo_true_ptr;

    DeviceTest() {
    }

    ~DeviceTest() override {
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
        this->device_hallo_false_ptr = std::make_unique<Device>("Hallo", false);
        this->device_hallo_true_ptr = std::make_unique<Device>("Hallo", true);
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
        this->device_hallo_false_ptr.reset(nullptr);
        this->device_hallo_true_ptr.reset(nullptr);
    }
};

TEST_F(DeviceTest, ConstructorValid) {
    ASSERT_EQ(this->device_hallo_false_ptr->getDeviceName(), "Hallo");
    ASSERT_EQ(this->device_hallo_false_ptr->isAvailable(), false);

    ASSERT_EQ(this->device_hallo_true_ptr->getDeviceName(), "Hallo");
    ASSERT_EQ(this->device_hallo_true_ptr->isAvailable(), true);
}

TEST_F(DeviceTest, EqualityName) {
    ASSERT_EQ(this->device_hallo_false_ptr->getDeviceName(), "Hallo");
    ASSERT_EQ(this->device_hallo_true_ptr->getDeviceName(), "Hallo");

    ASSERT_TRUE(*(this->device_hallo_false_ptr) == *(this->device_hallo_true_ptr));
    ASSERT_TRUE(*(this->device_hallo_false_ptr) == *(this->device_hallo_false_ptr));
    ASSERT_TRUE(*(this->device_hallo_true_ptr) == *(this->device_hallo_true_ptr));

    std::unique_ptr<Device> device_hello1_ptr = std::make_unique<Device>("Hallo1", false);

    ASSERT_FALSE(*(this->device_hallo_false_ptr) == *(device_hello1_ptr));
    ASSERT_FALSE(*(this->device_hallo_true_ptr) == *(device_hello1_ptr));
    ASSERT_TRUE(*(device_hello1_ptr) == *(device_hello1_ptr));
}

TEST_F(DeviceTest, EqualitySubclass) {
    std::unique_ptr<SensorDevice> device_hello1_ptr = std::make_unique<SensorDevice>("Hallo1", false);

    ASSERT_FALSE(*(this->device_hallo_false_ptr) == *(device_hello1_ptr));
    ASSERT_FALSE(*(this->device_hallo_true_ptr) == *(device_hello1_ptr));
    ASSERT_TRUE(*(device_hello1_ptr) == *(device_hello1_ptr));
}

