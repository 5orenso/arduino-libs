#include <Arduino.h>
#include <SwitchSensor.h>

#define PUBLISH_INTERVAL 15
#define SWITCH_SENSOR_PIN D5

SwitchSensor mySwitch = SwitchSensor(SWITCH_SENSOR_PIN, 1, false, false);
long lastRun = millis();
long switchSensorStart;

void setup(void) {
    Serial.begin(115200);
    mySwitch.begin();
}

void loop() {
    long now = millis();
    int switchStateChange = mySwitch.sampleValue();
    if (switchStateChange >= 0) {
        Serial.print(" --> switchStateChange: "); Serial.println(switchStateChange);
        if (switchStateChange == 1) {
            switchSensorStart = millis();
        } else {
            long switchSessionLength = millis() - switchSensorStart;
            Serial.print(" --> switchSessionLength: "); Serial.println(switchSessionLength);
        }
    }

    if (now - lastRun > (PUBLISH_INTERVAL * 1000)) {
        lastRun = now;
    }
    delay(0);
}
