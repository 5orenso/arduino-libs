#ifndef GENERIC_ANALOG_SENSOR_H
#define GENERIC_ANALOG_SENSOR_H

// using namespace std;
#include <Arduino.h>

class GenericAnalogSensor {
    bool
        debug;
    uint8_t
        sampleIndex,
        samplesTotal;
    float
        *samples;
    uint8_t
        pin;
    long
        lastSample;
    public:
        GenericAnalogSensor(uint8_t sensorPin, uint8_t samplesCount, bool debugSetting);
        bool begin();
        float sampleValue();
        float readValue();
};

#endif //GENERIC_ANALOG_SENSOR_H