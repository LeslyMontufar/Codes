//https://www.youtube.com/watch?v=P7zbMjrBehg

#include <ESP8266WiFi.h>
#define LED 2

const char* ssid = "Aula_AP";
const char* password = "12345678"; //Usando memória heap, 8 digitos
WiFiServer server(80); //Porta padrao


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  IPAddress staticIP(192, 168, 4, 2); // IP set to Static
  IPAddress gateway(192, 168, 4, 1);// gateway set to Static
  IPAddress subnet(255, 255, 255, 0);// subnet set to Static

  WiFi.mode(WIFI_AP);// Working mode only as Acess Point

  WiFi.softAP(ssid, password, 2, 0);
  WiFi.config(staticIP, gateway, subnet);

  server.begin();

  Serial.println("Server started");
  Serial.println(WiFi.softAPIP());

  pinMode(LED, OUTPUT);
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  while (!client.available()) {
    delay(1);
  }

  String req = client.readStringUntil('\r');
  req = req.substring(req.indexOf("/") + 1, req.indexOf("HTTP") - 1);
  Serial.println(req);
  client.flush();

  // Match the request

  if (req.indexOf("DESLIGA") != -1)
  {
    client.print("REcebido seu dado DESLIGA   ");
    digitalWrite(LED, HIGH);
  }
  else if (req.indexOf("R") != -1)
  {
    client.print("REcebido seu dado R   ");
  }
  else if (req.indexOf("Lesly") != -1)
  {
    client.print("REcebido seu dado My Name   ");
  }
  else if (req.indexOf("LIGA") != -1)
  {
    client.print("REcebido seu dado LIGA   ");
    digitalWrite(LED, LOW); //É ao contrário
  }
  else {
    client.print("Invalid Request");
    client.flush();
    client.stop();
    return;
  }

  client.print("HTTP/1.1 200 OK\n\n");
  client.flush();

}
