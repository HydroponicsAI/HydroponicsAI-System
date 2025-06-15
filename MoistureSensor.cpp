#include "MoistureSensor.h"

void setupMoistureSensor() {
  pinMode(MOISTURE_PIN, INPUT);
}

// Function to read raw analog value and convert to percentage
int getMoisture() {
  int raw = analogRead(MOISTURE_PIN);        
  int moisture = map(raw, 0, 4095, 0, 100);  // Dry = 0 → 0%, Wet = 4095 → 100%
  return constrain(moisture, 0, 100);        // Ensure value is within 0–100
}

// Function to classify moisture level into categories
String classifyMoisture(int value) {
  if (value < 30) {
    return "LM"; // LM: Low Moisture
  } else if (value < 60) {
    return "MM"; // MM: Moderate Moisture
  } else if (value < 80) {
    return "HM"; // HM: High Moisture
  } else {
    return "EHM"; // EHM: Extremely High Moisture
  }
}
