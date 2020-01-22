//
// Created by David Oberacker on 20.01.20.
//

#include "iot/home.hpp"

void HomeMqttCallbacks::connected(const std::string &string) {
    callback::connected(string);
}

void HomeMqttCallbacks::connection_lost(const std::string &string) {
    callback::connection_lost(string);
}

void HomeMqttCallbacks::message_arrived(mqtt::const_message_ptr ptr) {
    callback::message_arrived(ptr);
}

void HomeMqttCallbacks::on_failure(const mqtt::token &asyncActionToken) {

}

void HomeMqttCallbacks::on_success(const mqtt::token &asyncActionToken) {

}

void HomeMqttCallbacks::register_on_message_upstream_callback(const std::function<void(DeviceChange)>& callback) {
    this->on_message_upstream_callbacks.push_back(callback);
}

void Home::send_command(DeviceChange &change) {

}
