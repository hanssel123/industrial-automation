#include <IRremote.h>

const int RECV_PIN = 11;  // Pin donde está conectado el receptor IR
String numero;

void setup() {
  Serial.begin(9600);      // Iniciar comunicación serial a 9600 baudios
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);  // Iniciar el receptor IR
}

void loop() {
  // int numero = -1; 
  if (IrReceiver.decode()) {  // Si se recibe una señal IR
    // Serial.print("Código recibido: ");
    String datoRecibido = String(IrReceiver.decodedIRData.decodedRawData);
    Serial.println(datoRecibido);  // Imprimir el código en formato hexadecimal
    if (datoRecibido.equals("3910598400")) {
      numero = "0";
    } else if (datoRecibido.equals("4077715200")) {
      numero = "1";
    } else if (datoRecibido.equals("3877175040")) {
      numero = "2";
    } else if (datoRecibido.equals("2707357440")) {
      numero = "3";
    } else if (datoRecibido.equals("4144561920")) {
      numero = "4";
    } else if (datoRecibido.equals("3810328320")) {
      numero = "5";
    } else if (datoRecibido.equals("2774204160")) {
      numero = "6";
    } else if (datoRecibido.equals("3175284480")) {
      numero = "7";
    } else if (datoRecibido.equals("2907897600")) {
      numero = "8";
    } else if (datoRecibido.equals("3041591040")) {
      numero = "9";
    } else if (datoRecibido.equals("4161273600")) {
      numero = "-";  // -
    } else if (datoRecibido.equals("3927310080")) {
      numero = "+";  // +
    }
  
    else {
      numero = "-1";  // Si no se reconoce el código, asignar -1
    }
    Serial.print("Número reconocido: ");
    Serial.println(numero);
    IrReceiver.resume();  // Preparar el receptor para el próximo valor
  }
}


