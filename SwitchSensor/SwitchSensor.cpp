#include <SwitchSensor.h>
#include <Math.h>
#include <Arduino.h>

using namespace std;

SwitchSensor::SwitchSensor(uint8_t sensorPin, int samplesCount, bool debugSetting, bool verboseSetting) {
    debug = debugSetting;
    verbose = verboseSetting;
    sampleIndex = 0;
    lastSample = 0;
    samplesTotal = samplesCount;
    samples = new float[samplesCount];
    pin = sensorPin;
}

bool SwitchSensor::begin() {
    pinMode(pin, INPUT);
}

int SwitchSensor::sampleValue() {
    long now = millis();
    // Don't sample more often than every 100 millisecond.
    if (now - lastSample > 100) {
        lastSample = now;
        float lastValue = readValue();
        samples[sampleIndex] = digitalRead(pin);
        int currentValue = round(samples[sampleIndex]);
        sampleIndex++;
        if (sampleIndex >= samplesTotal) {
            sampleIndex = 0;
        }
        if (currentValue == 1) {      // Motion detected
            if (lastValue == 0.00) {  // Do we need to send a notification?
                return 1;
            }
        } else {                      // End motion detected
            if (lastValue == 1.00) {  // Do we need to send a notification?
                return 0;
            }
        }
    }
    return -1;
}

float SwitchSensor::readValue() {
    float average;
    average = 0;
    int valuesCount = 0;
    for (int i = 0; i < samplesTotal; i++) {
        if (samples[i] >= 0.00) {
            valuesCount++;
            average += samples[i];
        }
    }
    if (valuesCount > 0) {
        average = (float)average / (float)valuesCount;
    }
    return average;
}