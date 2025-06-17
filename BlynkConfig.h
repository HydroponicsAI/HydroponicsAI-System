#ifndef BLYNKCONFIG_H
#define BLYNKCONFIG_H

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "Credentials.h"  

#define BLYNK_TEMPLATE_ID    BYK_TEMPLATE_ID
#define BLYNK_TEMPLATE_NAME  BYK_TEMPLATE_NAME
#define BLYNK_AUTH_TOKEN     BYK_AUTH_TOKEN

const char* ssid = WIFI_SSID;
const char* pass = WIFI_PASSWORD;

// char ssid[] = WIFI_SSID;       
// char pass[] = WIFI_PASSWORD;   

#endif
