#include <Arduino.h>
#include <PirSensor.h>

#define PUBLISH_INTERVAL 15
#define MOTION_SENSOR_PIN D5

PirSensor motion = PirSensor(MOTION_SENSOR_PIN, 2, false, false);
long lastRun = millis();

void setup(void) {
    Serial.begin(115200);
    motion.begin();
}

void loop() {
    long now = millis();
    if (MOTION_SENSOR) {
        int motionStateChange = motion.sampleValue();
        if (motionStateChange >= 0) {
            Serial.println(motionStateChange);
        }
    }
    if (now - lastRun > (PUBLISH_INTERVAL * 1000)) {
        lastRun = now;
    }
    delay(0);
}
