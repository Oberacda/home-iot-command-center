//
// Created by David Oberacker on 20.01.20.
//

#include "iot/device.hpp"

#include <utility>

uint64_t Device::getDeviceId() const {
    return device_id;
}

const std::string &Device::getDeviceName() const {
    return device_name;
}

const std::vector<std::string> &Device::getDeviceSensors() const {
    return device_sensors;
}

bool Device::isAvailable() const {
    return is_available;
}

Device::Device(uint64_t deviceId, std::string deviceName, std::vector<std::string> deviceSensors,
               bool isAvailable) : device_id(deviceId), device_name(std::move(deviceName)), device_sensors(std::move(deviceSensors)),
                                   is_available(isAvailable) {}

Device::~Device() {

}

bool Device::operator==(const Device &rhs) const {
    return device_id == rhs.device_id;
}

bool Device::operator!=(const Device &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Device &device) {
    os << "device_id: " << device.device_id << " device_name: " << device.device_name << " is_available: " << device.is_available;
    return os;
}
