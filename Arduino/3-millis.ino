//1-millis()
#define ledPin 13

void setup() {
  pinMode(ledPin, OUTPUT);

}
unsigned long previousMillis= millis();
static bool ledState= LOW;
void loop() {
  
  if(millis()-previousMillis>= 200){//o maior(>) é importante, pois o processador pode estar abaixo desse if quando for exatamente igual a =200
    ledState = !ledState;
    previousMillis=millis();
  }
  digitalWrite(ledPin, ledState);

}
