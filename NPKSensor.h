#ifndef NPKSENSOR_H
#define NPKSENSOR_H

#include <Arduino.h>
#include <HardwareSerial.h>

// Structure for sensor readings
struct NPKData {
  int nitrogen;
  int phosphorous;
  int potassium;
};

// Pin config (for DE/RE on RS485 module)
#define NPK_DE_PIN 4
#define NPK_RE_PIN 5

// UART2 (Serial2) will be used
// RO(RX2), DI(TX2) 
void setupNPKSensor(long baudRate = 9600, int rxPin = 16, int txPin = 17);
NPKData getNPK();

#endif
