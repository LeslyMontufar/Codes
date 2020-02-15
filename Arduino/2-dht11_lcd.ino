//1-dht11+lcd

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3,POSITIVE);

#include <dht.h>
dht DHT;
const int dht11Pin= 8;

void setup() {
  lcd.begin(16,2);
}

int var2;
unsigned long prevMillis;//==0

void loop() {
  int var1 = DHT.read11(dht11Pin);
  if(millis()-prevMillis >= 500 && var1!= var2){
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Temperature:");
     lcd.print(DHT.temperature);
     lcd.print(" C");
     lcd.setCursor(0,1);
     lcd.print("Humidity: ");
     lcd.print(DHT.humidity);
     lcd.print("%");
     prevMillis = millis();
  }
  var2 = var1;
}
