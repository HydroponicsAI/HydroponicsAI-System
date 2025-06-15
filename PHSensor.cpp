#include "PHSensor.h"
#include <Arduino.h>

const float ADC_RESOLUTION = 4095.0;
const float VREF = 3.3;
const float PH_SLOPE = -5.7;
const float PH_OFFSET = 21.34;

void setupPH() {
  pinMode(PHPIN, INPUT);
}

int getPHRaw() {
  return analogRead(PHPIN);
}

float getPHValue() {
  int raw = getPHRaw();
  float voltage = (raw / ADC_RESOLUTION) * VREF;
  float pH = PH_SLOPE * voltage + PH_OFFSET;
  return pH;
}
