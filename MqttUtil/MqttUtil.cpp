#include <MqttUtil.h>
#include <PubSubClient.h>
// #include <Math.h>

#if ARDUINO >= 100
#include "Arduino.h"
#else
extern "C" {
#include "WConstants.h"
}
#endif

using namespace std;

MqttUtil::MqttUtil(int _chipId, const char* _packageName, const char* _ssid, const char* _inTopic, const char* _outTopic, bool debugSetting) {
    debug = debugSetting;
    packageName = _packageName;
    ssid = _ssid;
    inTopic = _inTopic;
    outTopic = _outTopic;
    chipId = _chipId;
}

void MqttUtil::publishMessage(PubSubClient &mqttClient, char *message) {
    Serial.print("Publish message: "); Serial.println(message);
    mqttClient.publish(outTopic, message);
}

void MqttUtil::publishKeyValueInt(PubSubClient &mqttClient, char const *key, int value) {
    char msg[150];
    snprintf(msg, 150, "{ \"chipId\": %d, \"%s\": %d }", chipId, key, value);
    Serial.print("Publish message: "); Serial.println(msg);
    mqttClient.publish(outTopic, msg);
}

void MqttUtil::publishKeyValueInt(PubSubClient &mqttClient, char const *key, int value, char const *key2, int value2) {
    char msg[150];
    snprintf(msg, 150, "{ \"chipId\": %d, \"%s\": %d, \"%s\": %d  }", chipId, key, value, key2, value2);
    Serial.print("Publish message: "); Serial.println(msg);
    mqttClient.publish(outTopic, msg);
}

void MqttUtil::publishKeyValueFloat(PubSubClient &mqttClient, char const *key, float value, int length, int decimal) {
    char msg[150];
    char textValue[10];
    dtostrf(value, length, decimal, textValue); // first 2 is the width including the . (1.) and the 2nd 2 is the precision (.23)
    snprintf(msg, 150, "{ \"chipId\": %d, \"%s\": %s }", chipId, key, textValue);
    Serial.print("Publish message: "); Serial.println(msg);
    mqttClient.publish(outTopic, msg);
}

void MqttUtil::publishKeyValueFloat(PubSubClient &mqttClient, char const *key, float value, char const *key2, float value2, int length, int decimal) {
    char msg[150];
    char textValue[10];
    char textValue2[10];
    dtostrf(value, length, decimal, textValue); // first 2 is the width including the . (1.) and the 2nd 2 is the precision (.23)
    dtostrf(value2, length, decimal, textValue2); // first 2 is the width including the . (1.) and the 2nd 2 is the precision (.23)
    snprintf(msg, 150, "{ \"chipId\": %d, \"%s\": %s, \"%s\": %s }", chipId, key, textValue, key2, textValue2);
    Serial.print("Publish message: "); Serial.println(msg);
    mqttClient.publish(outTopic, msg);
}

void MqttUtil::publishKeyValueFloat(PubSubClient &mqttClient, char const *key, float value, char const *key2, float value2, char const *key3, float value3, int length, int decimal) {
    char msg[150];
    char textValue[10];
    char textValue2[10];
    char textValue3[10];
    dtostrf(value, length, decimal, textValue); // first 2 is the width including the . (1.) and the 2nd 2 is the precision (.23)
    dtostrf(value2, length, decimal, textValue2); // first 2 is the width including the . (1.) and the 2nd 2 is the precision (.23)
    dtostrf(value3, length, decimal, textValue3); // first 2 is the width including the . (1.) and the 2nd 2 is the precision (.23)
    snprintf(msg, 150, "{ \"chipId\": %d, \"%s\": %s, \"%s\": %s, \"%s\": %s }", chipId, key, textValue, key2, textValue2, key3, textValue3);
    Serial.print("Publish message: "); Serial.println(msg);
    mqttClient.publish(outTopic, msg);
}

void MqttUtil::reconnectMqtt(PubSubClient &mqttClient, uint32 ipAddress, long wifiDisconnectedPeriode) {
    while (!mqttClient.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        // Attempt to connect
        if (mqttClient.connect(clientId.c_str())) {
            Serial.println("Connected to MQTT!");
            mqttClient.subscribe(inTopic);
            sendControllerInfo(mqttClient, ipAddress, wifiDisconnectedPeriode);
        } else {
            Serial.print("failed, rc="); Serial.print(mqttClient.state()); Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void MqttUtil::sendControllerInfo(PubSubClient &mqttClient, uint32 ipAddress, long wifiDisconnectedPeriode) {
    if (mqttClient.connected()) {
        // --[ Publish this device to AWS IoT ]----------------------------------------
        int nodemcuChipId = ESP.getChipId(); // returns the ESP8266 chip ID as a 32-bit integer.
        String nodemcuResetReason = ESP.getResetReason(); // returns String containing the last reset resaon in human readable format.
        int nodemcuFreeHeapSize = ESP.getFreeHeap(); // returns the free heap size.
        // Several APIs may be used to get flash chip info:
        int nodemcuFlashChipId = ESP.getFlashChipId(); // returns the flash chip ID as a 32-bit integer.
        int nodemcuFlashChipSize = ESP.getFlashChipSize(); // returns the flash chip size, in bytes, as seen by the SDK (may be less than actual size).
        // int nodemcuFlashChipSpeed = ESP.getFlashChipSpeed(void); // returns the flash chip frequency, in Hz.
        // int nodemcuCycleCount = ESP.getCycleCount(); // returns the cpu instruction cycle count since start as an unsigned 32-bit. This is useful for accurate timing of very short actions like bit banging.
        // WiFi.macAddress(mac) is for STA, WiFi.softAPmacAddress(mac) is for AP.
        // int nodemcuIP; // = WiFi.localIP(); // is for STA, WiFi.softAPIP() is for AP.

        char msg[150];
        char resetReason[25];
        strcpy(resetReason, nodemcuResetReason.c_str());
        // uint32 ipAddress;
        char ipAddressFinal[16];
        // ipAddress = WiFi.localIP();
        if (ipAddress) {
            const int NBYTES = 4;
            uint8 octet[NBYTES];
            for(int i = 0 ; i < NBYTES ; i++) {
                octet[i] = ipAddress >> (i * 8);
            }
            sprintf(ipAddressFinal, "%d.%d.%d.%d", octet[0], octet[1], octet[2], octet[3]);
        }
        snprintf(msg, 150, "{ \"chipId\": %d, \"freeHeap\": %d, \"ip\": \"%s\", \"ssid\": \"%s\" }",
            nodemcuChipId, nodemcuFreeHeapSize, ipAddressFinal, ssid
        );
        // if (VERBOSE) {
            Serial.print("Publish message: "); Serial.println(msg);
        // }
        mqttClient.publish(outTopic, msg);

        // More info about the software.
        snprintf(msg, 150, "{ \"chipId\": %d, \"ip\": \"%s\", \"sw\": \"%s\" }",
            nodemcuChipId, ipAddressFinal, packageName
        );
        // if (VERBOSE) {
            Serial.print("Publish message: "); Serial.println(msg);
        // }
        mqttClient.publish(outTopic, msg);

        // More info about the software.
        // 0 -> normal startup by power on
        // 1 -> hardware watch dog reset
        // 2 -> software watch dog reset (From an exception)
        // 3 -> software watch dog reset system_restart (Possibly unfed wd got angry)
        // 4 -> soft restart (Possibly with a restart command)
        // 5 -> wake up from deep-sleep
        snprintf(msg, 150, "{ \"chipId\": %d, \"wifiOfflinePeriode\": %d, \"resetReason\": \"%s\" }",
            nodemcuChipId, wifiDisconnectedPeriode, resetReason
        );
        // if (VERBOSE) {
            Serial.print("Publish message: "); Serial.println(msg);
        // }
        mqttClient.publish(outTopic, msg);
    }
}