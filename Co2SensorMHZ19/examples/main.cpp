#include <Arduino.h>
#include <Co2SensorMHZ19.h>

#define PUBLISH_INTERVAL 15
#define CO2_MH_Z19_RX D7
#define CO2_MH_Z19_TX D8

Co2SensorMHZ19 co2 = Co2SensorMHZ19(CO2_MH_Z19_RX, CO2_MH_Z19_TX, 20, false);
long lastRun = millis();

void setup(void) {
    Serial.begin(115200);
    co2.begin();
}

void loop() {
    long now = millis();
    co2.sampleValue();
    if (now - lastRun > (PUBLISH_INTERVAL * 1000)) {
        lastRun = now;

        float valueCo2 = co2.readValue();
        Serial.println(valueCo2);
    }
    delay(0);
}