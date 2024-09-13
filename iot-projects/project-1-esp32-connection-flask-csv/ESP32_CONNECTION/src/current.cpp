#include "current.h"
#include <Arduino.h>

// Ajustes del sensor de corriente
#define CURRENT_SENSOR_PIN 34

const int mVperAmp = 100;
const float referenceVoltage = 3.3;
const int ADCresolution = 4096;
float zeroCurrentOffset = 1920;

unsigned long lastPeakPrint = 0;
const int sampleWindow = 5000;
const int smoothingWindow = 100;

float calculatePeakCurrent();
float smoothCurrent(float current);

// Implementación de la función getcurrent
float getcurrent() {
  // Comprobamos si han pasado 5 segundos para calcular la corriente pico
  if (millis() - lastPeakPrint >= 5000) {
    lastPeakPrint = millis();  // Actualizamos el tiempo de la próxima muestra

    // Calculamos y devolvemos la corriente RMS basada en el pico
    float peakCurrent = calculatePeakCurrent();
    float rmsCurrent = peakCurrent / sqrt(2.0);

    // Retornamos el valor ajustado de la corriente
    if (rmsCurrent <= 0.07) {
      return 0.0;
    } else {
      return rmsCurrent * 2.2;  // Devuelve la corriente en A
    }
  }

  // Si no ha pasado suficiente tiempo, retornamos 0
  return 0;
}

// Función para calcular la corriente pico en la ventana de muestreo
float calculatePeakCurrent() {
  unsigned long startMillis = millis();
  float maxCurrent = 0;

  while (millis() - startMillis < sampleWindow) {
    int sensorValue = analogRead(CURRENT_SENSOR_PIN);
    float voltage = sensorValue * (referenceVoltage / ADCresolution);
    float current = (voltage - (zeroCurrentOffset * referenceVoltage / ADCresolution)) / (mVperAmp / 1000.0);
    current = smoothCurrent(current);

    if (abs(current) > maxCurrent) {
      maxCurrent = abs(current);
    }

    delay(1);  // Pequeño delay para evitar sobrecarga del loop
  }

  return maxCurrent;
}

// Función para suavizar la corriente usando un promedio móvil
float smoothCurrent(float current) {
  static float readings[smoothingWindow];
  static int index = 0;
  static float total = 0;
  static bool filled = false;

  total -= readings[index];
  readings[index] = current;
  total += current;
  index = (index + 1) % smoothingWindow;

  if (!filled && index == 0) {
    filled = true;
  }

  return filled ? total / smoothingWindow : current;
}
