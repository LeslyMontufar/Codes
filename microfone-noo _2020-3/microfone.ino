#define led 13
#define sensor 0

void setup() {
  pinMode(led, OUTPUT);
  pinMode(sensor, INPUT);
  Serial.begin(115200);
}

int som;
void loop() {
  som = analogRead(sensor);
  Serial.println(som);
  if (som){
    digitalWrite(led, HIGH);
    Serial.println("ON");
    delay(1000);
  }
  Serial.println("desligado");
  digitalWrite(led, LOW);
}
