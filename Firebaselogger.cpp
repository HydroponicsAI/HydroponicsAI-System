#include <Firebase_ESP_Client.h>
#include <WiFi.h>
#include <time.h>

#include "FirebaseLogger.h"

Firebase_ESP_Client firebaseClient;
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// NTP Setup for Real-Time Timestamp (IST = GMT+5:30)
void setupNTP() {
  configTime(19800, 0, "pool.ntp.org");  // 19800 = GMT+5:30
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
  config.api_key = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
  config.database_url = "https://xxxxxxxxxxxxxxxxxxxxx.firebasedatabase.app/";
  auth.user.email = "XXXXXXXXXXXXXXXXXXXXXX";
  auth.user.password = "XXXXXXXXXXXXXXXX";

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  setupNTP();  // initialize time sync
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

  String timestampKey = String(time(nullptr));  // Unix time as key

  // Log historical entry
  String logPath = "/hydroponics/logs/" + timestampKey;
  if (firebaseClient.RTDB.setJSON(&fbdo, logPath.c_str(), &json)) {
    Serial.println("Firebase log (logs) success");
  } else {
    Serial.print("Firebase error (logs): ");
    Serial.println(fbdo.errorReason());
  }

  // Update latest
  String latestPath = "/hydroponics/latest";
  if (firebaseClient.RTDB.setJSON(&fbdo, latestPath.c_str(), &json)) {
    Serial.println("Firebase log (latest) success");
  } else {
    Serial.print("Firebase error (latest): ");
    Serial.println(fbdo.errorReason());
  }
}