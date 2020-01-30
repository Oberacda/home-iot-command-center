/*!
 * @file device.hpp
 * @brief Header declaring classes related to devices in the IoT network.
 *
 * @author David Oberacker <david.oberacker(at)gmail.com>
 * @version 1.0.0
 * @date 20.01.20
 */

#ifndef HOME_IOT_CTL_IOT_DEVICE_HPP
#define HOME_IOT_CTL_IOT_DEVICE_HPP

#pragma once

#include <string>
#include <vector>
#include <ostream>
#include <sstream>
#include <iosfwd>
#include <stdexcept>

#include "home_iot_ctl_exports.hpp"


namespace D4ve::Iot::Devices {

    /*!
     * @brief Class modeling a single IoT device in the network.
     *
     * @details A device is a node in the Mqtt network that has certain capabilities.
     *
     * @author David Oberacker <david.oberacker(at)gmail.com>
     * @version 1.0.0
     */
    class HOME_IOT_CTL_API Device {
    private:
        /*!
         * @brief Name of the device in the MQTT context.
         * @details This is a unique identifier in the network. It is valid for all nodes in the network.
         */
        std::string device_name;

        /*!
         * @brief Boolean marking if the sensor as recorded as available.
         * @details If this is set to false, the sensor was present in the network at one time but was not when the last
         * index update was performed.
         */
        bool is_available;

    public:
        virtual ~Device();

        /*!
         * @brief Operator to check id two devices are equal.
         * @param rhs The device to compare to.
         * @return true iff the two devices are representing the same physical device, false otherwise.
         */
        bool operator==(const Device &rhs) const;

        /*!
         * @brief Operator to check id two devices are not equal.
         * @param rhs The device to compare to.
         * @return true iff the two devices are not representing the same physical device, false otherwise.
         */
        bool operator!=(const Device &rhs) const;

        /*!
         * @brief Creates a new device from a id, a name and the availablity.
         *
         * @details This creates a new device registered from the network.
         *
         * @param deviceName The mqtt network global device name.
         * @param isAvailable Indicator if the device was available at the last indexing.
         */
        Device(std::string deviceName, bool isAvailable);

        /*!
         * @brief Getter for the unique MQTT Client name of the device.
         *
         * @details This is a unique identifier in the network. It is valid for all nodes in the network.s
         *
         * @return The unique MQTT client name.
         */
        [[nodiscard]] const std::string &getDeviceName() const;

        /*!
         * @brief Getter for the isAvaliable attribute.
         * @details  If this returns false, the sensor was present in the network at one time but was not when the last
         * index update was performed.
         * @return true iff the sensor was present at the last indexing, false iff he was not present.
         */
        [[nodiscard]] bool isAvailable() const;

        /*!
         * @brief Sets the availability to a new value.
         *
         * @param isAvailable The new value for the availability.
         */
        void setIsAvailable(bool isAvailable);

        /*!
         * @brief Prints a common representation of the device as a stream.
         * @param os The stream to write the representation to.
         * @param device The device to represent.
         * @return A stream with the representation added. Can be used to chain calls.
         */
        friend std::ostream HOME_IOT_CTL_API &operator<<(std::ostream &os, const D4ve::Iot::Devices::Device &device);
    };

/*!
 * @brief Class describing a sensor with sensors available.
 * @details These devices are able to record an publish data. This specialization is used to identify possible sensors
 * that can be used.
 *
 * @author David Oberacker <david.oberacker(at)gmail.com>
 * @version 1.0.0
 */
    class HOME_IOT_CTL_API SensorDevice : public Device {
    private:
        /*!
         * @brief List of sensors in this device.
         * @details This contains the common names of the sensors available to the device.
         */
        std::vector<std::string> device_sensors;
    public:

        /*!
         * @brief Getter for the sensors available in this device.
         * @details This contains the common names of the sensors available to the device.
         * @return The common names of installed sensors.
         */
        [[nodiscard]] const std::vector<std::string> &getDeviceSensors() const;

        /*!
         * @brief Adds a single sensor with a name to the device.
         * @param sensor_name The name of the sensor. This string has to be at least one char long or a exception is thrown.
         *
         * @throws std::invalid_argument If the given sensor_name is not at least one char long this exception is thrown.
         */
        void addSensor(const std::string &sensor_name) noexcept(false);

        /*!
         * @brief Adds a set of sensors with given names to the device.
         * @param sensors The names of the sensors. Ever name has to be at least one char long or a exception is thrown.
         *
         * @throws std::invalid_argument If one given sensor name is not at least one char long this exception is thrown.
         * If this happens the sensor_names that are infront in the collection then the name causing the exception
         * are added to the device. The names following are not.
         */
        void addSensors(const std::vector<std::string> &sensors) noexcept(false);

        /*!
         * @brief Creates a new device with sensor capabilities.
         * @details This creates a new sensor device registered from the network.
         *
         * @param deviceName The mqtt network global device name.
         * @param isAvailable Indicator if the device was available at the last indexing.
         */
        SensorDevice(const std::string &deviceName, bool isAvailable);

        /*!
         * @brief Prints a common representation of the device as a stream.
         * @param os The stream to write the representation to.
         * @param device The device to represent.
         * @return A stream with the representation added. Can be used to chain calls.
         */
        friend std::ostream HOME_IOT_CTL_API &operator<<(std::ostream &os, const D4ve::Iot::Devices::SensorDevice &device);
    };
};

#endif //HOME_IOT_CTL_IOT_DEVICE_HPP
