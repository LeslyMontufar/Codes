//3-Fading

#define ledPin 3 //-controle de intensidade- pino PWM
#define tiltSwitch 2 //interrupcao só no pino 2 ou 3
#define ledPin2 8
#define ledPin3 7

void funcao();

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(tiltSwitch, INPUT_PULLUP);//ativa o resistor interno do arduino

  attachInterrupt(digitalPinToInterrupt(tiltSwitch), funcao, RISING);//FALLING, LOW, CHANGE são possíveis;
}

void loop() {
  for(int i=0; i<255;i++){
    analogWrite(ledPin, i);
    delay(10);
  }
  for(int i=255; i>0; i--){
    analogWrite(ledPin,i);
    delay(10);
  }
}

void funcao(){  
  for(int i=1; i<=10; i++){
    digitalWrite(ledPin2, HIGH);
    delay(200);
    digitalWrite(ledPin2, LOW);
    delay(200);
    digitalWrite(ledPin3, HIGH);
    delay(200);
    digitalWrite(ledPin3, LOW);
    delay(200);
  }
}
