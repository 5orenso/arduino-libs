#include <PirSensor.h>
#include <Math.h>
#include <Arduino.h>

using namespace std;

PirSensor::PirSensor(uint8_t sensorPin, int samplesCount, bool debugSetting, bool verboseSetting) {
    debug = debugSetting;
    verbose = verboseSetting;
    sampleIndex = 0;
    lastSample = 0;
    samplesTotal = samplesCount;
    samples = new float[samplesCount];
    pin = sensorPin;
}

bool PirSensor::begin() {
    pinMode(pin, INPUT);
}

int PirSensor::sampleValue() {
    long now = millis();
    // Don't sample more often than every 50 millisecond.
    if (now - lastSample > 500) {
        lastSample = now;
        float lastValue = readValue();
        samples[sampleIndex] = digitalRead(pin);
        int currentValue = round(samples[sampleIndex]);
        // Increasing sampleIndex for next loop.
        sampleIndex++;
        if (sampleIndex >= samplesTotal) {
            sampleIndex = 0;
        }
        if (currentValue == 1) {      // Motion detected
            if (lastValue == 0.00) {  // Do we need to send a notification?
                return true;
            }
        } else {                      // End motion detected
            if (lastValue == 1.00) {  // Do we need to send a notification?
                return false;
            }
        }
    }
    return -1;
}

float PirSensor::readValue() {
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