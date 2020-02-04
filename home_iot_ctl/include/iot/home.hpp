/*!
 * @file home.hpp
 * @brief Header declaring classes related to the home mangement of the IoT network.
 *
 * @author David Oberacker <david.oberacker(at)gmail.com>
 * @version 1.0.0
 * @date 20.01.20
 */


#ifndef HOME_IOT_CTL_IOT_HOME_HPP
#define HOME_IOT_CTL_IOT_HOME_HPP

#pragma once

#include <memory>
#include <functional>
#include <utility>
#include <type_traits>

#include <mqtt/async_client.h>

#include "iot/device.hpp"
#include "home_iot_ctl_exports.hpp"

namespace D4ve::Iot::Home {

    /*!
     * @brief Class representing the callbacks used for the Home IoT network client.
     *
     * @details Callback functions for specific network events can be added to this class.
     *
     * @author David Oberacker <david.oberacker(at)gmail.com>
     * @version 1.0.0
     */
    class HOME_IOT_CTL_API HomeSubscriber {
    private:
        std::function<void(D4ve::Iot::Devices::SensorDevice)> on_announce_callback;
        std::function<void(D4ve::Iot::Devices::SensorDevice)> on_change_callback;
        std::function<void(std::string)> on_error_callback;
        std::function<void(std::string)> on_disconnect_callback;
        std::function<void(std::string)> on_connect_callback;
    public:
        HomeSubscriber(std::function<void(D4ve::Iot::Devices::SensorDevice)> onAnnounceCallback,
                       std::function<void(D4ve::Iot::Devices::SensorDevice)> onChangeCallback,
                       std::function<void(std::string)> onErrorCallback,
                       std::function<void(std::string)> onDisconnectCallback,
                       std::function<void(std::string)> onConnectCallback);

        virtual ~HomeSubscriber();

        void announce(D4ve::Iot::Devices::SensorDevice device);

        void change(D4ve::Iot::Devices::SensorDevice device);

        void error(const std::string &error_message);

        void connect(const std::string &connect_message);

        void disconnect(const std::string &disconnect_message);
    };

    /*!
     * @brief Class representing a client for the home IoT network.
     *
     * @details The client function allows to send commands and register callbacks to and from the network.
     *
     * @author David Oberacker <david.oberacker(at)gmail.com>
     * @version 1.0.0
     */
    class HOME_IOT_CTL_API HomeIotClient {
    public:
        /*!
         * @brief Adds a subscriber to home network events.
         * @param subscriber The subscriber to add to the HomeIoTClient.
         */
        virtual void addSubscriber(const HomeSubscriber& subscriber) = 0;

        /*!
         * @brief Check if the Client is connected to the network.
         * @return true iff the client is connected otherwise false.
         */
        virtual bool isConnected() = 0;

        /*!
         * @brief Starts to connect the client.
         * Iff successful a callback will be called.
         */
        virtual void connectClient() = 0;

        /*!
         * @brief Requests an announcement from all devices in the network.
         */
        virtual void requestAnnounce() = 0;

        /*!
         * @brief Gets the status of a single device that was previously announced.
         *
         * @details IF the status is returned a callback is returned.
         *
         * @param device The device to get the status from.
         */
        virtual void getDeviceStatus(Devices::Device device) = 0;

        /*!
         * @brief Sets the device status for a previously announced device.
         * @details IF the status is changed a callback will be send.
         * @param details The device to change the status of.
         * @param deviceStatus The new status to set on the device.
         */
        virtual void setDeviceStatus(Devices::Device details, Devices::DeviceStatus deviceStatus) = 0;
    };

    /*!
     * Creates a new instance of a Mqtt based home IoT client.
     *
     * @return A newly created mqtt home iot client.
     */
    static std::unique_ptr<HomeIotClient> createMqttHomeIotClient();
};

#endif //HOME_IOT_CTL_IOT_HOME_HPP
