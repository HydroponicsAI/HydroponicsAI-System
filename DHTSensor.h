#ifndef DHTSENSOR_H
#define DHTSENSOR_H

#define DHTPIN 13  //connect to pin 13 on esp32
#define DHTTYPE DHT11

void setupDHT();
float getTemperature();
float getHumidity();

#endif
