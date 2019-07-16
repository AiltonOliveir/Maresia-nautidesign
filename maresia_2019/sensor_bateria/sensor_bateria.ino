// Rx Nrf24l01 PA
//Display Oled 128x64 12c SSD1306
 
#include <U8glib.h>
#include <SPI.h> //INCLUSÃO DE BIBLIOTECA
#include <nRF24L01.h> //INCLUSÃO DE BIBLIOTECA
#include <RF24.h> //INCLUSÃO DE BIBLIOTECA


U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);  // Display which does not send AC
 
void draw() 
{
  //Comandos graficos para o display devem ser colocados aqui
  //Seleciona a fonte de texto
  u8g.setFont(u8g_font_8x13B);
  //Linha superior - temperatura 
  u8g.drawStr( 5, 15, "23");
  u8g.drawCircle(28,8,3);
  u8g.drawStr( 34, 15, "C");
  //Hora
  u8g.setFont(u8g_font_fub30);
  u8g.drawStr( 10, 57, "09:35");
  //Texto - AM
  u8g.setFont(u8g_font_5x7);
  u8g.drawStr( 115, 33, "AM");
  //moldura relogio
  u8g.drawRFrame(0,18, 128, 46, 4);
  //Desenho bateria
  u8g.drawRFrame(105, 3, 20,12 , 0);
  u8g.drawBox(125, 6, 2,6);
  u8g.drawBox(107, 5, 4,8);
  u8g.drawBox(114, 5, 4,8);
  //Desenho linhas sinal
  u8g.drawVLine(99,0, 15);
  u8g.drawVLine(98,0, 15);
  u8g.drawVLine(96,4, 11);
  u8g.drawVLine(95,4, 11);
  u8g.drawVLine(93,8, 7);
  u8g.drawVLine(92,8, 7);
  u8g.drawVLine(90,12, 3);
  u8g.drawVLine(89,12, 3);
}

RF24 radio(5, 6); //CRIA UMA INSTÂNCIA UTILIZANDO OS PINOS (CE, CSN)

const byte address[6] = "00666"; //CRIA UM ENDEREÇO PARA ENVIO DOS
//DADOS (O TRANSMISSOR E O RECEPTOR DEVEM SER CONFIGURADOS COM O MESMO ENDEREÇO)
int tensao = 0 ;

void setup() {
  Serial.begin(9600); //INICIALIZA A SERIAL
  radio.begin(); //INICIALIZA A COMUNICAÇÃO SEM FIO
  radio.openReadingPipe(0, address); //DEFINE O ENDEREÇO PARA RECEBIMENTO DE DADOS VINDOS DO TRANSMISSOR
  radio.setPALevel(RF24_PA_HIGH); //DEFINE O NÍVEL DO AMPLIFICADOR DE POTÊNCIA
  radio.startListening(); //DEFINE O MÓDULO COMO RECEPTOR (NÃO ENVIA DADOS)


  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
}



void loop() {
  u8g.firstPage();  
  do
  {
    draw();
  } while( u8g.nextPage() );
   
  delay(50);
  
  if (radio.available()) { //SE A COMUNICAÇÃO ESTIVER HABILITADA
    radio.read(&tensao, sizeof(int)); //LÊ OS DADOS RECEBIDOS
    Serial.println(tensao); //IMPRIME NA SERIAL OS DADOS RECEBIDOS
  }
}
