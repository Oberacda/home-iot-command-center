//
// Created by David Oberacker on 20.01.20.
//

#ifndef HOME_IOT_COMMAND_CENTER_HOME_HPP
#define HOME_IOT_COMMAND_CENTER_HOME_HPP

#pragma once

#include <memory>
#include <functional>
#include <utility>
#include <type_traits>

#include <mqtt/async_client.h>

#include "iot/device.hpp"
#include "home_iot_ctl_exports.hpp"

namespace D4ve::Iot::Home {

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
     * @brief Class to represent the callbacks used on async mqtt operations!
     */
    class HOME_IOT_CTL_API_NO_EXPORT HomeMqttCallbacks : public virtual mqtt::callback,
                                                         public virtual mqtt::iaction_listener {
    private:
        /*!
         * @brief Vector of clients that are subscribed to the callbacks defined in this method.
         * @details These subscribers define callbacks that move incoming messages up to the required higher functions.
         */
        std::vector<HomeSubscriber> subscribers;

        /*!
         * @brief MQTT connection retry counter!
         */
        int nretry_;

        /*!
         * @brief MQTT client used for reconnecting the client!
         */
        mqtt::async_client &cli_;

        /*!
         * @brief MQTT connection options for reconnecting!
         */
        mqtt::connect_options &connOpts_;

    public:

        void register_subscriber(const HomeSubscriber &subscriber);

        void connected(const mqtt::string &string) override;

        void connection_lost(const mqtt::string &string) override;

        void message_arrived(mqtt::const_message_ptr ptr) override;

        void on_failure(const mqtt::token &asyncActionToken) override;

        void on_success(const mqtt::token &asyncActionToken) override;

        HomeMqttCallbacks(
                mqtt::async_client &cli,
                mqtt::connect_options &connOpts,
                std::vector<HomeSubscriber> subscribers)
                : nretry_(0),
                  cli_(cli),
                  connOpts_(connOpts),
                  subscribers(std::move(subscribers)) {};

        HomeMqttCallbacks(
                mqtt::async_client &cli,
                mqtt::connect_options &connOpts) : nretry_(0),
                                                   cli_(cli),
                                                   connOpts_(connOpts),
                                                   subscribers({}) {};
    };

    class HOME_IOT_CTL_API Home {
    private:
        std::unique_ptr<mqtt::async_client> mqtt_client;
        HomeMqttCallbacks callbacks;
    };
};

#endif //HOME_IOT_COMMAND_CENTER_HOME_HPP
