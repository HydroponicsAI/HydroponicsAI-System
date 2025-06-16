#ifndef FIREBASE_LOGGER_H
#define FIREBASE_LOGGER_H

#include <FirebaseESP32.h> 
#include "SensorData.h"     

//Firebase handles
extern FirebaseData fbdo;
extern FirebaseAuth auth;
extern FirebaseConfig config;

void setupFirebase();
void logSensorData(const SensorData &data);
String getTimestamp();     

#endif
