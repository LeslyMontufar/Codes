//creditos: https://www.youtube.com/watch?v=iZc8_X8JxYs

#include "WiFi.h"

String redeSSID = "";
int intensidadeSinal = -9999;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  //WiFi.disconnect();
}

void loop() {
  Serial.println("scan start");

  int n = WiFi.scanNetworks();
  Serial.println("Escaneamento realizado");

  //verifica se encontrou alguma rede
  if (n == 0) {
    Serial.println("Nenhuma rede encontrada");
  } else {
    redeSSID = "";
    intensidadeSinal = -9999;
    Serial.print(n);
    Serial.println(" redes encontradas\n");
    for (int i = 0; i < n; ++i) {
      // imprime no log cada uma das redes encontradas
      Serial.print("SSID: ");
      Serial.println(WiFi.SSID(i)); //nome da rede
      Serial.print("SINAL: ");
      Serial.print(WiFi.RSSI(i)); //intensidade do sinal
      Serial.print("\t\tcanal: ");
      Serial.print((int)WiFi.channel(i));
      Serial.print("\t\tMAC: ");
      Serial.print(WiFi.BSSIDstr(i));
      Serial.println("\n\n");

      if (abs(WiFi.RSSI(i)) < abs(intensidadeSinal)){
        intensidadeSinal = WiFi.RSSI(i);
        redeSSID = WiFi.SSID(i);
        Serial.print("REDE COM MELHOR SINAL ENCONTRADA: ( ");
        Serial.print(redeSSID);
        Serial.print(" ) - SINAL : ( ");
        Serial.print(intensidadeSinal );
        Serial.println(" )");
      }
      delay(10);
    }
  }
  Serial.println("\n------------------------------------------------------------------------------------\n");

  // deixa um intervalo de 10 segundos para fazer um novo escaneamento
  delay(5000);
}
