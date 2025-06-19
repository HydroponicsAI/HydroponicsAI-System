#include "NPKSensor.h"

// MODBUS commands
const byte N_CMD[8] = { 0x01, 0x03, 0x00, 0x1E, 0x00, 0x01, 0xE4, 0x0C };
const byte P_CMD[8] = { 0x01, 0x03, 0x00, 0x1F, 0x00, 0x01, 0xB5, 0xCC };
const byte K_CMD[8] = { 0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xC0 };

void setupNPKSensor(long baudRate, int rxPin, int txPin) {
  Serial2.begin(baudRate, SERIAL_8N1, rxPin, txPin);
  pinMode(NPK_DE_PIN, OUTPUT);
  pinMode(NPK_RE_PIN, OUTPUT);
  digitalWrite(NPK_DE_PIN, LOW);
  digitalWrite(NPK_RE_PIN, LOW);
}

void setTransmitMode() {
  digitalWrite(NPK_DE_PIN, HIGH);
  digitalWrite(NPK_RE_PIN, HIGH);
}

void setReceiveMode() {
  digitalWrite(NPK_DE_PIN, LOW);
  digitalWrite(NPK_RE_PIN, LOW);
}

int sendAndReadSensor(const byte* cmd) {
  byte values[11];
  setTransmitMode();
  delay(10);
  Serial2.write(cmd, 8);
  Serial2.flush();
  setReceiveMode();
  delay(200);

  byte i = 0;
  unsigned long start = millis();
  while (i < 7 && millis() - start < 300) {
    if (Serial2.available()) {
      values[i++] = Serial2.read();
    }
  }

  if (i < 5) return -1;  // Incomplete response
  return (values[3] << 8) | values[4];
}

NPKData getNPK() {
  NPKData data;
  data.nitrogen = sendAndReadSensor(N_CMD);
  data.phosphorous = sendAndReadSensor(P_CMD);
  data.potassium = sendAndReadSensor(K_CMD);
  return data;
}
