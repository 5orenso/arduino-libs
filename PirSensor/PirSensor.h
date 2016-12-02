#ifndef PIR_SENSOR_H
#define PIR_SENSOR_H

#include <Arduino.h>

class PirSensor {
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
        PirSensor(uint8_t sensorPin, int samplesCount, bool debugSetting, bool verboseSetting);
        bool begin();
        int sampleValue();
        float readValue();
};

#endif //PIR_SENSOR_H