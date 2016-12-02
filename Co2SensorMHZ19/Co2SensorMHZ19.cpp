#include <Co2SensorMHZ19.h>
// #include <Math.h>
#include <SoftwareSerial.h>
#include <Arduino.h>

using namespace std;

Co2SensorMHZ19::Co2SensorMHZ19(uint8_t sensorRxPin, uint8_t sensorTxPin, int samplesCount, bool debugSetting) : co2Serial(SoftwareSerial(sensorRxPin, sensorTxPin, false, 256)) {
    debug = debugSetting;
    sampleIndex = 0;
    lastSample = 0;
    samplesTotal = samplesCount;
    samples = new float[samplesCount];
    rxPin = sensorRxPin;
    txPin = sensorTxPin;
}

bool Co2SensorMHZ19::begin() {
    co2Serial.begin(9600); //Init sensor MH-Z19
}

float Co2SensorMHZ19::sampleValue() {
    long now = millis();
    // Don't sample more often than every 200 millisecond.
    if (now - lastSample > 200) {
        lastSample = now;
        // Read co2 data
        byte cmd[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79}; // command to ask for data
        unsigned char response[9]; // for answer
        unsigned int ppm;
        // Send command
        co2Serial.write(cmd, 9);
        memset(response, 0, 9);
        co2Serial.readBytes(response, 9);
        int i;
        byte crc = 0;
        for (i = 1; i < 8; i++) {
            crc += response[i];
        }
        crc = 255 - crc;
        crc++;

        if (!(response[0] == 0xFF && response[1] == 0x86 && response[8] == crc)) {
            // Serial.println("CRC error: " + String(crc) + " / "+ String(response[8] ));
            co2Serial.flush();
            return -1;
        } else {
            unsigned int responseHigh = (unsigned int) response[2];
            unsigned int responseLow = (unsigned int) response[3];
            ppm = (256 * responseHigh) + responseLow;
        }
        // /Read co2 data

        samples[sampleIndex] = ppm;
        sampleIndex++;
        if (sampleIndex >= samplesTotal) {
            sampleIndex = 0;
        }
        return samples[sampleIndex];
    }
}

float Co2SensorMHZ19::readValue() {
    float average;
    average = 0;
    int valuesCount = 0;
    for (int i = 0; i < samplesTotal; i++) {
        if (samples[i] > 0.00) {
            valuesCount++;
            average += samples[i];
        }
    }
    average = (float)average / (float)valuesCount;
    return average;
}
