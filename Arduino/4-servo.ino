#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}
unsigned long prevMillis = 0, pM=0;

void loop() {
  if (pos == 0) {
    if ((millis() - prevMillis) >= 15) {
      if (pos < 180) {
        pos++;
      }
      myservo.write(pos);
      prevMillis = millis();
    }
  }
  if (pos == 180) {
    if ((millis() - pM) >= 15) {
      if (pos > 0) {
        pos--;
      }
      pM=millis();
      myservo.write(pos);
    }
  }
}
