#include <SoftwareSerial.h>
SoftwareSerial HC12(3, 2); // HC-12 TX Pin, HC-12 RX Pin
float fator_correcao = (12.6/1023.0);
float valor, tensao;


void setup() {
  Serial.begin(9600); //INICIALIZA A SERIAL
  HC12.begin(9600);               // Serial port to HC12
 
void loop() {
  while (HC12.available()) {       // If HC-12 has data
      valor = HC12.read();
       if ( valor != -1.0){
       Serial.print(valor);      // Send the data to Serial monitor
       Serial.println("volts");
  }
}
