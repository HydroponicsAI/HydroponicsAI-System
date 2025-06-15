#include "SensorData.h"
#include "DHTSensor.h"
#include "PHSensor.h"
#include "MoistureSensor.h"

SensorData getAllSensorData() {
  SensorData data; // object
  data.valid = true;
  data.errorMsg = "";

  data.temperature = getTemperature();
  data.humidity = getHumidity();
  data.ph = getPHValue();
  data.moisture = getMoisture();
  data.moistureStatus = classifyMoisture(data.moisture);

  if (isnan(data.temperature)) {
    Serial.println("Failed to read temperature from DHT sensor!");
    data.valid = false;
    data.errorMsg += "Tmp ";//Error message that is to be print on LCD screen 
  }
  if (isnan(data.humidity)) {
    Serial.println("Failed to read humidity from DHT sensor!");
    data.valid = false;
    data.errorMsg += "Hum ";
  }
  if (isnan(data.ph)) {
    Serial.println("Failed to read from the pH sensor!");
    data.valid = false;
    data.errorMsg += "pH ";
  }
  if (data.ph > 14 || data.ph < 0) {
    Serial.println("pH out of Bounds: " + String(data.ph, 2));
    data.valid = false;
    data.errorMsg += "pH-OOB ";//OOB stands for out of bounds
  }
  if (data.moisture < 0 || data.moisture > 100) {
    Serial.println("Failed to read from the moisture sensor!");
    data.valid = false;
    data.errorMsg += "Moi ";
  }

  return data;
}
