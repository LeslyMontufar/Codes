#define buzzer 8
#include "Lesly.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2,1,0,4,5,6,7,3, POSITIVE);

int melodia[]{
  //9*14 + 7 = 133
  NOTE_FS4, NOTE_E4, NOTE_FS4, NOTE_FS4, NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_FS4, NOTE_E4, 
  NOTE_D4, NOTE_G3, NOTE_G3, NOTE_D4, NOTE_C4, NOTE_B3, NOTE_A3, NOTE_B3, 0, NOTE_FS4, //10
  NOTE_E4, NOTE_FS4, NOTE_FS4, NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_FS4, 
  NOTE_E4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_CS4, NOTE_FS4, NOTE_E4, NOTE_FS4,
  NOTE_FS4, NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_G4,
  NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_D4, 
  NOTE_A4, NOTE_A4, NOTE_A4, NOTE_B4, NOTE_G4, NOTE_FS4, NOTE_G4, NOTE_FS4, NOTE_E4,
  NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_B3, NOTE_E4, 
  NOTE_E4, NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_B4, NOTE_G4, 
  NOTE_FS4, NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_B4, NOTE_A4, 
  NOTE_B4, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_B4, NOTE_C5, NOTE_B4, NOTE_G4, NOTE_E4, 
  NOTE_D4, NOTE_B4, NOTE_C5, NOTE_B4, NOTE_G4, NOTE_E4, NOTE_G4, NOTE_FS4, NOTE_E4, 
  NOTE_FS4, NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_B4, NOTE_G4, 
  NOTE_FS4, NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_B4,  NOTE_A4,
  NOTE_B4, NOTE_B4,  NOTE_A4, NOTE_B4, NOTE_B4,  NOTE_A4, NOTE_B4
};

int duracao[]{
  //9*14 + 8 = 134
  4, 8, 2, 4, 8, 4, 8, 4, 8,
  4, 4, 8, 4, 8, 4, 8, 2, 8,
  4, 8, 2, 4, 8, 4, 8, 2, 8,
  4, 8, 4, 2, 2, 4, 1, 4, 8,
  2, 4, 8, 4, 8, 2, 8, 4, 8, 
  4, 2, 2, 4, 1, 2, 4, 1, 2,
  8, 2, 8, 4, 4, 4, 8, 4, 8,
  2, 4, 4, 8, 4, 8, 2, 4, 4,
  8, 2, 4, 4, 4, 2, 8, 4, 4,
  4, 8, 2, 8, 2, 4, 4, 4, 1,
  4, 1, 1, 4, 1, 8, 4, 8, 4,
  2, 2, 8, 4, 8, 4, 2, 4, 1,
  4, 1, 4, 4, 4, 2, 8, 4, 8,
  4, 8, 2, 8, 2, 4, 4, 4, 1,
  4, 1, 1, 4, 1, 1, 4, 1
  
  };

void setup() {
  lcd.begin(16,2);
  
  lcd.setCursor(0,0);
  for(int i=0; i<134; i++){
    lcd.clear();
    int tempo = 2000/duracao[i]; 
    tone(buzzer, melodia[i], tempo);
    lcd.print(melodia[i]);
    int tempoEntreNotas= tempo *1.3;
    delay(tempoEntreNotas);
    noTone(buzzer);  
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
