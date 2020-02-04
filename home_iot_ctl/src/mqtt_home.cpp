/*!
 * @file mqtt_home.cpp
 * @brief Source file for classes related to the mqtt home client in the IoT network.
 *
 * @author David Oberacker <david.oberacker(at)gmail.com>
 * @version 1.0.0
 * @date 04.02.20
 */

#include <string>
#include <utility>
#include <rapidjson/document.h>

#include "iot/home.hpp"
#include "iot/device.hpp"

namespace D4ve::Iot::Home {

    /*!
     * @brief Class to represent the callbacks used on async mqtt operations!
     */
    class HOME_IOT_CTL_API_NO_EXPORT MqttHomeIotClientCallbacks : public virtual mqtt::callback,
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

        void register_subscriber(const HomeSubscriber &subscriber) {
            this->subscribers.push_back(subscriber);
        };

        void connected(const mqtt::string &string) override {
            callback::connected(string);
        };

        void connection_lost(const mqtt::string &string) override {
            callback::connection_lost(string);
        };

        void message_arrived(mqtt::const_message_ptr ptr) override {
            if (ptr->get_topic() == "home/arduino/announce") {
                rapidjson::Document d;
                d.Parse(ptr->get_payload().data());

                if (!d.HasParseError()) {
                    std::string device_type = d["device_type"].GetString();
                    std::string device_name = d["name"].GetString();
                    if (device_type == "sensor") {
                        D4ve::Iot::Devices::SensorDevice device(device_name, D4ve::Iot::Devices::DeviceStatus::UNKNOWN);
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
        };

        void on_failure(const mqtt::token &asyncActionToken) override {
        };

        void on_success(const mqtt::token &asyncActionToken) override {

        };

        MqttHomeIotClientCallbacks(
                mqtt::async_client &cli,
                mqtt::connect_options &connOpts,
                std::vector<HomeSubscriber> subscribers)
                : nretry_(0),
                  cli_(cli),
                  connOpts_(connOpts),
                  subscribers(std::move(subscribers)) {};

        MqttHomeIotClientCallbacks(
                mqtt::async_client &cli,
                mqtt::connect_options &connOpts) : nretry_(0),
                                                   cli_(cli),
                                                   connOpts_(connOpts),
                                                   subscribers({}) {};
    };

    class HOME_IOT_CTL_API_NO_EXPORT MqttHomeIotClient : public HomeIotClient {
    public:
        void addSubscriber(const HomeSubscriber &subscriber) override {

        }

        bool isConnected() override {
            return false;
        }

        void connectClient() override {

        }

        void requestAnnounce() override {

        }

        void getDeviceStatus(Devices::Device device) override {

        }

        void setDeviceStatus(Devices::Device details, Devices::DeviceStatus deviceStatus) override {

        }

    private:
        std::unique_ptr<mqtt::async_client> mqtt_client;
        MqttHomeIotClientCallbacks callbacks;
    };

/*!
 * @brief Creates a new HomeIotClient that uses the MQTT protocol for commuication.
 * @return
 */
    std::unique_ptr<HomeIotClient> createMqttHomeIotClient() {
        return std::unique_ptr<MqttHomeIotClient>();
    }


}