#define BLYNK_TEMPLATE_ID "TMPL30i1ewUh6"
#define BLYNK_TEMPLATE_NAME "temp11"
#define BLYNK_AUTH_TOKEN "ll8f65v-Fs5LiKBisYurcFRybuwdWnLg"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "Display.h"  

char ssid[] = "chosphel";
char pass[] = "chopel123";

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
  delayHere(1000);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delayHere(300);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected!");
    showMessage("WiFi Status:", "Connected");
    delayHere(1000);
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
    int attempts = 0;
    while (!Blynk.connected() && attempts < 20) {
      Blynk.connect();  // Try connecting to Blynk cloud
      Serial.print(".");
      delayHere(500);
      attempts++;
    }

    if (Blynk.connected()) {
      Serial.println("\nBlynk connected!");
      showMessage("Blynk Status:", "Connected");
    } else {
      Serial.println("\nBlynk connection failed.");
      showMessage("Blynk Status:", "Failed");
    }
    delayHere(1000);
  }
}
