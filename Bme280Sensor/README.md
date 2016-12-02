## BME280 sensor library

This library is built upon https://www.github.com/finitespace/BME280 sensor library.

Purpose of this lib is to make it easy to sample data and report without blocking the main loop.


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


## Contribute

Please contribute with pull-requests.
