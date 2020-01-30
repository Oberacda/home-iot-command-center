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
#include <iostream>

const std::string &D4ve::Iot::Devices::Device::getDeviceName() const {
    return device_name;
}

bool D4ve::Iot::Devices::Device::isAvailable() const {
    return is_available;
}

D4ve::Iot::Devices::Device::Device(std::string deviceName, bool isAvailable) : device_name(std::move(deviceName)),
                                   is_available(isAvailable) {}

D4ve::Iot::Devices::Device::~Device() {

}

bool D4ve::Iot::Devices::Device::operator==(const D4ve::Iot::Devices::Device &rhs) const {
    return device_name == rhs.device_name;
}

bool D4ve::Iot::Devices::Device::operator!=(const D4ve::Iot::Devices::Device &rhs) const {
    return !(rhs == *this);
}



void D4ve::Iot::Devices::Device::setIsAvailable(bool isAvailable) {
    is_available = isAvailable;
}

std::ostream HOME_IOT_CTL_API &
D4ve::Iot::Devices::operator<<(std::ostream &os, const D4ve::Iot::Devices::Device &device) {
        os << "[ device_name: " << device.getDeviceName() << " is_available: " << device.isAvailable() << " ]";
        return os;
}

const std::vector<std::string> &D4ve::Iot::Devices::SensorDevice::getDeviceSensors() const {
    return device_sensors;
}

D4ve::Iot::Devices::SensorDevice::SensorDevice(const std::string &deviceName, bool isAvailable) : Device(deviceName, isAvailable) {}

void D4ve::Iot::Devices::SensorDevice::addSensor(const std::string& sensor_name) {
    if (sensor_name.length() < 1) {
        throw std::invalid_argument("The given sensor_name is too short!");
    }

    this->device_sensors.push_back(sensor_name);
}

void D4ve::Iot::Devices::SensorDevice::addSensors(const std::vector<std::string>& sensors) {
    for (auto sensor_name : sensors) {
        this->addSensor(sensor_name);
    }
}

std::ostream HOME_IOT_CTL_API &
D4ve::Iot::Devices::operator<<(std::ostream &os, const D4ve::Iot::Devices::SensorDevice &device) {
    os << "[ " << static_cast<const D4ve::Iot::Devices::Device &>(device) << " sensors: " << device.getDeviceSensors().size() << " ]";
    return os;
}
