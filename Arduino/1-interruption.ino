//1-interruption

#include <Wire.h> //wire==arame==fio //conecta dispositivos
#include <LiquidCrystal_I2C.h>  //I2C é a sigla de Inter-Integrated Circuit, e basicamente é um protocolo de comunicação entre dispositivos que “falam” I2C.

//O Arduino vem com pinos próprios para a conexão I2C, 
//no caso do Uno e derivados os pinos são sempre o 4 (SDA) e 5(SCL).
//SDA significa Serial Data e SCL significa Serial Clock. 
//SDA é o pino que efetivamente transfere os dados, e SCL serve para temporização entre os dispositivos, 
//de modo que a comunicação pela SDA possa ter confiabilidade. 
//Como podem observar, tanto o envio quanto a recepção de dados é realizada utilizando a linha SDA,
//ou seja, é uma linha bi-direcional de comunicação, 
//ora estamos enviando dados por este pino, ora estamos recebendo dados.

LiquidCrystal_I2C lcd(0x27, 2,1,0,4,5,6,7,3, POSITIVE);

#define switchA 3 //interrupcao só nos pinos 2 e 3
#define blueLed 10
#define whiteLed 9
#define redLed 11

void switchPressed();

void setup() {
  pinMode(blueLed, OUTPUT);
  pinMode(whiteLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(switchA, INPUT_PULLUP);

  lcd.begin(16,2);
  attachInterrupt(digitalPinToInterrupt(switchA), switchPressed, RISING);
}
unsigned long inicialM = 0;
int ledState= LOW;

void loop() {
  if((millis() - inicialM) >= 500){
     ledState = !ledState;
     inicialM = millis();
  }
  digitalWrite(blueLed, ledState); //digitalWrite só recebe 0 ou 1 (LOW ou HIGH);
  digitalWrite(whiteLed, !ledState); //Já o analogWrite recebe mais intensidades (de 0 a 255), com a condição de que o led esteja num pino PWM;

  //noInterrupts(); - desativa a interrupção
  //... - neste intervalo nao pode haver interrupção
  //interrupts(); - reativa a interrupção

  //detachInterrupt(digitalPinToInterrupt(switchA));//desanexa a interrupção
  //digitalPinToInterrupt é só uma função de tradução(traduz para 0 ou 1);
}

void switchPressed(){
  static bool state=LOW; //static faz o valor da variável não ser destruída, para a informação da var ser guardada
  static unsigned long inicialMillis=0;//vamos ver como ele é inicializado!  
  //lcd.setCursor(0,0);
  //lcd.print(inicialMillis); //não sei o porquê mas a interrupção não funciona com o lcds 
  if((millis()-inicialMillis)>100){
    state= !state;
    inicialMillis= millis();
  }
  digitalWrite(redLed, state);
}
