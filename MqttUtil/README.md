## MqttUtil library

Purpose of this lib is to gather commonly used functions into one library to avoid duplicating code.


## installation

Library can be found at PlatformIO.org:
http://platformio.org/lib/show/1302/MqttUtil

```bash
# Using library Id
$ platformio lib install 1302

# Using library Name
$ platformio lib install "MqttUtil"

# Install specific version
$ platformio lib install 1302@1.0.0
$ platformio lib install "MqttUtil@1.0.0"
```


## Example

```cpp

#include <MqttUtil.h>

...

MqttUtil mqttUtil = MqttUtil(nodemcuChipId, PACKAGE_NAME, ssid, inTopic, outTopic, false);

...

void reconnectMqtt(uint32 ipAddress, long wifiDisconnectedPeriode) {
    while (!client.connected()) {
        ...
        if (client.connect(clientId.c_str())) {
            Serial.println("Connected to MQTT!");
            client.subscribe(inTopic);
            mqttUtil.sendControllerInfo(client, ipAddress, wifiDisconnectedPeriode);
        }
    }
}

void loop() {
    ...
}

```


## Other resources

* [Getting started with NodeMCU, Arduino or Wemos D1 mini](https://github.com/5orenso/arduino-getting-started)
* [NodeMCU code for the toilet sensors integrated with AWS IoT](https://github.com/5orenso/nodemcu-mqtt-toilet-project)
* [NodeMCU code for the toilet lights integrated with AWS IoT](https://github.com/5orenso/nodemcu-mqtt-toilet-project-display)
* [NodeMCU code for home sensors integrated with AWS IoT](https://github.com/5orenso/nodemcu-mqtt-home-sensors)
* [NodeMCU code for BME280 sensor integrated with AWS IoT](https://github.com/5orenso/nodemcu-mqtt-bme280)
* [NodeMCU code for DallasTemperature sensor integrated with AWS IoT](https://github.com/5orenso/nodemcu-mqtt-dallastemperature)
* [Arduino code for Neopixel animations](https://github.com/5orenso/nodemcu-neopixel-animations)
* [AMI for MQTT Broker](https://github.com/5orenso/aws-ami-creation)
* [All PlatforIO.org libs by Sorenso](http://platformio.org/lib/search?query=author%253A%2522Sorenso%2522)


## Contribute

Please contribute with pull-requests.
