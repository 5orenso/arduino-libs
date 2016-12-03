## CO2 MH-Z19 sensor library

Purpose of this lib is to make it easy to sample data and report without blocking the main loop.


## installation

Library can be found at PlatformIO.org:
http://platformio.org/lib/show/1293/Co2SensorMHZ19

```bash
# Using library Id
$ platformio lib install 1293

# Using library Name
$ platformio lib install "Co2SensorMHZ19"

# Install specific version
$ platformio lib install 1293@1.0.0
$ platformio lib install "Co2SensorMHZ19@1.0.0"
```


## Example

```cpp
#include <Arduino.h>
#include <Co2SensorMHZ19.h>

#define PUBLISH_INTERVAL 15
#define CO2_MH_Z19_RX D7
#define CO2_MH_Z19_TX D8

Co2SensorMHZ19 co2 = Co2SensorMHZ19(CO2_MH_Z19_RX, CO2_MH_Z19_TX, 20, false);
long lastRun = millis();

void setup(void) {
    Serial.begin(115200);
    co2.begin();
}

void loop() {
    long now = millis();
    co2.sampleValue();
    if (now - lastRun > (PUBLISH_INTERVAL * 1000)) {
        lastRun = now;

        float valueCo2 = co2.readValue();
        Serial.println(valueCo2);
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
