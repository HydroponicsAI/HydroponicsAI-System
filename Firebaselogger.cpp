#include "FirebaseLogger.h"
#include <Firebase_ESP_Client.h>
#include <WiFi.h>
#include <time.h>

Firebase_ESP_Client firebaseClient;
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Setup NTP for IST (GMT+5:30)
// Setup NTP for IST (GMT+5:30) with multiple servers for redundancy
void setupNTP() {
  configTime(19800, 0, "pool.ntp.org", "time.nist.gov", "time.google.com");

  struct tm timeinfo;
  int retries = 0;
  const int maxRetries = 30;
  Serial.print("Waiting for NTP sync...");
  while (!getLocalTime(&timeinfo) && retries < maxRetries) {
    Serial.print(".");
    delay(200);
    retries++;
  }

  if (retries < maxRetries) {
    Serial.println("NTP time sync successful.");
  } else {
    Serial.println("NTP time sync failed.");
  }
}

// Return formatted timestamp
String getTimestamp() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return "NTP FAIL";
  }
  char timeString[25];
  strftime(timeString, sizeof(timeString), "%d-%m-%Y %H:%M:%S", &timeinfo);
  return String(timeString);
}

// Initialize Firebase and auth
void setupFirebase() {
  Serial.println("Initializing Firebase...");

  config.api_key = FIREBASE_API_KEY;
  config.database_url = FIREBASE_DATABASE_URL;
  auth.user.email = FIREBASE_USER_EMAIL;
  auth.user.password = FIREBASE_USER_PASSWORD;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  setupNTP();  // Ensure time sync for timestamps
}

// Log sensor data to Firebase
void logSensorData(const SensorData &data) {
  if (!data.valid) {
    Serial.println("Invalid sensor data. Skipping log.");
    return;
  }

  if (!Firebase.ready()) {
    Serial.println("Firebase not ready. Skipping log.");
    return;
  }

  FirebaseJson json;
  json.set("temperature", data.temperature);
  json.set("humidity", data.humidity);
  json.set("ph", data.ph);
  json.set("moisture", data.moisture);
  json.set("moistureStatus", data.moistureStatus);
  json.set("timestamp", getTimestamp());
  json.set("nitrogen", data.nitrogen);
  json.set("potassium", data.potassium);
  json.set("phosphorous", data.phosphorous);

  String timestampKey = String(time(nullptr));  // Unix timestamp

  String logPath = "/hydroponics/logs/" + timestampKey;
  if (firebaseClient.RTDB.setJSON(&fbdo, logPath.c_str(), &json)) {
    Serial.println("Firebase: Data sent to 'logs' SUCCESSFULLY");
  } else {
    Serial.print("Firebase Error (logs): ");
    Serial.println(fbdo.errorReason());
  }

  String latestPath = "/hydroponics/latest";
  if (firebaseClient.RTDB.setJSON(&fbdo, latestPath.c_str(), &json)) {
    Serial.println("Firebase: Data sent to 'latest' SUCCESSFULLY");
  } else {
    Serial.print("Firebase error (latest): ");
    Serial.println(fbdo.errorReason());
  }
}
