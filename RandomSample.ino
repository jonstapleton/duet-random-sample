#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>

// WAV files converted to code by wav2sketch
#include "AudioSampleSnare.h"        // http://www.freesound.org/people/KEVOY/sounds/82583/
#include "AudioSampleTomtom.h"       // http://www.freesound.org/people/zgump/sounds/86334/
#include "AudioSampleHihat.h"        // http://www.freesound.org/people/mhc/sounds/102790/
#include "AudioSampleKick.h"         // http://www.freesound.org/people/DWSD/sounds/171104/
#include "AudioSampleGong.h"         // http://www.freesound.org/people/juskiddink/sounds/86773/
#include "AudioSampleCashregister.h" // http://www.freesound.org/people/kiddpark/sounds/201159/

AudioPlayMemory    sound0;
AudioPlayMemory    sound1;  
AudioPlayMemory    sound2;  
AudioPlayMemory    sound3;
AudioPlayMemory    sound4;
AudioPlayMemory    sound5;
AudioMixer4        mix1;    
AudioMixer4        mix2;    
AudioOutputAnalog  dac;     

// Create Audio connections between the components
//
AudioConnection c1(sound0, 0, mix1, 0);
AudioConnection c2(sound1, 0, mix1, 1);
AudioConnection c3(sound2, 0, mix1, 2);
AudioConnection c4(sound3, 0, mix1, 3);
AudioConnection c5(mix1, 0, mix2, 0);   // output of mix1 into 1st input on mix2
AudioConnection c6(sound4, 0, mix2, 1);
AudioConnection c7(sound5, 0, mix2, 2);
AudioConnection c10(mix2, 0, dac, 0);

Bounce button0 = Bounce(0, 5);

void setup() {
  pinMode(0, INPUT_PULLUP);
  AudioMemory(10);
  audioShield.enable();
  audioShield.volume(0.5);
  mix1.gain(0, 0.4);
  mix1.gain(1, 0.4);
  mix1.gain(2, 0.4);
  mix1.gain(3, 0.4);
  mix2.gain(1, 0.4);
  mix2.gain(2, 0.4);
}

void loop() {
  button0.update();
  int randNumber = random(1, 5);
  if (button0.fallingEdge()) {
    if(randNumber <= 1 && randNumber >= 0) {
      sound0.play(AudioSampleSnare);
    } else if(randNumber <= 2 && randNumber >= 1) {
      sound1.play(AudioSampleTomtom);
    } else if(randNumber <= 3 && randNumber >= 2) {
      sound3.play(AudioSampleKick);
    } else if(randNumber <= 4 && randNumber >= 3) {
      sound4.play(AudioSampleGong);
    } else if(randNumber <= 4 && randNumber >= 3) {
      sound5.play(AudioSampleCashregister);
    }
  }
}

