#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h> //já baixou

// Constants
const char *ssid = "ESP32AP"; // Nome da rede
const char *password = "senha123456"; // Senha da rede

const char *msg_toggle_led = "toggleLED"; //toggle==alternar
const char *msg_get_led = "getLEDState";

const int dns_port = 53;
const int http_port = 80; //porta http padrão
const int ws_port = 1337; //porta da web socket
const int led_pin = 2; //LED_BUILTIN

// Globals 
AsyncWebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(1337);
char msg_buf[10];
int led_state = 0;

/******************************************************************************************
 * Functions
 */

// Callback: recebendo mensagem da WebSocket
void onWebSocketEvent(uint8_t client_num, 
                      WStype_t type,
                      uint8_t * payload, //payload é a msg recebida
                      size_t length){
  // Percebe o tipo de evento WebSocket
  switch(type){
    // Algum client desconectou
    case WStype_DISCONNECTED:
      Serial.printf("{%u} Desconectado!\n", client_num);
      break;
    
    //Novo client conectou!
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(client_num); //Internet Protocol, parece que o padrao aqui em casa seria 192.168.0.1
        Serial.printf("{%u} Conectado de ", client_num); // O IP é identificação na rede
        Serial.println(ip.toString());
      }
      break;
    
     //Aqui executa a ação conforme o texto!
     //No caso, será o alternador de LED
     case WStype_TEXT:
      Serial.printf("{%u} Texto recebido: %s\n", client_num, payload);
      
      // Toggle LED - Alternador de LED
      if (!strcmp( (char *) payload, "toggleLED")) { //um dos comandos é toggleLED e o outro é getLEDState
        led_state = led_state? 0:1;
        Serial.printf("Toggling LED to %u\n", led_state);
        digitalWrite(led_pin, led_state);
        
      } else if (!strcmp( (char *) payload, "getLEDState")) {
        sprintf(msg_buf, "%d", led_state); //adiciona texto a msg_buf -> manda p led_state em char
        Serial.printf("Sending to [%u]: %s\n", client_num, msg_buf);
        webSocket.sendTXT(client_num, msg_buf); // Aqui que manda msg evt no websocket.onmessage !!!
      
      } else {
        Serial.println("[%u] Messagem não reconhecida.");
      }
      break;

     //Ignoramos os outros tipos de mensagem
     case WStype_BIN:
     case WStype_ERROR:
     case WStype_FRAGMENT_TEXT_START:
     case WStype_FRAGMENT_BIN_START:
     case WStype_FRAGMENT:
     case WStype_FRAGMENT_FIN:
     default:
      break;
  }
}

// Callback: enviar para homepage do index.html
void onIndexRequest(AsyncWebServerRequest *request) {
  IPAddress remote_ip = request->client()->remoteIP();
  Serial.println("["+remote_ip.toString() +
                  "] HTTP GET request of "+ request->url());
  request->send(SPIFFS, "/index.html", "text/html"); //anexando um vinculo com /index.html
}

// Callback: enviar o arquivo css do homepage
void onCSSRequest(AsyncWebServerRequest *request) {
  IPAddress remote_ip = request->client()->remoteIP();
  Serial.println("["+remote_ip.toString() +
                  "] HTTP GET request of "+ request->url());
  request->send(SPIFFS, "/style.css", "text/css"); //anexando um vinculo com css
}

// Callback: enviar para homepage do index.html
void onPageNotFound(AsyncWebServerRequest *request) {
  IPAddress remote_ip = request->client()->remoteIP();
  Serial.println("["+remote_ip.toString() +
                  "] HTTP GET request of "+ request->url());
  request->send(404, "text/plain", "Not found");
}

/******************************************************************************************
 * Main
 */

void setup() {
    //Inicializa LED e desliga
    pinMode(led_pin, OUTPUT);
    digitalWrite(led_pin, LOW);

    //Inicia a porta Serial
    Serial.begin(115200);

    // Testa se SPIFFS está funciona, senao mostra:
    if (!SPIFFS.begin()) {
      Serial.println("Error! Error! no SPIFFS");
      while(1);
    }

    // Se deu certo, inicia o Access Point
    WiFi.softAP(ssid, password);
    // printa 
    Serial.println();
    Serial.println("AP rodando");
    Serial.print("My IP address: ");
    Serial.println(WiFi.softAPIP());

    // On HTTP request for root, fornece index.html file
    server.on("/", HTTP_GET, onIndexRequest);
    server.on("/style.css", HTTP_GET, onCSSRequest);
    server.onNotFound(onPageNotFound);

    // Inicia o servidor web
    server.begin();

    // Inicia o servidor do webSocket e assigna o callback correspondente
    webSocket.begin();
    webSocket.onEvent(onWebSocketEvent);
}

void loop() {
    webSocket.loop(); // Procura e manipula as webSockets data
}
