#ifndef BLYNKCONFIG_H
#define BLYNKCONFIG_H

#include "Credentials.h"

#define BLYNK_TEMPLATE_ID TEMPLATE_ID
#define BLYNK_TEMPLATE_NAME TEMPLATE_NAME
#define BLYNK_AUTH_TOKEN AUTH_TOKEN

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = WIFI_SSID;
char pass[] = WIFI_PASSWORD;

#endif
