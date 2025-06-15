#ifndef PHSENSOR_H
#define PHSENSOR_H

#define PHPIN 34   //ADC1 pins(GPIOs 32-39) required as they can be used when wifi is active

extern const float ADC_RESOLUTION;
extern const float VREF;
extern const float PH_SLOPE;
extern const float PH_OFFSET;

void setupPH();
int getPHRaw();
float getPHValue();

#endif
