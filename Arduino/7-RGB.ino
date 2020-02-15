//4-LED_RGB

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2,1,0,4,5,6,7,3, POSITIVE);

#define red 6 //controle de brilho só PWM: 3,5,6,9,10,11
#define green 5
#define blue 3

#define buttonOrTilt 2 //interrupcao só pinos 2 e 3
void pushButton();
void setup() {
  lcd.begin(16,2);
  
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(buttonOrTilt, INPUT_PULLUP); //ativa a resistencia interna do Arduino;

  attachInterrupt(digitalPinToInterrupt(buttonOrTilt), pushButton, RISING);

  analogWrite(red, HIGH);
  analogWrite(green, LOW);
  analogWrite(blue, LOW);
}

int redV=255, greenV=0, blueV=0;
void loop() {
  if(redV==255){
    for(int i=1; i<=255; i++){
      redV--;
      greenV++;
      analogWrite(red, redV);
      analogWrite(green, greenV);
      delay(10);
    }
  }
  if(greenV==255){
    for(int i=1; i<=255; i++){
      greenV--;
      blueV++;
      analogWrite(red, redV);
      analogWrite(green, greenV);
      delay(10);
    }
  }
  if(blueV==255){
    for(int i=1; i<=255; i++){
      blueV--;
      redV++;
      analogWrite(red, redV);
      analogWrite(green, greenV);
      delay(10);
    }
  }
}
void pushButton(){
  int cont=0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("oi");
  if(cont==1){
    lcd.setCursor(0,1);
    lcd.print("cont==1");
  }
  cont=1;
}
