#include <Arduino.h>
#include <WiFi.h>
#include <SD.h>
#include <SPI.h>
#include <HTTPClient.h>

// const char* ssid = "WLAN_Invitados";
// const char* password = "ud1str1tal";
const char* ssid = "hans";
const char* password = "Dani2024";
const char* serverName = "http://192.168.12.33:5000/upload";

int voltagePin = 34;
int currentPin = 32;
float voltage = 0.0;
float current = 0.0;

String logEntry = "Tiempo,Voltaje,Corriente,\n";

void sendDataToServer(String logEntry);

void setup() {
  Serial.begin(9600); // Initialize serial communication

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi :( :( :(");
  }
  Serial.println("Conectado a WiFi :) :) :) :)");
  logEntry = "Tiempo,Voltaje,Corriente,\n";
  sendDataToServer(logEntry);

}

void loop() {
  // float voltageValue = random(110, 113);
  // float currentValue = random(1, 3);

  int voltageValue = analogRead(voltagePin);
  int currentValue = analogRead(currentPin);

  voltage = (voltageValue * 3.3) / 4095;
  current = ((currentValue * 5.0) / 1023.0) - 2.5;

  Serial.print("Voltaje: ");
  Serial.print(voltageValue);
  Serial.print(" V, Corriente: ");
  Serial.print(currentValue);
  Serial.println(" A");

  // String logEntry = String(millis()) + "," + String(voltage) + "," + String(current) + "\n";
  logEntry = String(millis()) + "," + String(voltage) + "," + String(current) +  "," + String(voltageValue) + "," + String(currentValue) + "\n";
  Serial.println(logEntry);

  sendDataToServer(logEntry);
  
  delay(1000);  // Simula la generación de datos cada segundo

}


void sendDataToServer(String logEntry) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "text/plain");

    int httpResponseCode = http.POST(logEntry);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Respuesta del servidor: " + response);
    } else {
      Serial.println("Error en la conexión: " + String(httpResponseCode));
    }

    http.end();
  } else {
    Serial.println("WiFi no conectado");
  }
}