/*!
 * @file home.cpp
 * @brief Source file for classes related to home client in the IoT network.
 *
 * @author David Oberacker <david.oberacker(at)gmail.com>
 * @version 1.0.0
 * @date 20.01.20
 */

#include "iot/home.hpp"

#include "iot/device.hpp"

#include <string>
#include <utility>

#include <rapidjson/document.h>

D4ve::Iot::Home::HomeSubscriber::HomeSubscriber(
        std::function<void(D4ve::Iot::Devices::SensorDevice)> onAnnounceCallback,
        std::function<void(D4ve::Iot::Devices::SensorDevice)> onChangeCallback,
        std::function<void(std::string)> onErrorCallback,
        std::function<void(std::string)> onDisconnectCallback,
        std::function<void(std::string)> onConnectCallback) : on_announce_callback(
        std::move(
                onAnnounceCallback)), on_change_callback(std::move(onChangeCallback)), on_error_callback(
        std::move(onErrorCallback)),
                                                              on_disconnect_callback(
                                                                      std::move(
                                                                              onDisconnectCallback)),
                                                              on_connect_callback(std::move(
                                                                      onConnectCallback)) {}

D4ve::Iot::Home::HomeSubscriber::~HomeSubscriber() = default;

void D4ve::Iot::Home::HomeSubscriber::announce(D4ve::Iot::Devices::SensorDevice device) {
    this->on_announce_callback(std::move(device));
}

void D4ve::Iot::Home::HomeSubscriber::change(D4ve::Iot::Devices::SensorDevice device) {
    this->on_change_callback(std::move(device));
}

void D4ve::Iot::Home::HomeSubscriber::error(const std::string &error_message) {
    this->on_error_callback(error_message);
}

void D4ve::Iot::Home::HomeSubscriber::connect(const std::string &connect_message) {
    this->on_connect_callback(connect_message);
}

void D4ve::Iot::Home::HomeSubscriber::disconnect(const std::string &disconnect_message) {
    this->on_disconnect_callback(disconnect_message);
}




