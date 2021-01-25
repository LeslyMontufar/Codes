/*****************************************************
 * AQUECIMENTO DO AQUARIO
 */

 float TEMP_IDEAL_MIN = 26.5; // 21
 float TEMP_IDEAL_MAX = 27; // 25
 float DT = TEMP_IDEAL_MAX - TEMP_IDEAL_MIN;
 #define LED_BUILTIN 2 // PINO DO LED PARA TESTE

 void aquecimento(float t) {
  if (t < TEMP_IDEAL_MIN){
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("\t  Frio -> Ligar aquecimento");
  } else if(t > TEMP_IDEAL_MAX - (DT)/4) {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("\t  Quente -> Desligar aquecimento");
  } else {
    Serial.println("\t  Dentro da faixa de temp ideal");
  }
 }

/*****************************************************
 * LEITURA DA TEMPERATURA
 */

#include<OneWire.h>
#include<DallasTemperature.h>

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
