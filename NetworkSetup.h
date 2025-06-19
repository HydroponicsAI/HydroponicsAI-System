#define BLYNK_TEMPLATE_ID "TMPL30i1ewUh6"
#define BLYNK_TEMPLATE_NAME "temp11"
#define BLYNK_AUTH_TOKEN "ll8f65v-Fs5LiKBisYurcFRybuwdWnLg"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "Display.h"  // Custom LCD wrapper

char ssid[] = "Galaxy";
char pass[] = "wangmo1999";

// Non-blocking delay function
void delayHere(unsigned long totalTime) {
  unsigned long startTime = millis();
  while (millis() - startTime < totalTime) {
    Blynk.run();
    yield();
  }
}

void connectToWiFi() {
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi");
  showMessage("WiFi Status:", "Connecting...");

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 1000) {
    delayHere(300);  
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected!");
    showMessage("WiFi Status:", "Connected");
    delayHere(500);
  } else {
    Serial.print("\nWiFi connection failed. Total attempts: ");
    Serial.println(attempts);
    showMessage("WiFi Status:", "Failed");
    delayHere(1000);
  }
}

void setupBlynk() {
  Serial.println("Connecting to Blynk....");
  showMessage("Blynk Status:", "Connecting...");
  delayHere(1000);

  if (WiFi.status() == WL_CONNECTED) {
    Blynk.config(BLYNK_AUTH_TOKEN);

    if (Blynk.connect(2000)) {
      Serial.println("Blynk connected!");
      showMessage("Blynk Status:", "Connected");
      delayHere(1000);
    } else {
      Serial.println("Blynk connection failed.");
      showMessage("Blynk Status:", "Failed");
      delayHere(1000);
    }
  }
}
