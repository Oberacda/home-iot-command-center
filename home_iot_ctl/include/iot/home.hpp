//
// Created by David Oberacker on 20.01.20.
//

#ifndef HOME_IOT_COMMAND_CENTER_HOME_HPP
#define HOME_IOT_COMMAND_CENTER_HOME_HPP

#pragma once

#include <memory>
#include <functional>
#include <utility>

#include <mqtt/async_client.h>

#include "iot/device.hpp"
#include "home_iot_ctl_exports.hpp"

/*!
 * @brief Class to represent the callbacks used on async mqtt operations!
 */
class HOME_IOT_CTL_API_NO_EXPORT HomeMqttCallbacks : public virtual mqtt::callback,
                          public virtual mqtt::iaction_listener

{
private:
    /*!
     * @brief Upstream callbacks that are used to process incoming messages!
     */
    std::vector<std::function<void(DeviceChange)>> on_message_upstream_callbacks;

    /*!
     * @brief MQTT connection retry counter!
     */
    int nretry_;

    /*!
     * @brief MQTT client used for reconnecting the client!
     */
    mqtt::async_client& cli_;

    /*!
     * @brief MQTT connection options for reconnecting!
     */
    mqtt::connect_options& connOpts_;

public:

    /**!
     * @brief Function to register a new upstream callback on message received.
     *
     * @todo This function has to be made thread save in order to allow running in a multithreaded environement!
     * @param callback The function callback to register.
     */
    void register_on_message_upstream_callback(const std::function<void(DeviceChange)>& callback);

    void connected(const mqtt::string &string) override;

    void connection_lost(const mqtt::string &string) override;

    void message_arrived(mqtt::const_message_ptr ptr) override;

    void on_failure(const mqtt::token &asyncActionToken) override;

    void on_success(const mqtt::token &asyncActionToken) override;

    HomeMqttCallbacks(mqtt::async_client& cli, mqtt::connect_options& connOpts, std::vector<std::function<void(DeviceChange)>> on_message_upstream_callbacks)
    : nretry_(0), cli_(cli), connOpts_(connOpts), on_message_upstream_callbacks(std::move(on_message_upstream_callbacks)) {}

};

class HOME_IOT_CTL_API Home {
private:
    std::unique_ptr<mqtt::async_client> mqtt_client;
    HomeMqttCallbacks callbacks;

public:
    void send_command(DeviceChange& change);
};

#endif //HOME_IOT_COMMAND_CENTER_HOME_HPP
