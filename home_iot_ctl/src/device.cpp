/*!
 * @file device.cpp
 * @brief Source file for classes related to devices in the IoT network.
 *
 * @author David Oberacker <david.oberacker(at)gmail.com>
 * @version 1.0.0
 * @date 20.01.20
 */

#include "iot/device.hpp"

#include <utility>

const std::string &Device::getDeviceName() const {
    return device_name;
}

bool Device::isAvailable() const {
    return is_available;
}

Device::Device(std::string deviceName, bool isAvailable) : device_name(std::move(deviceName)),
                                   is_available(isAvailable) {}

Device::~Device() {

}

bool Device::operator==(const Device &rhs) const {
    return device_name == rhs.device_name;
}

bool Device::operator!=(const Device &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Device &device) {
    os << " device_name: " << device.device_name << " is_available: " << device.is_available;
    return os;
}

void Device::setIsAvailable(bool isAvailable) {
    is_available = isAvailable;
}

const std::vector<std::string> &SensorDevice::getDeviceSensors() const {
    return device_sensors;
}

SensorDevice::SensorDevice(const std::string &deviceName, bool isAvailable) : Device(deviceName, isAvailable) {}

void SensorDevice::addSensor(const std::string& sensor_name) {
    if (sensor_name.length() < 1) {
        throw std::invalid_argument("The given sensor_name is too short!");
    }

    this->device_sensors.push_back(sensor_name);
}

void SensorDevice::addSensors(const std::vector<std::string>& sensors) {
    for (auto sensor_name : sensors) {
        this->addSensor(sensor_name);
    }
}
