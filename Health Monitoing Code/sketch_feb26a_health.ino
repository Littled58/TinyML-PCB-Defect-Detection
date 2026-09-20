/*#include <WiFi.h>
#include "esp_system.h"

int calculateHealth() {

  int health = 100;

  // -------- RAM HEALTH --------
  uint32_t freeHeap = ESP.getFreeHeap();
  if (freeHeap < 50000) health -= 20;
  else if (freeHeap < 100000) health -= 10;

  // -------- PSRAM HEALTH --------
  if (!psramFound()) {
    health -= 15;
  }

  // -------- WIFI HEALTH --------
  if (WiFi.status() == WL_CONNECTED) {
    int rssi = WiFi.RSSI();
    if (rssi < -80) health -= 15;
    else if (rssi < -60) health -= 5;
  } else {
    health -= 20;
  }

  // -------- CPU TEMP (ESP32-S3 internal sensor) --------
  float temp = temperatureRead();
  if (temp > 70) health -= 20;
  else if (temp > 60) health -= 10;

  // -------- UPTIME HEALTH --------
  uint32_t uptime = millis() / 1000;
  if (uptime < 10) health -= 5; // just started

  if (health < 0) health = 0;

  return health;
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("ESP32-S3 HEALTH MONITOR STARTED");
}

void loop() {

  int healthScore = calculateHealth();

  Serial.print("Health Score: ");
  Serial.print(healthScore);
  Serial.println(" / 100");

  Serial.print("Free Heap: ");
  Serial.println(ESP.getFreeHeap());

  Serial.print("CPU Temp: ");
  Serial.println(temperatureRead());

  Serial.println("--------------------");

  delay(3000);
}*/

/#include <Arduino.h>
#include <WiFi.h>
#include "esp_system.h"

// ===============================
// TinyML model
// ===============================

// Pretend-trained weights
float w_heap = 0.4;
float w_temp = -0.6;
float w_wifi = 0.5;
float bias = 0.2;



float relu(float x){
  if(x > 0) return x;
  return 0;
}

// TinyML prediction
int tinyml_predict(float heap, float temp, float wifi){

  float z = (heap*w_heap) + (temp*w_temp) + (wifi*w_wifi) + bias;
  float output = relu(z);

  if(output > 0.6) return 2;      // HEALTHY
  else if(output > 0.3) return 1; // WARNING
  else return 0;                  // CRITICAL
}

// ===============================
// Health Score Calculation
// ===============================
int calculateHealthScore(float heap, float temp, float wifi){

  // Convert normalized values into score parts
  int heapScore = heap * 40;
  int tempScore = (1.0 - temp) * 30;
  int wifiScore = wifi * 30;

  int health = heapScore + tempScore + wifiScore;

  // Clamp 0–100
  if(health > 100) health = 100;
  if(health < 0) health = 0;

  return health;
}

void setup() {

  Serial.begin(115200);
  Serial.println("TinyML Board Health Monitor Started");

}

void loop() {

  // ===============================
  // Feature Extraction
  // ===============================

  float cpuTemp = temperatureRead();   // REAL CPU TEMP

  float heapNorm = ESP.getFreeHeap() / 300000.0;
  if(heapNorm > 1) heapNorm = 1;

  float tempNorm = cpuTemp / 80.0;
  if(tempNorm > 1) tempNorm = 1;

  float wifiNorm = 0.5;
  if(WiFi.status() == WL_CONNECTED){
    wifiNorm = (WiFi.RSSI()+100)/60.0;
    if(wifiNorm > 1) wifiNorm = 1;
    if(wifiNorm < 0) wifiNorm = 0;
  }

  // ===============================
  // TinyML Prediction
  // ===============================

  int result = tinyml_predict(heapNorm,tempNorm,wifiNorm);

  // ===============================
  // Health Score
  // ===============================

  int healthScore = calculateHealthScore(heapNorm,tempNorm,wifiNorm);

  // ===============================
  // OUTPUT
  // ===============================

  Serial.println("===== ESP32 BOARD HEALTH =====");

  Serial.print("CPU Temperature: ");
  Serial.print(cpuTemp);
  Serial.println(" C");

  Serial.print("Health Score: ");
  Serial.print(healthScore);
  Serial.println(" / 100");

  Serial.print("TinyML Prediction: ");

  if(result == 2) Serial.println("HEALTHY");
  else if(result == 1) Serial.println("WARNING");
  else Serial.println("CRITICAL");

  Serial.println("------------------------------");

  delay(3000);
}/*