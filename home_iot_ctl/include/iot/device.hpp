//
// Created by David Oberacker on 20.01.20.
//

#ifndef HOME_IOT_COMMAND_CENTER_DEVICE_HPP
#define HOME_IOT_COMMAND_CENTER_DEVICE_HPP

#pragma once

#include <string>
#include <vector>
#include <ostream>

#include "home_iot_ctl_exports.hpp"

class HOME_IOT_CTL_API DeviceChange {
    
};

class Device {
private:
    uint64_t device_id;
    std::string device_name;
    std::vector<std::string> device_sensors;
    bool is_available;

public:
    virtual ~Device();

    bool operator==(const Device &rhs) const;

    bool operator!=(const Device &rhs) const;

    Device(uint64_t deviceId, std::string deviceName, std::vector<std::string> deviceSensors,
           bool isAvailable);

    uint64_t getDeviceId() const;

    const std::string &getDeviceName() const;

    const std::vector<std::string> &getDeviceSensors() const;

    bool isAvailable() const;

    friend std::ostream &operator<<(std::ostream &os, const Device &device);
};



#endif //HOME_IOT_COMMAND_CENTER_DEVICE_HPP
