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
     * @brief Status of a device in the IoT network.
     *
     * @details This enum encodes the status of a device. The device has to answer at least once in order to get a status.
     */
    enum class DeviceStatus {
        UNKNOWN, ///< Device status is unknown.
        DISCONNECTED, ///< Device is known but does not respond any more.
        IDLE, ///< The device is available but not doing any job.
        RUNNING, ///< The device is available and is running its job.
        ERROR ///< The device is in a error state.
    };

    std::ostream HOME_IOT_CTL_API &operator<<(std::ostream& os, DeviceStatus status);

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
         * @brief The status of the device.
         */
        DeviceStatus status;


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
         * @param status Status of the device.
         */
        Device(std::string deviceName, DeviceStatus status);

        /*!
         * @brief Getter for the unique MQTT Client name of the device.
         *
         * @details This is a unique identifier in the network. It is valid for all nodes in the network.s
         *
         * @return The unique MQTT client name.
         */
        [[nodiscard]] const std::string &getDeviceName() const;

        /*!
         * @brief Gets the current status of the device.
         *
         * @return Current known status of the device.
         */
        [[nodiscard]] DeviceStatus getStatus() const;

        /*!
         * @brief Sets a new status for the device.
         *
         * @param status The new status to be set.
         */
        void setStatus(DeviceStatus status);

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
        SensorDevice(const std::string &deviceName, DeviceStatus status);

        /*!
         * @brief Prints a common representation of the device as a stream.
         * @param os The stream to write the representation to.
         * @param device The device to represent.
         * @return A stream with the representation added. Can be used to chain calls.
         */
        friend std::ostream HOME_IOT_CTL_API &
        operator<<(std::ostream &os, const D4ve::Iot::Devices::SensorDevice &device);
    };

};

#endif //HOME_IOT_CTL_IOT_DEVICE_HPP
