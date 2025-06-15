#ifndef MOISTURESENSOR_H
#define MOISTURESENSOR_H

#include <Arduino.h>

#define MOISTURE_PIN 32 // connect as pin 32 (ADC1 pin)

// Function declarations
void setupMoistureSensor();                      // Initialize pin
int getMoisture();                               // Read analog and convert to percentage
String classifyMoisture(int value);              // Convert percentage to category string

#endif
