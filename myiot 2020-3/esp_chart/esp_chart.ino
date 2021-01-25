#include <ESPmDNS.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

const char* ssid = "WANTED"; // NOME DA REDE
const char* password = "lsh7257e5"; // SENHA DA REDE

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

/*****************************************************
 * TEMPERATURA
 */
 
#include "Temperatura.h"
#define pinoDS18B20 15 // PINO DO SENSOR DE TEMPERATURA

OneWire oneWire(pinoDS18B20);
DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;
 
/*****************************************************
 * SETUP
 */

String processor(const String& var);
void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

  // Sensor de Temperatura
  sensors.begin();
  verifica_contato_sensor_DS18B20(sensors, sensor1);
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("Error! Error! SPIFFS!");
    return;
  }

  // Connect to Wi-Fi
  Serial.print("Conectando o ESP32 ao WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
  // Assign a name to IP address
  if(!MDNS.begin("esp32")) {
    Serial.println("Erro ao iniciar mDNS");
    return;
  }

  // Print ESP32 Local IP Address
  Serial.println();
  Serial.print("Meu endereço IP: ");
  Serial.println(WiFi.localIP());

  // Anexando html com SPIFFS
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  }); //The last argument of the send() function is the processor, so that we can replace the placeholder with the value we want,in this case the ledState.
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });
  server.on("/temperatura.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/temperatura.js", "text/javascript");
  });

  // Routes: tags para comunicacao
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){ //HTTP_GET indica que existe comunicacao
    request->send_P(200, "text/plain", readDS18B20Temperature(sensors, sensor1).c_str());
  });
  server.on("/aquecimento", HTTP_GET, [](AsyncWebServerRequest *request){ 
    request->send_P(200, "text/plain", String(digitalRead(LED_BUILTIN)).c_str());
  });

  // Start server
  server.begin();
}
 
void loop(){
  
}

String ledState,t;
String processor(const String& var){ //só altera com atualizacao da pagina
  Serial.println(String(digitalRead(LED_BUILTIN)));
  Serial.print(var);
  Serial.print(": ");
  if(var == "AQUECIMENTO"){
    if(digitalRead(LED_BUILTIN)){
      ledState = "ON";
    }
    else{
      ledState = "OFF";
    }
    Serial.println(ledState);
    return ledState;
  }
  else if (var == "TEMPERATURE"){
    t = readDS18B20Temperature(sensors, sensor1);
    Serial.println(t);
    return t;
  }
}
