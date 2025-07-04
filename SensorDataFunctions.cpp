#include "SensorData.h"
#include "DHTSensor.h"
#include "PHSensor.h"
#include "MoistureSensor.h"
#include "NPKSensor.h"

SensorData getAllSensorData() {
  SensorData data; // object
  data.valid = true;
  data.errorMsg = "";

  data.temperature = getTemperature();
  data.humidity = getHumidity();
  data.ph = getPHValue();
  data.moisture = getMoisture();
  data.moistureStatus = classifyMoisture(data.moisture);
  NPKData npk = getNPK();

  data.nitrogen = npk.nitrogen;
  data.phosphorous = npk.phosphorous;
  data.potassium =  npk.potassium;

  if (isnan(data.temperature)) {
    Serial.println("Failed to read temperature from DHT sensor!");
    data.valid = false;
    data.errorMsg += "Tmp ";//Error message that is to be print on LCD screen 
  }
  if (isnan(data.humidity) || data.humidity < 0) {
    Serial.println("Failed to read humidity from DHT sensor!");
    data.valid = false;
    data.errorMsg += "Hum ";
  }
  if (isnan(data.ph)) {
    Serial.println("Failed to read from the pH sensor!");
    data.valid = false;
    data.errorMsg += "pH ";
  }
  if (data.ph > 14 || data.ph < 0||isnan(data.ph)) {
    Serial.println("pH out of Bounds: " + String(data.ph, 2));
    data.valid = false;
    data.errorMsg += "pH-OOB ";//OOB stands for out of bounds
  }
  if (data.moisture < 0 || data.moisture > 100||isnan(data.moisture)) {
    Serial.println("Failed to read from the moisture sensor!");
    data.valid = false;
    data.errorMsg += "Moi ";
  }

  if(isnan(data.potassium)||isnan(data.phosphorous)||isnan(data.nitrogen))
  {
    Serial.println("Faild to red from npk sensor!");
    data.valid = false;
    data.errorMsg += "npk";
  }
  if(data.potassium < 0 || data.phosphorous < 0 || data.nitrogen < 0)
  {
    Serial.println("Value OOB for npk!");
    data.valid = false;
    data.errorMsg += "npk OOB";
  }

  return data;
}
