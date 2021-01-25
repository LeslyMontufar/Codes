#include <WiFi.h>
#include <FirebaseESP32.h>

#define FIREBASE_HOST "esp32-flutter-firebase-7b9b6.firebaseio.com" 
#define FIREBASE_AUTH "DQAkV1J1LiRtlNg98TovG681IqhEI668xdbzxBeq"
#define WIFI_SSID "WANTED"
#define WIFI_PASSWORD "lsh7257e5"

//Define FirebaseESP32 data object
FirebaseData firebaseData;

// Root Path
String path = "/ESP32_Device";

/*****************************************************
 * LEITURA DA TEMPERATURA
 */

#include <OneWire.h>
#include <DallasTemperature.h>
#define pinoDS18B20 15 
#define pinoAquecer 2
#define pinoResfriar 2

OneWire oneWire(pinoDS18B20);
DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;

class TellMeTemperature {
  // Atributos da classe
  int tempPin;
  int hotPin;
  int coldPin;
  int interval;

  float minTemp;
  float maxTemp;

  // Váriáveis aux
  float temp;
  float prev_temp;
  int tempState;
  int prev_tempState;
  unsigned long previousMillis;

  public:  
  TellMeTemperature(int pinSensor, int pinH, int pinC, int readInterval, float minT, float maxT) { //the constructor has the same name of the class and initializes all atributes
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
      if(isnan(temp))
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
    if (prev_tempState != tempState){
      prev_tempState = tempState;
      Firebase.setInt(firebaseData, path + "/Temperature/State", tempState);
    }
  }  
};

// Objects
TellMeTemperature temperature(pinoDS18B20, pinoAquecer, pinoResfriar, 500, 26, 26.3);

void setup() {
  Serial.begin(115200);

  temperature.Init();
  initWifi();
}

void loop() {
  temperature.Uptade();
  temperature.ControlUptade();
}

void initWifi(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}
