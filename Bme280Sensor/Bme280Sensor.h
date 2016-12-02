
#ifndef BME280_SENSOR_H
#define BME280_SENSOR_H

#include <Arduino.h>
#include <Wire.h>
#include <BME280.h>

class Bme280Sensor {
    bool
        debug;
    int
        sampleIndex,
        samplesTotal;
    float
        *samplesTemperature,
        *samplesPressure,
        *samplesHumidity;
        // *samplesDewPoint;
    uint8_t
        sdaPin,
        sclPin;
    long
        lastSample;
    BME280 bme280; // SDA = D2, SCL = D1
    public:
        Bme280Sensor(uint8_t sdaPin, uint8_t sclPin, int samplesCount, bool debugSetting);
        bool begin();
        float sampleValue();
        float readValueTemperature();
        float readValuePressure();
        float readValueHumidity();
};

#endif //BME280_SENSOR_H