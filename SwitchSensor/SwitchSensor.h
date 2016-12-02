#ifndef SWITCH_SENSOR_H
#define SWITCH_SENSOR_H

#include <Arduino.h>

class SwitchSensor {
    bool
        debug,
        verbose;
    int
        sampleIndex,
        samplesTotal;
    float
        *samples;
    uint8_t
        pin;
    long
        lastSample;
    public:
        SwitchSensor(uint8_t sensorPin, int samplesCount, bool debugSetting, bool verboseSetting);
        bool begin();
        int sampleValue();
        float readValue();
};

#endif //SWITCH_SENSOR_H