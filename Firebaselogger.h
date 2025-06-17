#ifndef FIREBASE_LOGGER_H
#define FIREBASE_LOGGER_H

#include <Firebase_ESP_Client.h>
#include "SensorData.h"     
// #include "Credentials.h"

//Firebase handles
extern FirebaseData fbdo;
extern FirebaseAuth auth;
extern FirebaseConfig config;

void setupFirebase();
void logSensorData(const SensorData &data);
String getTimestamp();     

#endif
