#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

AudioPlaySdWav           playSdWav1;     //xy=217,212
AudioMixer4              mixer1;         //xy=471,210
AudioOutputAnalog        dac1;           //xy=665,222
AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord2(playSdWav1, 1, mixer1, 1);
AudioConnection          patchCord3(mixer1, dac1);

int thresHold = 1027;

boolean fileOnePlaying = false;
boolean fileTwoPlaying = false;
boolean fileThreePlaying = false;
boolean fileFourPlaying = false;

void setup() {
  randomSeed(analogRead(A9));
  Serial.begin(9600);
  AudioMemory(8);
  SPI.setMOSI(11);
  SPI.setSCK(13);
  if (!(SD.begin(BUILTIN_SDCARD))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  pinMode(13, OUTPUT); // LED on pin 13
  mixer1.gain(0, 0.99);
  mixer1.gain(1, 0.99);
  delay(1000);
}

void loop() {
  if(touchRead(15) > thresHold) {
    int randNumber = random(1, 5);
    if(randNumber <= 1 && randNumber >= 0 && fileOnePlaying == false) {
      Serial.println("Start playing 1");
      playSdWav1.play("SDTEST1.WAV");
      digitalWrite(13, HIGH);
      fileOnePlaying = true;
      fileTwoPlaying = false;
      fileThreePlaying = false;
      fileFourPlaying = false;
      delay(10); // wait for library to parse WAV info
    }
    if(randNumber <= 2 && randNumber >= 1 && fileTwoPlaying == false) { 
      Serial.println("Start playing 2");
      playSdWav1.play("SDTEST2.WAV");
      digitalWrite(13, HIGH);
      fileOnePlaying = false;
      fileTwoPlaying = true;
      fileThreePlaying = false;
      fileFourPlaying = false;
      delay(10); // wait for library to parse WAV info
    }
    if(randNumber <= 3 && randNumber >= 2 && fileThreePlaying == false) { 
      Serial.println("Start playing 3");
      playSdWav1.play("SDTEST3.WAV");
      digitalWrite(13, HIGH);
      fileOnePlaying = false;
      fileTwoPlaying = false;
      fileThreePlaying = true;
      fileFourPlaying = false;
      delay(10); // wait for library to parse WAV info
    }
    if(randNumber <= 4 && randNumber >= 3 && fileFourPlaying == false) { 
      Serial.println("Start playing 4");
      playSdWav1.play("SDTEST4.WAV");
      digitalWrite(13, HIGH);
      fileOnePlaying = false;
      fileTwoPlaying = false;
      fileThreePlaying = false;
      fileFourPlaying = true;
      delay(10); // wait for library to parse WAV info
    }
  } else {
    digitalWrite(13, LOW);
  }
}










