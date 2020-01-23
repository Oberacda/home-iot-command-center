//
// Created by David Oberacker on 2019-08-02.
//

#include <memory>
#include <algorithm>
#include <vector>

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

TEST_F(DeviceTest, ToString) {
    std::unique_ptr<Device> device_hello1_ptr = std::make_unique<Device>("Hallo1", false);
    std::cout << *device_hello1_ptr << std::endl;
}

TEST_F(DeviceTest, EqualitySubclass) {
    std::unique_ptr<SensorDevice> device_hello1_ptr = std::make_unique<SensorDevice>("Hallo1", false);

    ASSERT_FALSE(*(this->device_hallo_false_ptr) == *(device_hello1_ptr));
    ASSERT_FALSE(*(this->device_hallo_true_ptr) == *(device_hello1_ptr));
    ASSERT_TRUE(*(device_hello1_ptr) == *(device_hello1_ptr));
}

TEST_F(DeviceTest, UnequalityName) {
    ASSERT_EQ(this->device_hallo_false_ptr->getDeviceName(), "Hallo");
    ASSERT_EQ(this->device_hallo_true_ptr->getDeviceName(), "Hallo");

    ASSERT_FALSE(*(this->device_hallo_false_ptr) != *(this->device_hallo_true_ptr));
    ASSERT_FALSE(*(this->device_hallo_false_ptr) != *(this->device_hallo_false_ptr));
    ASSERT_FALSE(*(this->device_hallo_true_ptr) != *(this->device_hallo_true_ptr));

    std::unique_ptr<Device> device_hello1_ptr = std::make_unique<Device>("Hallo1", false);

    ASSERT_TRUE(*(this->device_hallo_false_ptr) != *(device_hello1_ptr));
    ASSERT_TRUE(*(this->device_hallo_true_ptr) != *(device_hello1_ptr));
    ASSERT_FALSE(*(device_hello1_ptr) != *(device_hello1_ptr));
}

TEST_F(DeviceTest, UnequalitySubclass) {
    std::unique_ptr<SensorDevice> device_hello1_ptr = std::make_unique<SensorDevice>("Hallo1", false);

    ASSERT_TRUE(*(this->device_hallo_false_ptr) != *(device_hello1_ptr));
    ASSERT_TRUE(*(this->device_hallo_true_ptr) != *(device_hello1_ptr));
    ASSERT_FALSE(*(device_hello1_ptr) != *(device_hello1_ptr));
}

TEST_F(DeviceTest, AddSensor) {
    std::unique_ptr<SensorDevice> device_sensor_ptr = std::make_unique<SensorDevice>("Hallo1", false);
    device_sensor_ptr->addSensor("Test1");
    ASSERT_EQ(device_sensor_ptr->getDeviceSensors().size(), 1);
    ASSERT_TRUE(std::find(device_sensor_ptr->getDeviceSensors().begin(),
    device_sensor_ptr->getDeviceSensors().end(), 
    "Test1") != device_sensor_ptr->getDeviceSensors().end());
    ASSERT_FALSE(std::find(device_sensor_ptr->getDeviceSensors().begin(),
    device_sensor_ptr->getDeviceSensors().end(), 
    "Test2") != device_sensor_ptr->getDeviceSensors().end());

    device_sensor_ptr->addSensor("Test2");
    ASSERT_EQ(device_sensor_ptr->getDeviceSensors().size(), 2);
    ASSERT_TRUE(std::find(device_sensor_ptr->getDeviceSensors().begin(),
    device_sensor_ptr->getDeviceSensors().end(), 
    "Test1") != device_sensor_ptr->getDeviceSensors().end());
    ASSERT_TRUE(std::find(device_sensor_ptr->getDeviceSensors().begin(),
    device_sensor_ptr->getDeviceSensors().end(), 
    "Test2") != device_sensor_ptr->getDeviceSensors().end());
}

TEST_F(DeviceTest, SetAvailability) {
    std::unique_ptr<Device> device_sensor_ptr = std::make_unique<Device>("Hallo1", false);
    ASSERT_FALSE(device_sensor_ptr->isAvailable());
    device_sensor_ptr->setIsAvailable(true);
    ASSERT_TRUE(device_sensor_ptr->isAvailable());
}

TEST_F(DeviceTest, SensorNameInvalid) { 
    std::unique_ptr<SensorDevice> device_sensor_ptr = std::make_unique<SensorDevice>("Hallo1", false);
    ASSERT_NO_THROW(device_sensor_ptr->addSensor("Test1"));
    ASSERT_THROW(device_sensor_ptr->addSensor(""), std::invalid_argument);
}

TEST_F(DeviceTest, AddSensors) {
    std::unique_ptr<SensorDevice> device_sensor_ptr = std::make_unique<SensorDevice>("Hallo1", false);
    ASSERT_EQ(device_sensor_ptr->getDeviceSensors().size(), 0);

    std::unique_ptr<std::vector<std::string>> sensor_names_ptr = std::make_unique<std::vector<std::string>>();
    
    for (int i = 0; i < 1000; i++) {
        sensor_names_ptr->push_back("Test" + std::to_string(i));
    }
    
    ASSERT_EQ(sensor_names_ptr->size(), 1000);
    
    device_sensor_ptr->addSensors(*(sensor_names_ptr));
    ASSERT_EQ(device_sensor_ptr->getDeviceSensors().size(), 1000);

    sensor_names_ptr.reset(nullptr);

    for (int i = 0; i < 1000; i++) {
        ASSERT_EQ(device_sensor_ptr->getDeviceSensors()[i], "Test" + std::to_string(i));
    }
}