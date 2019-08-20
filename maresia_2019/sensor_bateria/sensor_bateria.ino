#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
SoftwareSerial HC12(8, 9); // HC-12 TX Pin, HC-12 RX Pin

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
float tensao = 12.6;
float antena = 0;


void setup() {
  Serial.begin(9600);             
  HC12.begin(9600);               
  lcd.begin(16, 2);
  
}

void loop() {
  while (HC12.available()) {        
    if ( valor != -1.0){
    antena = HC12.read();          
    tensao = antena*(12.6/255.0);
    }}
  
   //Limpa a tela
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(0, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("Robotech-Maresia");
  lcd.setCursor(4, 1);
  lcd.print(tensao);
  lcd.setCursor(9, 1);
  lcd.print("V");
  delay(500);
    
  }
