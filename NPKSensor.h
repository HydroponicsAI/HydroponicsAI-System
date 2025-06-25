#ifndef NPKSENSOR_H
#define NPKSENSOR_H

#include <Arduino.h>
#include <HardwareSerial.h>

struct NPKData {
  int nitrogen;
  int phosphorous;
  int potassium;
};

#define NPK_DE_PIN 4
#define NPK_RE_PIN 5

// RO(RX2), DI(TX2) pin on board
void setupNPKSensor(long baudRate = 9600, int rxPin = 16, int txPin = 17);
NPKData getNPK();

#endif
