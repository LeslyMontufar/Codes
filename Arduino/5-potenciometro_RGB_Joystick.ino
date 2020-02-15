//2-potenciometro + RGB + Joystick

#define potPin A3
//para poder -controlar intensidade- tem usar pino PWM;

const int redPin=11;
const int greenPin=10;
const int bluePin=9;
#define xPin A0
#define yPin A1
const int SW = 7;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(potPin, INPUT);//nao precisava declarar o INPUT porque o pino é analogico;
  pinMode(SW, INPUT_PULLUP);
  Serial.begin(9600);
}

int valor_pot, x, y; //z== valor_pot;
void loop() {
  valor_pot= analogRead(potPin);
  valor_pot= map(valor_pot, 0, 1023, 0, 255);
  analogWrite(greenPin, valor_pot);
  //Serial.print("valor_pot = ");
  Serial.println(valor_pot);

 // x= analogRead(xPin);
 // x= map(x,0,1023,0,255);
  //analogWrite(redPin, x);
 // Serial.println(x);

 // y= map(analogRead(yPin),0,1023,0,255);
 // analogWrite(bluePin,y);
 // Serial.println(y);
 // Serial.println();
  delay(100);
}
