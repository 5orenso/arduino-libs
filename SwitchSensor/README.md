## Switch sensor library

Purpose of this lib is to make it easy to sample data and report without blocking the main loop.


## installation

Library can be found at PlatformIO.org:
http://platformio.org/lib/show/1296/SwitchSensor

```bash
# Using library Id
$ platformio lib install 1296

# Using library Name
$ platformio lib install "SwitchSensor"

# Install specific version
$ platformio lib install 1296@1.0.0
$ platformio lib install "SwitchSensor@1.0.0"
```


## Example

```cpp
#include <Arduino.h>
#include <SwitchSensor.h>

#define PUBLISH_INTERVAL 15
#define SWITCH_SENSOR_PIN D5

SwitchSensor mySwitch = SwitchSensor(SWITCH_SENSOR_PIN, 1, false, false);
long lastRun = millis();
long switchSensorStart;

void setup(void) {
    Serial.begin(115200);
    mySwitch.begin();
}

void loop() {
    long now = millis();
    int switchStateChange = mySwitch.sampleValue();
    if (switchStateChange >= 0) {
        Serial.print(" --> switchStateChange: "); Serial.println(switchStateChange);
        if (switchStateChange == 1) {
            switchSensorStart = millis();
        } else {
            long switchSessionLength = millis() - switchSensorStart;
            Serial.print(" --> switchSessionLength: "); Serial.println(switchSessionLength);
        }
    }

    if (now - lastRun > (PUBLISH_INTERVAL * 1000)) {
        lastRun = now;
    }
    delay(0);
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
