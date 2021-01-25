/*****************************************************
 * LEITURA DA TEMPERATURA
 */

#include<OneWire.h>
#include<DallasTemperature.h>
#define pinoDS18B20 15 // PINO DO SENSOR DE TEMPERATURA
#define pinoAquecer 2
#define pinoResfriar 2

//OneWire oneWire(pinoDS18B20);
//DallasTemperature sensors(&oneWire);
//DeviceAddress sensor1;

class TellMeTemperature {
  // Atributos da classe
  int tempPin;
  int hotPin;
  int coldPin;
  int interval;

  float minTemp;
  float maxTemp;

  OneWire oneWire(tempPin);
  DallasTemperature sensors(&oneWire);
  DeviceAddress sensor1;

  // Váriáveis aux
  float temp;
  float prev_temp;
  int tempState;
  unsigned long previousMillis;

  public:
  TellMeTemperature(int pinSensor, int pinH, int pinC, int readInterval, minT, maxT) { //the constructor has the same name of the class and initializes all atributes
    tempPin = pinSensor;
    hotPin = pinH;
    coldPin = pinC;
    interval = readInterval;

    minTemp = minT;
    maxTemp = maxT;

    temp = 0;
    prev_temp = 0;
    tempState = 0; // -1 frio | 0 estável | 1 quente
    previousMillis = 0;
  }

  void verifica_contato_sensor_DS18B20() {
    Serial.println("\n***********************************************");
    Serial.println("Localizado sensores DS18B20...");
    Serial.print("Foram encontrados ");
    Serial.print(sensors.getDeviceCount(), DEC); //DallasTemperature
    Serial.println(" sensores.");
  
    if (!sensors.getAddress(sensor1, 0)) //DeviceAddress
      Serial.println("Sensores nao encontrados !");
    
    Serial.print("Endereco sensor: ");
    for (uint8_t i = 0; i < 8; i++) { //i era de 16bits com a parte negativa
      if (sensor1[i] < 16) Serial.print("0");
      Serial.print(sensor1[i], HEX);
    }
    Serial.println("\n***********************************************\n");
  }

  void Init() {
    sensors.begin();
    pinMode(hotPin, OUTPUT);
    pinMode(coldPin, OUTPUT);

    verifica_contato_sensor_DS18B20(); // Info | Serial Port
  }

  void Uptade() {
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis >= interval) {
      sensors.requestTemperatures(); // é mais útil se tiver mais de um sensor DS18B20
      temp = sensors.getTempC(sensor1);
      if(isnan(t))
        Serial.println("Falha ao ler o sensor de temperatura");
      else if(prev_temp != temp){ //evita atualizar à toa
        prev_temp = temp;
        Firebase.setDouble(firebaseData, path + "/Temperature/Data", temp); //Envia para o Firebase
      }     
    }
  }

  void ControlUptade() {
    if(temp < minTemp) {
      tempState = -1;
      Serial.print("Frio -> ");
      Serial.println(temp);
      digitalWrite(hotPin, HIGH);
    } else if (temp>maxTemp) {
      tempState = 1;
      Serial.print("Quente -> ");
      Serial.println(temp);
      digitalWrite(coldPin, LOW);
    } else {
      tempState = 0;
      Serial.print("Temperatura estável -> ");
      Serial.println(temp);
      digitalWrite(hotPin, LOW);
      digitalWrite(coldPin, LOW);
    }
  }  
}
