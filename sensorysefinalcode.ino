#pragma region Global Variables 

#pragma region Button Pins 

#define Button1_Pin 6
#define Button2_Pin 3
#define Button3_Pin 4
#define Button4_Pin 7

int buttonPins[] = {Button1_Pin, Button2_Pin, Button3_Pin, Button4_Pin};
bool buttonStatus[] = {false, false, false, false};

#pragma endregion Button Pins 

#pragma region LED 

#define NUM_LEDS 36

#define LED1_Pin 2
#define LED2_Pin 9 
#define LED3_Pin 10
#define LED4_Pin 8


#pragma endregion LED 

#pragma region Time 

#define TimeLimit 3000
#define BlinkDelay 1000

#pragma endregion Time 

#pragma region Audio 

int tones[] = {262, 330,392,494};

#define Buzzer_Pin1_POW 13
#define Buzzer_Pin2_POW 12
#define Buzzer_Pin1_DAT 11
#define Buzzer_Pin2_DAT 5

#pragma endregion Audio

#pragma endregion Global Variables 

#include <FastLED.h>

CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];
CRGB leds4[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, LED1_Pin>(leds1, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, LED2_Pin>(leds2, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, LED3_Pin>(leds3, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, LED4_Pin>(leds4, NUM_LEDS);

  // Initialize button pins as INPUT
  pinMode(Button1_Pin, INPUT_PULLUP);
  pinMode(Button2_Pin, INPUT_PULLUP);
  pinMode(Button3_Pin, INPUT_PULLUP);
  pinMode(Button4_Pin, INPUT_PULLUP);

  pinMode(Buzzer_Pin1_POW, OUTPUT);
  pinMode(Buzzer_Pin2_POW, OUTPUT);
  pinMode(Buzzer_Pin1_DAT, OUTPUT);
  pinMode(Buzzer_Pin1_DAT, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  int currentScore = 0; 
  // int pattern[] = {0,3,2,3,3,2,0,0,2,3};

  while(currentScore < 10){
    
    delay(500);

    randomSeed(analogRead(A0)); //makes sure its acutally random

    bool roundWin = false;

    //Inditcate Button to be Pushed 
     int targetButton = random(0, 4);
      //int targetButton = 0;
    //  int targetButton = pattern[currentScore];
     switch(targetButton){
      case 0:
       turnOn(targetButton, CRGB::Blue);
       delay(BlinkDelay);
       turnOff(targetButton); 
      break;
      case 1: 
      turnOn(targetButton, CRGB::OrangeRed);
       delay(BlinkDelay);
       turnOff(targetButton); 
      break;
      case 2:
      turnOn(targetButton, CRGB::Magenta);
       delay(BlinkDelay);
       turnOff(targetButton);  
      break;
      case 3:
      turnOn(targetButton, CRGB::Yellow);
       delay(BlinkDelay);
       turnOff(targetButton);  
      break;
     }
     
    unsigned long startTime = millis();

    while(millis() - startTime < TimeLimit){
        int numPressed = 0; 
        for(int i = 0; i < 4; i++){
        if(!digitalRead(buttonPins[i])){
          numPressed++;
          buttonStatus[i] = true;
        }
        else{
          buttonStatus[i] = false;
        }
      }

     if(numPressed == 1 && buttonStatus[targetButton]){
        turnOn(targetButton, CRGB::Green);
        delay(BlinkDelay);
        turnOff(targetButton);
        roundWin = true;
        currentScore += 1;
        break;
      }
      else if(numPressed >= 1 && !(buttonStatus[targetButton])){
        break;
      }
    }

    if(!roundWin){

      for(int i = 0; i < 4; i++){
            turnOn(i, CRGB::Red);
      }
      
      delay(BlinkDelay);
       
      for(int i = 0; i < 4; i++){
           turnOff(i);
      }

        while(true){
        if(!digitalRead(Button2_Pin) && !digitalRead(Button4_Pin) && digitalRead(Button1_Pin) && digitalRead(Button3_Pin)){
          unsigned long exitTimeStart = millis();
          while(millis() - exitTimeStart < 3000){
            if(digitalRead(Button2_Pin) || digitalRead(Button4_Pin) || !digitalRead(Button1_Pin) || !digitalRead(Button3_Pin)){
              break;
            }
          }

          if(millis() - exitTimeStart >= 3000){
            for(int i = 0; i < 4; i++){
            turnOn(i, CRGB::White);
      }
      
            delay(BlinkDelay);
       
            for(int i = 0; i < 4; i++){
                turnOff(i);
            }
            break;
          }

        }
      }
    }
  }

  if(currentScore >= 10){
    for(int i = 0; i < 4; i++){
            turnOn(i, CRGB::Green);
    }
    delay(3000);
    for(int i = 0; i < 4; i++){
            turnOff(i);
    }
  }
  while(true){
        if(!digitalRead(Button2_Pin) && !digitalRead(Button4_Pin) && digitalRead(Button1_Pin) && digitalRead(Button3_Pin)){
          unsigned long exitTimeStart = millis();
          while(millis() - exitTimeStart < 3000){
            if(digitalRead(Button2_Pin) || digitalRead(Button4_Pin) || !digitalRead(Button1_Pin) || !digitalRead(Button3_Pin)){
              break;
            }
          }

          if(millis() - exitTimeStart >= 3000){
            for(int i = 0; i < 4; i++){
            turnOn(i, CRGB::White);
      }
      
            delay(BlinkDelay);
       
            for(int i = 0; i < 4; i++){
                turnOff(i);
            }
            break;
          }

        }
      }
}


void turnOn(int n, CRGB color){ 
  switch(n){
      case 0:
        fill_solid(leds1, NUM_LEDS, color);
        FastLED.show();
      break;
      case 1:
      for(int j = 0; j < NUM_LEDS; j++){
          fill_solid(leds2, NUM_LEDS, color);
          FastLED.show();
        }
      break;
      case 2:
      for(int k = 0; k < NUM_LEDS; k++){
          fill_solid(leds3, NUM_LEDS, color);
          FastLED.show();
        } 
      break;
      case 3:
      for(int m = 0; m < NUM_LEDS; m++){
          fill_solid(leds4, NUM_LEDS, color);
          FastLED.show();
        } 
      break;
     }
    
     if(color == "Red"){
        digitalWrite(Buzzer_Pin1_POW, HIGH);
        digitalWrite(Buzzer_Pin2_POW, HIGH); 
        tone(Buzzer_Pin1_DAT, 120, 300);
        tone(Buzzer_Pin2_DAT, 120, 300);   //E6
        delay(275);
        tone(Buzzer_Pin1_DAT, 400, 650);
        tone(Buzzer_Pin2_DAT, 400, 650);   //G6
        delay(275);
        tone(Buzzer_Pin1_DAT, 165, 1250);
        tone(Buzzer_Pin2_DAT, 165, 1250);   //E7
        delay(175);
        tone(Buzzer_Pin1_DAT, 918, 700);
        tone(Buzzer_Pin2_DAT, 918, 700);   //C7
        delay(500);
     }
     else{
         digitalWrite(Buzzer_Pin1_POW, HIGH);
         digitalWrite(Buzzer_Pin2_POW, HIGH);  
         tone(Buzzer_Pin1_DAT, tones[n]);
         tone(Buzzer_Pin2_DAT, tones[n]);
     }
    
     return;
}


void turnOff(int n){
  switch(n){
      case 0:
        fill_solid(leds1, NUM_LEDS, CRGB::Black);
          FastLED.show();
      break;
      case 1:
      fill_solid(leds2, NUM_LEDS, CRGB::Black);
          FastLED.show();
      break;
      case 2:
      fill_solid(leds3, NUM_LEDS, CRGB::Black);
          FastLED.show();
      break;
      case 3:
      fill_solid(leds4, NUM_LEDS, CRGB::Black);
          FastLED.show();
      break;
     }
     noTone(Buzzer_Pin1_DAT);
     noTone(Buzzer_Pin2_DAT);
     digitalWrite(Buzzer_Pin1_POW, LOW);
     digitalWrite(Buzzer_Pin2_POW, LOW); 
}