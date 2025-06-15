#include "BlynkConfig.h"
#include "SensorData.h"
#include "DHTSensor.h"
#include "Display.h"
#include "PHSensor.h"
#include "MoistureSensor.h"

BlynkTimer timer;

//Previous sensor readings for comparison
float lastTemperature = -100.0;
float lastHumidity = -100.0;
float lastPH = -100.0;
int lastMoisture = -1;

const float TEMP_THRESHOLD = 0.5;
const float HUMIDITY_THRESHOLD = 2.0;
const float PH_THRESHOLD = 0.1;
const int MOISTURE_THRESHOLD = 10;

//Function to send sensor values to Blynk(Only if there is a significant change)
void sendSensorData() {
  SensorData data = getAllSensorData();
  if (!data.valid) {
    Serial.println("Error in gathering Sensor Data!");
    showMessage("Sensor Error", data.errorMsg);  //Message to display on the LCD
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(data.temperature);
  Serial.print(" °C | Humidity: ");
  Serial.print(data.humidity);
  Serial.print(" % | pH: ");
  Serial.println(data.ph);
  Serial.print("Moisture: ");
  Serial.print(data.moisture);
  Serial.print("% - ");
  Serial.println(data.moistureStatus);

  //Update Blynk only if there are significant changes
  if (abs(data.temperature - lastTemperature) >= TEMP_THRESHOLD) {
    Blynk.virtualWrite(V0, data.temperature);//write to the V0 virtual pin
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

  displayReadings(data.ph, data.temperature, data.humidity, data.moisture, data.moistureStatus);  // Display on LCD
}

void setup() {
  Serial.begin(115200);
  setupDHT();                                    //Initialize DHT sensor
  setupPH();                                     //Initialize pH sensor
  setupMoistureSensor();                         //Initialize Moisture sensor
  setupDisplay();                                //Initialize display
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);     //Connect to Blynk server
  showMessage("HydroponicsAI", "System Ready");  //First message to display on LCD Display
  timer.setInterval(10000L, sendSensorData);     //Call sendSensorData every 10 seconds(to not overwhelm Blynk and keep the traffic in control)
}

void loop() {
  Blynk.run();  //Run Blynk background tasks
  timer.run();  //Handle timed functions like sendSensorData()
}
