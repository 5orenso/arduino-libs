#ifndef MQTT_UTIL_H
#define MQTT_UTIL_H

// using namespace std;
#include <Arduino.h>
#include <PubSubClient.h>

class MqttUtil {
    bool
        debug;
    int
        chipId;
    const char* inTopic;
    const char* outTopic;
    const char* ssid;
    const char* packageName;
    public:
        MqttUtil(int _chipId, const char* packageName, const char* ssid, const char* inTopic, const char* outTopic, bool debugSetting);
        void reconnectMqtt(PubSubClient &_mqttClient, uint32 ipAddress, long wifiDisconnectedPeriode);
        void publishMessage(PubSubClient &_mqttClient, char *message);
        void publishKeyValueInt(PubSubClient &mqttClient, char const *key, int value);
        void publishKeyValueInt(PubSubClient &mqttClient, char const *key, int value, char const *key2, int value2);
        void publishKeyValueFloat(PubSubClient &mqttClient, char const *key, float value, int length, int decimal);
        void publishKeyValueFloat(PubSubClient &mqttClient, char const *key, float value, char const *key2, float value2, int length, int decimal);
        void publishKeyValueFloat(PubSubClient &mqttClient, char const *key, float value, char const *key2, float value2, char const *key3, float value3, int length, int decimal);
        void sendControllerInfo(PubSubClient &_mqttClient, uint32 ipAddress, long wifiDisconnectedPeriode);
};

#endif //MQTT_UTIL_H