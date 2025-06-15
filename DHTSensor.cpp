#include "DHTSensor.h"
#include <DHT.h>



DHT dht(DHTPIN, DHTTYPE);  //object

void setupDHT() {
  dht.begin();
}

float getTemperature() {
  return dht.readTemperature();
}

float getHumidity() {
  return dht.readHumidity();
}