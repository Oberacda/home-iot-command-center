#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by David Oberacker on 2019-08-02.
//

#include <memory>
#include <algorithm>
#include <vector>
#include <ostream>
#include <sstream>

#include <gtest/gtest.h>
#include <iot/device.hpp>

class DeviceTest : public ::testing::Test {

public:
    std::unique_ptr<D4ve::Iot::Devices::Device> device_hallo_false_ptr;
    std::unique_ptr<D4ve::Iot::Devices::Device> device_hallo_true_ptr;

    DeviceTest() = default;

    ~DeviceTest() override = default;

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
        this->device_hallo_false_ptr = std::make_unique<D4ve::Iot::Devices::Device>("Hallo", D4ve::Iot::Devices::DeviceStatus::UNKNOWN);
        this->device_hallo_true_ptr = std::make_unique<D4ve::Iot::Devices::Device>("Hallo", D4ve::Iot::Devices::DeviceStatus::UNKNOWN);
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
        this->device_hallo_false_ptr.reset(nullptr);
        this->device_hallo_true_ptr.reset(nullptr);
    }
};

TEST_F(DeviceTest, ConstructorValid) {
    EXPECT_EQ(this->device_hallo_false_ptr->getDeviceName(), "Hallo");
    EXPECT_EQ(this->device_hallo_false_ptr->getStatus(), D4ve::Iot::Devices::DeviceStatus::UNKNOWN);

    EXPECT_EQ(this->device_hallo_true_ptr->getDeviceName(), "Hallo");
    EXPECT_EQ(this->device_hallo_true_ptr->getStatus(), D4ve::Iot::Devices::DeviceStatus::UNKNOWN);
}


TEST_F(DeviceTest, EqualityName) {
    EXPECT_EQ(this->device_hallo_false_ptr->getDeviceName(), "Hallo");
    EXPECT_EQ(this->device_hallo_true_ptr->getDeviceName(), "Hallo");

    EXPECT_TRUE(*(this->device_hallo_false_ptr) == *(this->device_hallo_true_ptr));
    EXPECT_TRUE(*(this->device_hallo_false_ptr) == *(this->device_hallo_false_ptr));
    EXPECT_TRUE(*(this->device_hallo_true_ptr) == *(this->device_hallo_true_ptr));

    std::unique_ptr<D4ve::Iot::Devices::Device> device_hello1_ptr = std::make_unique<D4ve::Iot::Devices::Device>(
            "Hallo1", D4ve::Iot::Devices::DeviceStatus::UNKNOWN);

    EXPECT_FALSE(*(this->device_hallo_false_ptr) == *(device_hello1_ptr));
    EXPECT_FALSE(*(this->device_hallo_true_ptr) == *(device_hello1_ptr));
    EXPECT_TRUE(*(device_hello1_ptr) == *(device_hello1_ptr));
}

TEST_F(DeviceTest, ToString) {
    std::stringstream stringstream;
    std::unique_ptr<D4ve::Iot::Devices::Device> device_hello1_ptr = std::make_unique<D4ve::Iot::Devices::Device>(
            "Hallo1", D4ve::Iot::Devices::DeviceStatus::UNKNOWN);
    stringstream << *device_hello1_ptr;

    EXPECT_EQ(stringstream.str(), "[ device_name: Hallo1 status: UNKNOWN ]");
}


TEST_F(DeviceTest, UnequalityName) {
    EXPECT_EQ(this->device_hallo_false_ptr->getDeviceName(), "Hallo");
    EXPECT_EQ(this->device_hallo_true_ptr->getDeviceName(), "Hallo");

    EXPECT_FALSE(*(this->device_hallo_false_ptr) != *(this->device_hallo_true_ptr));
    EXPECT_FALSE(*(this->device_hallo_false_ptr) != *(this->device_hallo_false_ptr));
    EXPECT_FALSE(*(this->device_hallo_true_ptr) != *(this->device_hallo_true_ptr));

    std::unique_ptr<D4ve::Iot::Devices::Device> device_hello1_ptr = std::make_unique<D4ve::Iot::Devices::Device>(
            "Hallo1", D4ve::Iot::Devices::DeviceStatus::UNKNOWN);

    EXPECT_TRUE(*(this->device_hallo_false_ptr) != *(device_hello1_ptr));
    EXPECT_TRUE(*(this->device_hallo_true_ptr) != *(device_hello1_ptr));
    EXPECT_FALSE(*(device_hello1_ptr) != *(device_hello1_ptr));
}


TEST_F(DeviceTest, SetStatus) {
    std::unique_ptr<D4ve::Iot::Devices::Device> device_sensor_ptr = std::make_unique<D4ve::Iot::Devices::Device>(
            "Hallo1", D4ve::Iot::Devices::DeviceStatus::UNKNOWN);
    EXPECT_EQ(device_sensor_ptr->getStatus(), D4ve::Iot::Devices::DeviceStatus::UNKNOWN);
    device_sensor_ptr->setStatus(D4ve::Iot::Devices::DeviceStatus::DISCONNECTED);
    EXPECT_EQ(device_sensor_ptr->getStatus(), D4ve::Iot::Devices::DeviceStatus::DISCONNECTED);
}


class SensorDeviceTest : public ::testing::Test {

public:
    std::unique_ptr<D4ve::Iot::Devices::SensorDevice> test_sensor_device_1_ptr;
    std::unique_ptr<D4ve::Iot::Devices::SensorDevice> test_sensor_device_2_ptr;

    SensorDeviceTest() = default;

    ~SensorDeviceTest() override = default;

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
        this->test_sensor_device_1_ptr = std::make_unique<D4ve::Iot::Devices::SensorDevice>("Hallo1", D4ve::Iot::Devices::DeviceStatus::UNKNOWN);
        this->test_sensor_device_2_ptr = std::make_unique<D4ve::Iot::Devices::SensorDevice>("Hallo2", D4ve::Iot::Devices::DeviceStatus::UNKNOWN);
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
        this->test_sensor_device_1_ptr.reset(nullptr);
        this->test_sensor_device_2_ptr.reset(nullptr);
    }
};

TEST_F(SensorDeviceTest, ConstructorValid) {
    EXPECT_EQ(this->test_sensor_device_1_ptr->getDeviceName(), "Hallo1");
    EXPECT_EQ(this->test_sensor_device_1_ptr->getStatus(), D4ve::Iot::Devices::DeviceStatus::UNKNOWN);

    EXPECT_EQ(this->test_sensor_device_2_ptr->getDeviceName(), "Hallo2");
    EXPECT_EQ(this->test_sensor_device_2_ptr->getStatus(), D4ve::Iot::Devices::DeviceStatus::UNKNOWN);
}

TEST_F(SensorDeviceTest, NameInvalid) {
    EXPECT_NO_THROW(this->test_sensor_device_1_ptr->addSensor("Test1"));
    EXPECT_THROW(this->test_sensor_device_1_ptr->addSensor(""), std::invalid_argument);
}

TEST_F(SensorDeviceTest, Unequality) {
    std::unique_ptr<D4ve::Iot::Devices::SensorDevice> device_hello1_ptr = std::make_unique<D4ve::Iot::Devices::SensorDevice>(
            "Hallo3", D4ve::Iot::Devices::DeviceStatus::UNKNOWN);

    EXPECT_TRUE(*(this->test_sensor_device_1_ptr) != *(device_hello1_ptr));
    EXPECT_TRUE(*(this->test_sensor_device_2_ptr) != *(device_hello1_ptr));
    EXPECT_FALSE(*(device_hello1_ptr) != *(device_hello1_ptr));
}

TEST_F(DeviceTest, AddSensor) {
    std::unique_ptr<D4ve::Iot::Devices::SensorDevice> device_sensor_ptr = std::make_unique<D4ve::Iot::Devices::SensorDevice>(
            "Hallo1", D4ve::Iot::Devices::DeviceStatus::UNKNOWN);
    device_sensor_ptr->addSensor("Test1");
    EXPECT_EQ(device_sensor_ptr->getDeviceSensors().size(), 1);
    EXPECT_TRUE(std::find(device_sensor_ptr->getDeviceSensors().begin(),
                          device_sensor_ptr->getDeviceSensors().end(),
                          "Test1") != device_sensor_ptr->getDeviceSensors().end());
    EXPECT_FALSE(std::find(device_sensor_ptr->getDeviceSensors().begin(),
                           device_sensor_ptr->getDeviceSensors().end(),
                           "Test2") != device_sensor_ptr->getDeviceSensors().end());

    device_sensor_ptr->addSensor("Test2");
    EXPECT_EQ(device_sensor_ptr->getDeviceSensors().size(), 2);
    EXPECT_TRUE(std::find(device_sensor_ptr->getDeviceSensors().begin(),
                          device_sensor_ptr->getDeviceSensors().end(),
                          "Test1") != device_sensor_ptr->getDeviceSensors().end());
    EXPECT_TRUE(std::find(device_sensor_ptr->getDeviceSensors().begin(),
                          device_sensor_ptr->getDeviceSensors().end(),
                          "Test2") != device_sensor_ptr->getDeviceSensors().end());
}


TEST_F(SensorDeviceTest, AddSensors) {
    EXPECT_EQ(this->test_sensor_device_1_ptr->getDeviceSensors().size(), 0);

    std::unique_ptr<std::vector<std::string>> sensor_names_ptr = std::make_unique<std::vector<std::string>>();

    for (int i = 0; i < 1000; i++) {
        sensor_names_ptr->push_back("Test" + std::to_string(i));
    }

    EXPECT_EQ(sensor_names_ptr->size(), 1000);

    this->test_sensor_device_1_ptr->addSensors(*(sensor_names_ptr));
    EXPECT_EQ(this->test_sensor_device_1_ptr->getDeviceSensors().size(), 1000);

    sensor_names_ptr.reset(nullptr);

    for (int i = 0; i < 1000; i++) {
        EXPECT_EQ(this->test_sensor_device_1_ptr->getDeviceSensors()[i], "Test" + std::to_string(i));
    }
}


TEST_F(SensorDeviceTest, ToString) {
    std::stringstream stringstream;

    stringstream << *(this->test_sensor_device_1_ptr);

    EXPECT_EQ(stringstream.str(), "[ [ device_name: Hallo1 status: UNKNOWN ] sensors: 0 ]");
}

TEST_F(SensorDeviceTest, Equality) {
    std::unique_ptr<D4ve::Iot::Devices::SensorDevice> device_hello1_ptr = std::make_unique<D4ve::Iot::Devices::SensorDevice>(
            "Hallo3", D4ve::Iot::Devices::DeviceStatus::UNKNOWN);

    EXPECT_FALSE(*(this->test_sensor_device_1_ptr) == *(device_hello1_ptr));
    EXPECT_FALSE(*(this->test_sensor_device_2_ptr) == *(device_hello1_ptr));
    EXPECT_TRUE(*(device_hello1_ptr) == *(device_hello1_ptr));
}
#pragma clang diagnostic pop