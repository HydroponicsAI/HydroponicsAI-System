#include "NetworkSetup.h"
#include "SensorData.h"
#include "DHTSensor.h"
#include "Display.h"
#include "PHSensor.h"
#include "MoistureSensor.h"
#include "Firebaselogger.h"

BlynkTimer timer;

//This will print data to the sereial monitor
void printSensorData(const SensorData& data) {
  static unsigned long lastTimePrint = 0;
  const unsigned long printInterval = 5000;  // print every 5 seconds
  unsigned long now = millis();

  if (now - lastTimePrint >= printInterval) {
    Serial.printf("Temperature: %.2f °C | Humidity: %.2f %% | pH: %.2f | Moisture: %d%% - %s\n",
                  data.temperature, data.humidity, data.ph, data.moisture, data.moistureStatus.c_str());
    lastTimePrint = now;
  }
}


//This will update the values in the Blynk app
void updateBlynkData(const SensorData& data) {
  // Virtual pin assignment 
  // V0 = Temp, V1 = Humidity, V2 = pH, V3 = Moisture

  // Internal threshold constants
  static float lastTemperature = -100.0;
  static float lastHumidity = -100.0;
  static float lastPH = -100.0;
  static int lastMoisture = -1;

  const float TEMP_THRESHOLD = 2.0;
  const float HUMIDITY_THRESHOLD = 2.0;
  const float PH_THRESHOLD = 1;
  const int MOISTURE_THRESHOLD = 10;
  if (abs(data.temperature - lastTemperature) >= TEMP_THRESHOLD) {
    Blynk.virtualWrite(V0, data.temperature);
    lastTemperature = data.temperature;
  }

  if (abs(data.humidity - lastHumidity) >= HUMIDITY_THRESHOLD) {
    Blynk.virtualWrite(V1, data.humidity);
    lastHumidity = data.humidity;
  }

  if (abs(data.ph - lastPH) >= PH_THRESHOLD) {
    Blynk.virtualWrite(V2, data.ph);
    lastPH = data.ph;
  }

  if (abs(data.moisture - lastMoisture) >= MOISTURE_THRESHOLD) {
    Blynk.virtualWrite(V3, data.moisture);
    lastMoisture = data.moisture;
  }
}
//Function to send sensor values to Blynk as well as Firebase
void sendSensorData() {
  SensorData data = getAllSensorData();
  if (!data.valid) {
    Serial.println("Error in gathering Sensor Data!");
    showMessage("Sensor Error", data.errorMsg);  //Message to display on the LCD
    delayHere(1000);
    return;
  }
  updateBlynkData(data);  //this will send data to blynk app
  displayReadings(data);  // Display on LCD
  logSensorData(data);    //Function to send data to the firebase
}
void printExecuted(const String& function_name) {
  Serial.println(function_name + " executed successfully.");
}
void setup() {
  Serial.begin(115200);
  printExecuted("Serial Monitor");

  setupDisplay();
  printExecuted("[setupDisplay()], Display setup");

  showMessage("Hydroponics", "System Booting...");
  delay(1000);

  connectToWiFi();        // Connet to Wifi
  printExecuted("[connectToWifi()], WiFi");

  setupBlynk();           // Connect to Blynk server
  printExecuted("[setupBlynk()], Blynk");

  setupDHT();             // Initialize DHT sensor
  printExecuted("[setupDHT()], DHT");

  setupPH();              // Initialize pH sensor
  printExecuted("[setupPH()], PH");

  setupMoistureSensor();  // Initialize moisture sensor
  printExecuted("[setupMoistureSensor()], Moisture");

  setupFirebase();
  printExecuted("[setupFirebase()], Firebase");

  showMessage("Hydroponics", "System Ready");

  timer.setInterval(10000L, sendSensorData);  // Call sendSensorData every 10 seconds
  printExecuted("[timer.setInterval], sendSensorData");
}


void loop() {
  if (Blynk.connected()) {
    Blynk.run();  // Only if Blynk is alive
  }
  timer.run();  //Handle timed functions like sendSensorData()
}
