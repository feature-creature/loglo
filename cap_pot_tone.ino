#include "pitches.h"

// notes in the melody: length 89
int melody[] = {
  NOTE_B0,
  NOTE_C1,
  NOTE_CS1,
  NOTE_D1,
  NOTE_DS1,
  NOTE_E1,
  NOTE_F1,
  NOTE_FS1,
  NOTE_G1,
  NOTE_GS1,
  NOTE_A1,
  NOTE_AS1,
  NOTE_B1,
  NOTE_C2,
  NOTE_CS2,
  NOTE_D2,
  NOTE_DS2,
  NOTE_E2,
  NOTE_F2,
  NOTE_FS2,
  NOTE_G2,
  NOTE_GS2,
  NOTE_A2,
  NOTE_AS2,
  NOTE_B2,
  NOTE_C3,
  NOTE_CS3,
  NOTE_D3,
  NOTE_DS3,
  NOTE_E3,
  NOTE_F3,
  NOTE_FS3,
  NOTE_G3,
  NOTE_GS3,
  NOTE_A3,
  NOTE_AS3,
  NOTE_B3,
  NOTE_C4,
  NOTE_CS4,
  NOTE_D4,
  NOTE_DS4,
  NOTE_E4,
  NOTE_F4,
  NOTE_FS4,
  NOTE_G4,
  NOTE_GS4,
  NOTE_A4,
  NOTE_AS4,
  NOTE_B4,
  NOTE_C5,
  NOTE_CS5,
  NOTE_D5,
  NOTE_DS5,
  NOTE_E5,
  NOTE_F5,
  NOTE_FS5,
  NOTE_G5,
  NOTE_GS5,
  NOTE_A5,
  NOTE_AS5,
  NOTE_B5,
  NOTE_C6,
  NOTE_CS6,
  NOTE_D6,
  NOTE_DS6,
  NOTE_E6,
  NOTE_F6,
  NOTE_FS6,
  NOTE_G6,
  NOTE_GS6,
  NOTE_A6,
  NOTE_AS6,
  NOTE_B6,
  NOTE_C7,
  NOTE_CS7,
  NOTE_D7,
  NOTE_DS7,
  NOTE_E7,
  NOTE_F7,
  NOTE_FS7,
  NOTE_G7,
  NOTE_GS7,
  NOTE_A7,
  NOTE_AS7,
  NOTE_B7,
  NOTE_C8,
  NOTE_CS8,
  NOTE_D8,
  NOTE_DS8
};

String melodyName[] = {
  "B0",
  "C1",
  "CS1",
  "D1",
  "DS1",
  "E1",
  "F1",
  "FS1",
  "G1",
  "GS1",
  "A1",
  "AS1",
  "B1",
  "C2",
  "CS2",
  "D2",
  "DS2",
  "E2",
  "F2",
  "FS2",
  "G2",
  "GS2",
  "A2",
  "AS2",
  "B2",
  "C3",
  "CS3",
  "D3",
  "DS3",
  "E3",
  "F3",
  "FS3",
  "G3",
  "GS3",
  "A3",
  "AS3",
  "B3",
  "C4",
  "CS4",
  "D4",
  "DS4",
  "E4",
  "F4",
  "FS4",
  "G4",
  "GS4",
  "A4",
  "AS4",
  "B4",
  "C5",
  "CS5",
  "D5",
  "DS5",
  "E5",
  "F5",
  "FS5",
  "G5",
  "GS5",
  "A5",
  "AS5",
  "B5",
  "C6",
  "CS6",
  "D6",
  "DS6",
  "E6",
  "F6",
  "FS6",
  "G6",
  "GS6",
  "A6",
  "AS6",
  "B6",
  "C7",
  "CS7",
  "D7",
  "DS7",
  "E7",
  "F7",
  "FS7",
  "G7",
  "GS7",
  "A7",
  "AS7",
  "B7",
  "C8",
  "CS8",
  "D8",
  "DS8"
};


const int ledPin = 3;
int capPotVal;
int capPotMin = 1023;
int capPotMax = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  indicateCalibrate();
  // calibrate soft pot
  while (millis() < 10500) {
    capPotVal = analogRead(A0);
    if (capPotVal > capPotMax) {
      capPotMax = capPotVal;
    }
    if (capPotVal < capPotMin) {
      capPotMin = capPotVal;
    }
  }
  indicateCalibrate();
  
  Serial.print("capPotMax: ");
  Serial.println(capPotMax);
  Serial.print("capPotMin: ");
  Serial.println(capPotMin);
}

void loop() {
  // capacitive touch potentiometer @ 5V : from 1/3 Vcc to 2/3 Vcc
  // 341 - 683
  capPotVal = analogRead(A0);
  int potMap = constrain(map(capPotVal, capPotMin, capPotMax - (capPotMax/15), 0, 88), 0, 88);

  // default returned value is 0
  // keep previous tone if no human touch input
  //  if(potMap != 0 && potMap != 1){
  if (potMap < 88) {
    // log values
    Serial.print("current tone : ");
    Serial.print(capPotVal);
    Serial.print(" : ");
    Serial.print(potMap);
    Serial.print(" : ");
    Serial.print(melody[potMap]);
    Serial.print(" : ");
    Serial.println(melodyName[potMap]);

    // no duration, play continuously
    tone(ledPin, melody[potMap]);
    //  int shared = potVal;
    //  Serial.print("photoresistor value: ");
    //  Serial.println(shared);
    //  Serial.print("difference: ");
    //  Serial.println(potVal - shared);
  }

  // optional
  // delay 100 milli for cpu's sake
  // or for how often a new tone is read
  // 10 / 25 / [50] / 100
  delay(100);

}

void indicateCalibrate() {
  digitalWrite(ledPin, HIGH);
  delay(50);
  digitalWrite(ledPin, LOW);
  delay(50);
  digitalWrite(ledPin, HIGH);
  delay(50);
  digitalWrite(ledPin, LOW);
  delay(50);
  digitalWrite(ledPin, HIGH);
  delay(50);
  digitalWrite(ledPin, LOW);
  delay(50);
  digitalWrite(ledPin, HIGH);
  delay(50);
  digitalWrite(ledPin, LOW);
  delay(50);
  digitalWrite(ledPin, HIGH);
  delay(50);
  digitalWrite(ledPin, LOW);
  delay(50);
}

