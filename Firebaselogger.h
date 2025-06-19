#ifndef FIREBASE_LOGGER_H
#define FIREBASE_LOGGER_H

#include <Firebase_ESP_Client.h>
#include "SensorData.h"     

#define FIREBASE_API_KEY "AIzaSyDjTgr81ChbVLjJ42q8_OIe8_I0fXzLf7Q"
#define FIREBASE_DATABASE_URL "https://hydroponicsai-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_USER_EMAIL "dorje.wm@gmail.com"
#define FIREBASE_USER_PASSWORD "Ladakh@123@NIELIT"
//Firebase handles
extern FirebaseData fbdo;
extern FirebaseAuth auth;
extern FirebaseConfig config;

void setupFirebase();
void logSensorData(const SensorData &data);
String getTimestamp();     

#endif
