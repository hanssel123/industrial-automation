#include "voltage.h"
#include <HardwareSerial.h>

const int RX_PIN = 16;
const int TX_PIN = 17;

HardwareSerial mySerial(2);
float getVoltage(){
    uint8_t highByte = mySerial.read();
    uint8_t lowByte = mySerial.read();
    float voltage = (highByte << 8 | lowByte) * 0.1;

    highByte = mySerial.read();
    lowByte = mySerial.read();
    float corriente = (highByte << 8 | lowByte) * 0.001;

    delay(1);
    return voltage;
}