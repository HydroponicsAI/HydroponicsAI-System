#include "FirebaseLogger.h"
#include <WiFi.h>
#include <time.h>

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

//NTP Setup for Real-Time Timestamp (IST = GMT+5:30)
void setupNTP() {
  configTime(19800, 0, "pool.ntp.org");
}

String getTimestamp() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return "NTP FAIL";
  }
  char timeString[25];
  strftime(timeString, sizeof(timeString), "%d-%m-%Y %H:%M:%S", &timeinfo);
  return String(timeString);
}

void setupFirebase() {
  config.api_key = "XXXXXX_API_KEY";
  config.database_url = "https://xxxx.firebaseio.com/";
  auth.user.email = "xxxx@email.com";
  auth.user.password = "xxxx";

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  setupNTP();  //initialize time sync
}

void logSensorData(const SensorData &data) {
  if (!data.valid) return;

  FirebaseJson json;
  json.set("temperature", data.temperature);
  json.set("humidity", data.humidity);
  json.set("ph", data.ph);
  json.set("moisture", data.moisture);
  json.set("moistureStatus", data.moistureStatus);
  json.set("timestamp", getTimestamp());  
  json.set("unix", String(time(nullptr))); //mysql like aka unix timestamp

  String logPath = "/hydroponics/logs/" + String(time(nullptr));

  // Log historical entry
  if (Firebase.RTDB.setJSON(&fbdo, logPath.c_str(), &json)) {
    Serial.println("Firebase log (logs) success");
  } else {
    Serial.print("Firebase error (logs): ");
    Serial.println(fbdo.errorReason());
  }

  // Also update latest
  String latestPath = "/hydroponics/latest";
  if (Firebase.RTDB.setJSON(&fbdo, latestPath.c_str(), &json)) {
    Serial.println("Firebase log (latest) success");
  } else {
    Serial.print("Firebase error (latest): ");
    Serial.println(fbdo.errorReason());
  }
}
