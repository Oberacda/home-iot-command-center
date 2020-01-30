//
// Created by David Oberacker on 20.01.20.
//
#include "iot/home.hpp"

#include "iot/device.hpp"

#include <string>
#include <utility>

#include <rapidjson/document.h>

void D4ve::Iot::Home::HomeMqttCallbacks::connected(const std::string &string) {
    callback::connected(string);
}

void D4ve::Iot::Home::HomeMqttCallbacks::connection_lost(const std::string &string) {
    callback::connection_lost(string);
}

void D4ve::Iot::Home::HomeMqttCallbacks::message_arrived(mqtt::const_message_ptr ptr) noexcept(false) {

    if (ptr->get_topic() == "home/arduino/announce") {
        rapidjson::Document d;
        d.Parse(ptr->get_payload().data());

        if (!d.HasParseError()) {
            std::string device_type = d["device_type"].GetString();
            std::string device_name = d["name"].GetString();
            if (device_type == "sensor") {
                D4ve::Iot::Devices::SensorDevice device(device_name, true);
                auto sensor_names = d["sensors"].GetArray();

                for (auto &sensor_name:sensor_names) {
                    device.addSensor(sensor_name.GetString());
                }

                for (auto &subscriber : this->subscribers) {
                    subscriber.announce(device);
                }
            }
        } else {
            for (auto &subscriber : this->subscribers) {
                subscriber.error("Invalid message received!");
            }
        }
    }

    callback::message_arrived(ptr);

}

void D4ve::Iot::Home::HomeMqttCallbacks::on_failure(const mqtt::token &asyncActionToken) {

}

void D4ve::Iot::Home::HomeMqttCallbacks::on_success(const mqtt::token &asyncActionToken) {

}

void D4ve::Iot::Home::HomeMqttCallbacks::register_subscriber(const HomeSubscriber &subscriber) {
    this->subscribers.push_back(subscriber);
}


D4ve::Iot::Home::HomeSubscriber::HomeSubscriber(std::function<void(D4ve::Iot::Devices::SensorDevice)> onAnnounceCallback,
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
