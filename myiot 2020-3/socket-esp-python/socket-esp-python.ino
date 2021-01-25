#include <WiFi.h>
#include <WebSocketsServer.h>

// Constants
const char *ssid = "ssid-name"; //service set identifier segundo a norma IEEE 802.11
const char *password = "senha123";

// Globals
WebSocketsServer webSocket = WebSocketsServer(80);

// Callback
void onWebSocketEvent(uint8_t num,
                      WStype_t type,
                      uint8_t * payload,
                      size_t length){
  // Percebe o tipo de evento WebSocket
  switch(type){
    // Client desconectou
    case WStype_DISCONNECTED:
      Serial.printf("{%u} Desconectado!\n", num);
      break;
    //Novo client conectou!
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num); //Internet Protocol, parece que o padrao aqui em casa seria 192.168.0.1
        Serial.printf("{%u} Conectado de ", num); // O IP é identificação na rede
        Serial.println(ip.toString());
      }
      break;
     //Ecoar a memsagem de texto do client
     case WStype_TEXT:
      Serial.printf("{%u} Text: %s\n", num, payload);
      webSocket.sendTXT(num,payload);
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

void setup() {
  // Inicia o Serial port com 115200 bits per second
  Serial.begin(115200);

  //Conecta
  Serial.println("Conectando ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //Printar IP address
  Serial.println("Conectado!");
  Serial.print("Meu endereço IP: ");
  Serial.println(WiFi.localIP()); 
  
  // Inicia WebSocket server e vincular o callback
  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);  //unico evento atento durante todo o loop
}

void loop() {
  webSocket.loop();
}
