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
