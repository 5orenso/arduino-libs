#include <Arduino.h>
#include <GenericAnalogSensor.h>

#define PUBLISH_INTERVAL 15
#define LIGHT_SENSOR_PIN A0

GenericAnalogSensor light = GenericAnalogSensor(LIGHT_SENSOR_PIN, 20, false);
long lastRun = millis();

void setup(void) {
    Serial.begin(115200);
    light.begin();
}

void loop() {
    long now = millis();
    light.sampleValue();
    if (now - lastRun > (PUBLISH_INTERVAL * 1000)) {
        lastRun = now;

        float valueLight = light.readValue();
        Serial.println(valueLight);
    }
    delay(0);
}
