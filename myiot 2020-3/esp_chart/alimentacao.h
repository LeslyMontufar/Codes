#include <Servo.h>
#define pinServo 5

class Sweeper {
  Servo servo;              //O servo
  int pos;              // posição atual do servo
  int increment;        // incremento que moverá o servo para uma direção
  int  updateInterval;      // intervalo entre incrementos
  unsigned long lastUpdate; // última posição

  public:
    Sweeper(int interval) {
      updateInterval = interval;
      increment = 1;
    }

    void Attach(int pin) {
      servo.attach(pin);
    }

    void Detach() {
      servo.detach();
    }

    void Update() {
      if ((millis() - lastUpdate) > updateInterval) { // momento para atualizar
        lastUpdate = millis();
        pos += increment;
        servo.write(pos);
        Serial.println(pos);
        if ((pos >= 180) || (pos <= 0)) {// fim do sweep
          // reversão
          increment = -increment;
        }
      }
    }
};

Sweeper servo(pin_servo)
