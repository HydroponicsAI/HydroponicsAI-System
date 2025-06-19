#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <Arduino.h>

struct SensorData {
  float temperature;
  float humidity;
  float ph;
  int moisture;
  String moistureStatus;
  int nitrogen;//npk values
  int phosphorous;//npk values
  int potassium;//npk vlues
  bool valid;
  String errorMsg;
};

SensorData getAllSensorData(); //function to fetch all the data from different sensors 

#endif 
