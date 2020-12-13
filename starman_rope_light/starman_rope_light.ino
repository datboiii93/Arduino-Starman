#include <FastLED.h>

const int LED_QUANT = 144;

#define LED_PIN     7
#define NUM_LEDS    LED_QUANT

CRGB leds[NUM_LEDS];

int button = 13;

int redRand;
int greenRand;
int blueRand;

bool isPlaying = false;

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(2, 4); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

void Dormant(){
    for(int k = 0; k < LED_QUANT; k++){
      leds[k] = CRGB(255, 200, 20);
      FastLED.show();
    }
}

void Activate(){
  myDFPlayer.play(1);
  for (int i = 0; i < 45; i++){
    redRand = random(0,256);
    greenRand = random(0,256);
    blueRand = random(0,256);
    FastLED.showColor(CRGB(redRand, greenRand, blueRand));
    delay(170);
  }
  Dormant();
  isPlaying = false;
  myDFPlayer.stop();
}

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(20);  //Set volume value. From 0 to 30
  Dormant();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(digitalRead(button));
  if(digitalRead(button) == 1 && isPlaying == false){
    isPlaying = true;
    Activate();
  }
}
