//Créditos: WR KITS
#include<OneWire.h>
#include<DallasTemperature.h>

#define pinoDS18B20 15
#define led1 2

OneWire oneWire(pinoDS18B20);
DallasTemperature sensors(&oneWire);
DeviceAddress sensor1; //Device adress

void mostra_endereco_sensor(DeviceAddress deviceAddress);
void verifica_contato_sensor_DS18B20() {
  Serial.println("Localizado sensores DS18B20...");
  Serial.print("Foram encontrados ");
  Serial.print(sensors.getDeviceCount(), DEC); //DallasTemperature
  Serial.println(" sensores.");

  if (!sensors.getAddress(sensor1, 0)) //DeviceAddress
    Serial.println("Sensores nao encontrados !");
  Serial.print("Endereco sensor: ");
  mostra_endereco_sensor(sensor1);
  Serial.println("\n");
}

float tempMin = 999;
float tempMax = 0;

void setup() {
  Serial.begin(9600);
  sensors.begin();
  verifica_contato_sensor_DS18B20();
  pinMode(led1, OUTPUT);
}

void loop() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempC(sensor1);

  if (tempC < tempMin)
    tempMin = tempC;
  if (tempC > tempMax)
    tempMax = tempC;

  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Min: ");
  Serial.print(tempMin);
  Serial.print(" Max: ");
  Serial.print(tempMax);

  if (tempC > 25) {
    digitalWrite(led1, HIGH);
    Serial.println("\t Led1 on");
  } else {
    digitalWrite(led1, LOW);
    Serial.println("\t Led1 off");
  }
  delay(1000);
}

void mostra_endereco_sensor(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) { //i era de 16bits com a parte negativa
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
