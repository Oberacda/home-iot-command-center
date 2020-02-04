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

D4ve::Iot::Devices::Device::Device(std::string deviceName, DeviceStatus status) : device_name(std::move(deviceName)),
                                                                                  status(status) {}

D4ve::Iot::Devices::Device::~Device() = default;

bool D4ve::Iot::Devices::Device::operator==(const D4ve::Iot::Devices::Device &rhs) const {
    return device_name == rhs.device_name;
}

bool D4ve::Iot::Devices::Device::operator!=(const D4ve::Iot::Devices::Device &rhs) const {
    return !(rhs == *this);
}


std::ostream HOME_IOT_CTL_API &
D4ve::Iot::Devices::operator<<(std::ostream &os, const D4ve::Iot::Devices::Device &device) {
    os << "[ device_name: " << device.getDeviceName() << " status: " << device.getStatus() << " ]";
    return os;
}

D4ve::Iot::Devices::DeviceStatus D4ve::Iot::Devices::Device::getStatus() const {
    return status;
}

void D4ve::Iot::Devices::Device::setStatus(D4ve::Iot::Devices::DeviceStatus status) {
    Device::status = status;
}

const std::vector<std::string> &D4ve::Iot::Devices::SensorDevice::getDeviceSensors() const {
    return device_sensors;
}

D4ve::Iot::Devices::SensorDevice::SensorDevice(const std::string &deviceName, DeviceStatus status) : Device(deviceName,
                                                                                                            status) {}

void D4ve::Iot::Devices::SensorDevice::addSensor(const std::string &sensor_name) {
    if (sensor_name.length() < 1) {
        throw std::invalid_argument("The given sensor_name is too short!");
    }

    this->device_sensors.push_back(sensor_name);
}

void D4ve::Iot::Devices::SensorDevice::addSensors(const std::vector<std::string> &sensors) {
    for (const auto &sensor_name : sensors) {
        this->addSensor(sensor_name);
    }
}

std::ostream HOME_IOT_CTL_API &
D4ve::Iot::Devices::operator<<(std::ostream &os, const D4ve::Iot::Devices::SensorDevice &device) {
    os << "[ " << static_cast<const D4ve::Iot::Devices::Device &>(device) << " sensors: "
       << device.getDeviceSensors().size() << " ]";
    return os;
}

std::ostream HOME_IOT_CTL_API &
D4ve::Iot::Devices::operator<<(std::ostream &os, D4ve::Iot::Devices::DeviceStatus status) {
    switch (status) {
        case DeviceStatus::UNKNOWN   :
            os << "UNKNOWN";
            break;
        case DeviceStatus::DISCONNECTED:
            os << "DISCONNECTED";
            break;
        case DeviceStatus::IDLE :
            os << "IDLE";
            break;
        case DeviceStatus::RUNNING  :
            os << "RUNNING";
            break;
        case DeviceStatus::ERROR  :
            os << "ERROR";
            break;
        default    :
            os.setstate(std::ios_base::failbit);
    }
    return os;
}
