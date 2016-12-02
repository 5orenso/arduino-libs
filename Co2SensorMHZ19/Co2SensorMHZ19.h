
#ifndef CO2SENSOR_MH_Z19_H
#define CO2SENSOR_MH_Z19_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class Co2SensorMHZ19 {
    bool
        debug;
    int
        sampleIndex,
        samplesTotal;
    float
        *samples;
    uint8_t
        rxPin,
        txPin;
    long
        lastSample;
    SoftwareSerial co2Serial;
    public:
        Co2SensorMHZ19(uint8_t sensorRxPin, uint8_t sensorTxPin, int samplesCount, bool debugSetting);
        bool begin();
        float sampleValue();
        float readValue();
};

#endif //CO2SENSOR_MH_Z19_H