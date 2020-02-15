#include "Lesly.h"

int sadness[]{
  NOTE_FS4, NOTE_E4, NOTE_B3, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_E4, 0,
  NOTE_G4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_D4, NOTE_B4, NOTE_A4, 0,
  
  NOTE_FS4, NOTE_E4, NOTE_B3, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_E4,0,
  NOTE_G4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_D4, NOTE_E4, 0
};

int duration[]{
  4, 4, 1, 2, 2, 1, 1, 4,//8
  1, 2, 2, 2, 2, 1, 1, 2,//8

  4, 4, 1, 2, 2, 1, 1, 4,//8
  1, 2, 2, 2, 2, 1, 1 //7
};
void setup() {

}

void loop() {
  for(int nota=0; nota<31; nota++){
    int noteDuration = 1000/ duration[nota];

    tone(8, sadness[nota], noteDuration);
    
    int pausaEntreNotas = noteDuration *1.3;
    delay(pausaEntreNotas);
    noTone(8);
  }

}
