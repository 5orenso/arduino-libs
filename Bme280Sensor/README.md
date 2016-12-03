## BME280 sensor library

This library is built upon https://www.github.com/finitespace/BME280 sensor library.

Purpose of this lib is to make it easy to sample data and report without blocking the main loop.


## installation

Library can be found at PlatformIO.org:
http://platformio.org/lib/show/1292/Bme280Sensor

```bash
# Using library Id
$ platformio lib install 1292

# Using library Name
$ platformio lib install "Bme280Sensor"

# Install specific version
$ platformio lib install 1292@1.0.0
$ platformio lib install "Bme280Sensor@1.0.0"
```


## Example

```cpp
#include <Arduino.h>
#include <Bme280Sensor.h>

#define PUBLISH_INTERVAL 15
#define BME280_SDA D2
#define BME280_SCL D1

Bme280Sensor bme280 = Bme280Sensor(BME280_SDA, BME280_SCL, 20, false);
long lastRun = millis();

void setup(void) {
    Serial.begin(115200);
    bme280.begin();
}

void loop() {
    long now = millis();
    bme280.sampleValue();
    if (now - lastRun > (PUBLISH_INTERVAL * 1000)) {
        lastRun = now;

        float temperature = bme280.readValueTemperature();
        Serial.println(temperature);
        float pressure = bme280.readValuePressure();
        Serial.println(pressure);
        float humidity = bme280.readValueHumidity();
        Serial.println(humidity);
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
