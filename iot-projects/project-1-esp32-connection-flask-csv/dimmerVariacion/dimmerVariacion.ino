#include "IRremote.h"              // Incluir Libería IR.
#include <TimerOne.h>              // Incluir Librería TimerOne
int receptor = 11;                 // Pin para ingreo de la señal de módulo IR              
IRrecv irrecv(receptor);           // Crea un nuevo objeto receptor que decodifique señales a códigos clave.
decode_results resultado;          // Una variable en donde se almacenan los códigos.  
         
volatile int i=0;                  // Variable usada por el contador.
volatile boolean cruce_cero=0;     // variable que actúa como switch al detectar cruce por cero.
int Triac = 3;                     // Salida conectada al optoacoplador MOC 3021.
int dim = 83;                      // Controla la intensidad de iluminación, 0 = ON ; 83 = OFF                
int T_int = 100;                   // Tiempo en el cual se producen la interrupciones en us. 

void setup() {   
  
  irrecv.enableIRIn();                                  // Inicia el receptor.
  pinMode(Triac, OUTPUT);                               // Configurar como salida.
  attachInterrupt(0, deteccion_Cruce_cero, RISING);    // Realiza una interrupción al detectar el crice por cero en el pin 2
  Timer1.initialize(T_int);                            //Inicializa la librería con el tiempo deseado.
  Timer1.attachInterrupt(Dimer, T_int);                // En cada interrupción ejecuta el codigo Dimer. 
}

void deteccion_Cruce_cero() 
{                                                      // Si existe un cruce por cero entonces la variable "cruce_cero" cambia a TRUE...
  cruce_cero = true;                                   //...reseteando el valor de "i", y colocando la salida conectada al Triac en estado...
  i=0;                                                 // ...bajo.
  digitalWrite(Triac, LOW);
}                                 

void Dimer() 
{                   
  if(cruce_cero == true) {                             // Al detectarse el cruce por cero inicia a correr un tiempo t = T_int*dim, en el cual...
    if(i>=dim) {                                       // ... el triac se dispara y empieza a conducir.
      digitalWrite(Triac, HIGH);                      
      i=0;                                              // Reseteo i.
      cruce_cero=false;                                   
    } 
    else {
      i++;                     
}}}                                      

void receptorIR() 

{
  switch(resultado.value)                             // usamos la variable "resultado.value" 
  {
  case 0x00FF4AB5:                                    // Código obtenido al presionar la teclar "arrriba"
    {
    if (dim<83)                                       // Si el valor de "dim" es menor al 83, entonces sumar 5 al valor de la variable "dim"...
   {                                                  //...si esque el valor de "dim" es mayor a 83, entonces se asigna 83 al valor "dim" como...  
    dim = dim + 5;                                    //... constante, lo que permite que la variable "dim" no supere el valor de 83.
    if (dim>83) 
    {
      dim=83; 
    }}}
    break;

  case  0x00FF18E7:  
  {   
  if (dim>5)  
  {
     dim = dim - 5;
  if (dim<0) 
    {
      dim=0;  
    } }}
    break;
  }
}
  
void loop() {  
 if (irrecv.decode(&resultado))                         // Si se ha recibido una señal IR...
  {                 
    receptorIR();                                       // ...ejecutar el código de receptorIR
    irrecv.resume();                                    // receptar el siguiente valor
  }  
}
