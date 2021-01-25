//RASCUNHO

#include<OneWire.h>
#include<DallasTemperature.h>

// GLOBALS
#define TEMP_IDEAL_MIN 26.5; // 21
#define TEMP_IDEAL_MAX 27; // 25
#define DT TEMP_IDEAL_MAX - TEMP_IDEAL_MIN;
#define LED_BUILTIN 2

 
class SensorDS18B20 {
  OneWire oneWire(pinoDS18B20);
  DallasTemperature sensors(&oneWire);
  DeviceAddress sensor1;
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

/*****************************************************
 * LEITURA DA TEMPERATURA
 */

void mostra_endereco_sensor(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) { //i era de 16bits com a parte negativa
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
void verifica_contato_sensor_DS18B20(DallasTemperature sensors, DeviceAddress sensor1) {
  Serial.println("\n***********************************************");
  Serial.println("Localizado sensores DS18B20...");
  Serial.print("Foram encontrados ");
  Serial.print(sensors.getDeviceCount(), DEC); //DallasTemperature
  Serial.println(" sensores.");

  if (!sensors.getAddress(sensor1, 0)) //DeviceAddress
    Serial.println("Sensores nao encontrados !");
  Serial.print("Endereco sensor: ");
  mostra_endereco_sensor(sensor1);
  Serial.println("\n***********************************************\n");
}

float tempMin = 999;
float tempMax = 0;

String readDS18B20Temperature(DallasTemperature sensors, DeviceAddress sensor1) {
  sensors.requestTemperatures();
  float t = sensors.getTempC(sensor1);
  if (t < tempMin)
    tempMin = t;
  if (t > tempMax)
    tempMax = t;

  Serial.print("Temp atual: ");
  Serial.print(t);
  Serial.print("\t Min: ");
  Serial.print(tempMin);
  Serial.print(" Max: ");
  Serial.print(tempMax);

  if (isnan(t)) {    
    Serial.println("Falha em ler o sensor DS18B20!");
    return "";
  }
  else {
    aquecimento(t);
    return String(t);
  }
}
