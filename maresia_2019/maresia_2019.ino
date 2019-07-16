// --- Mapeamento de Hardware ---
// arduino uno ou nano
//Ponte H Bts7960
//modulo de sensoriamento Nrf24l01 PA

#include <SPI.h> //INCLUSÃO DE BIBLIOTECA
#include <nRF24L01.h> //INCLUSÃO DE BIBLIOTECA
#include <RF24.h> //INCLUSÃO DE BIBLIOTECA

#define volt 2    // voltimetro no pino 2
#define ch3   3   // Canal 3 no pino 3
#define ch5   4   // Canal 5 no pino 4
#define r_en   7   // Right Enable 1 no pino 7
#define l_en   8   // Left Enable 2 no pino 8
#define r_pwm  9  // Right PWM  no pino 9
#define l_pwm  10 // Left PWM no pino 10



RF24 radio(5, 6); //CRIA UMA INSTÂNCIA UTILIZANDO OS PINOS (CE, CSN)
const byte address[6] = "00666";

void read_channels();      //Função para leitura das entradas dos canais
void test_channels();      //Função que mostra na tela os valores que o arduino recebe do controle remoto
void avante();
void reverso();
void sensoriamento();

//variáveis para os canais do rádio
int canal_03 = 0,canal_05 = 0;
int PWM=0;
int tensao = 0;

void setup()
{
  pinMode(ch3, INPUT); //Entrada para o canal 3 do rádio
  pinMode(ch5, INPUT); //Entrada para o canal 5 do rádio

  radio.begin(); //INICIALIZA A COMUNICAÇÃO SEM FIO
  radio.openWritingPipe(address); //DEFINE O ENDEREÇO PARA ENVIO DE DADOS AO RECEPTOR
  radio.setPALevel(RF24_PA_HIGH); //DEFINE O NÍVEL DO AMPLIFICADOR DE POTÊNCIA
  radio.stopListening(); //DEFINE O MÓDULO COMO TRANSMISSOR (NÃO RECEBE DADOS)

 //controlarão o PWM
  pinMode(r_pwm, OUTPUT);
  pinMode(l_pwm, OUTPUT);

  digitalWrite(r_pwm,LOW);
  digitalWrite(l_pwm,LOW);
  
 // pinos responsáveis por habilitar e desabilitar o PWM (usados na hora de ligar e desligar o controle remoto)
  pinMode(r_en, OUTPUT);
  pinMode(l_en, OUTPUT);

  digitalWrite(r_en,LOW);
  digitalWrite(l_en,LOW);
 
  Serial.begin(9600);            //Inicia comunicação Serial com 9600 de baud rate

} //end setup

void loop()
{ 
      sensoriamento();
      digitalWrite(r_en,HIGH);
      digitalWrite(l_en,HIGH);      
      read_channels();
      // test_channels();
       
while(canal_05<1500) // enquanto a chave estiver para baixo
{
     avante();
     read_channels();
     delay(5);
}
      reverso();
      delay(5);

} //end loop

void read_channels()
{
  canal_03 = pulseIn(ch3, HIGH, 25000); //Lê pulso em nível alto do canal 3 e armazena na variável canal_03
  canal_03 = constrain(canal_03,1000,2000);
  delay(5);

  canal_05 = pulseIn(ch5, HIGH, 25000); //Lê pulso em nível alto do canal 5 e armazena na variável canal_05
  canal_05 = constrain(canal_05,965,1930);
  delay(5);
  
   if(canal_03==0 || canal_03<=990) //condiçoes para o motor ficar totalmente desligado 
  {
  analogWrite(r_pwm,PWM*0);
  analogWrite(l_pwm,PWM*0);
  digitalWrite(l_en,LOW);
  digitalWrite(r_en,LOW);
  }

  if(canal_03<1150 && canal_05>750)
  {
  analogWrite(r_pwm,PWM*0);
  analogWrite(l_pwm,PWM*0);
  digitalWrite(l_en,LOW);
  digitalWrite(r_en,LOW);
  }
    
} //end read channels
void sensoriamento(){
  tensao = analogRead(volt)*(12/1023);
  radio.write(&tensao, sizeof(int)); //ENVIA AO RECEPTOR A MENSAGEM
  delay(5);
}
void avante()
{
      PWM=map(canal_03,1000,2000,0,255);
      analogWrite(r_pwm,PWM);
}

void reverso()
{
      PWM=map(canal_03,1000,2000,0,255);
      analogWrite(l_pwm,PWM);
}

void test_channels() //Testa os canais via serial monitor (comentar esta função e só chamar quando necessário)
{

      Serial.print("Valor:  ");
      Serial.print(canal_03);
      Serial.print(" | ");
      Serial.print(canal_05);
      Serial.print(" | ");
      Serial.print("Último PWM:");
      Serial.println(PWM);


} //end test_channels
