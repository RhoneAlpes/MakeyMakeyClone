/*
  JP Redonnet - October 20, 2016
  MakeyMakey clone
  version 0.1
 */
 
#include "Keyboard.h"
#include "Mouse.h"

//you can try to decrease AVERAGE and increase THRESOLD 
// Sampling time: 20 ms Sensitivity: 244 mV
//if you decrease the AVERAGE value you will have to increase the THRESHOLD value
#define AVERAGE 200 //sampling loop for low pass filter (AVERAGE value x 0.1ms)
#define THRESHOLD_1 20 //increase value to decrease sensitivity (THRESOLD value / 1023 x 5V)
#define THRESHOLD_2 50 //increase value to decrease sensitivity (THRESOLD value / 1023 x 5V)
#define THRESHOLD_3 70 //increase value to decrease sensitivity (THRESOLD value / 1023 x 5V)

#define KEYPRESSTIME 50 //key pressed duration in ms (and led turned on)

float left,right,up,down,space,leftclick,keyreturn,keyD,keyE,average;
boolean keyleftflag,keyrightflag,keyupflag,keydownflag,clickleftflag,keyspaceflag,keyreturnflag;
int threshold;

//Read analog input
//Moving averaging values (low-pass filter)
float analogReadPin(int pin, float PreviousValue) {
  float inputValue=PreviousValue;
  for(int i=0;i<AVERAGE;i++)
    inputValue+=analogRead(pin);
  return(inputValue/(AVERAGE+1));
}

//Read 14,15,16 pins
//Set sensitivity
void configure() {
  //todo  read pins 14,15,16 to setup threshold value
  threshold=THRESHOLD_2;
}

void setup() {
    keyleftflag=keyrightflag=keyupflag=keydownflag=keyreturnflag=0;
    clickleftflag=keyspaceflag=0;
    configure();
    pinMode(7, OUTPUT);
    //calibrate
    left=right=up=down=0;
    space=leftclick=keyreturn=keyD,keyE=0;
    for(int j=0;j<100;j++) { 
      digitalWrite(7, HIGH);
      left=analogReadPin(A0,left);
      digitalWrite(7, LOW);
      right=analogReadPin(A1,right);
      digitalWrite(7, HIGH);
      up=analogReadPin(A2,up);
      digitalWrite(7, LOW);
      down=analogReadPin(A3,down);
      digitalWrite(7, HIGH);
      space=analogReadPin(A8,space);
      digitalWrite(7, LOW);
      leftclick=analogReadPin(A9,leftclick);
      digitalWrite(7, HIGH);
      keyreturn=analogReadPin(A6,keyreturn);
      digitalWrite(7, LOW);
      keyD=analogReadPin(A7,keyD);
      digitalWrite(7, HIGH);
      keyE=analogReadPin(A10,keyE);
    }
    // initialize keyboard and mouse emulation:
    Keyboard.begin();
    Mouse.begin();
    delay(100);
}

// the loop function runs over and over again forever
void loop() {
  
  left=analogReadPin(A0,left);
  right=analogReadPin(A1,right);
  up=analogReadPin(A2,up);
  down=analogReadPin(A3,down);
  space=analogReadPin(A8,space);
  leftclick=analogReadPin(A9,leftclick);
  keyreturn=analogReadPin(A6,keyreturn);
  keyD=analogReadPin(A7,keyD);
  keyE=analogReadPin(A10,keyE);

  //moving average
  average=average/2+(left+right+up+down+space+leftclick+keyreturn+keyD+keyE)/18;
  average+=threshold;
  
  if (left > average) 
  {
    Keyboard.press(KEY_LEFT_ARROW);
    pinMode(18, OUTPUT);
    digitalWrite(18,HIGH);
    keyleftflag=1;
    delay(KEYPRESSTIME);
    digitalWrite(18,LOW);
    pinMode(18, INPUT);
    delay(1);
  }
  else if (keyleftflag)
  {
     Keyboard.release(KEY_LEFT_ARROW);
     keyleftflag=0;
  }
  
  if (right > average) 
  {
    Keyboard.press(KEY_RIGHT_ARROW);
    pinMode(19, OUTPUT);
    digitalWrite(19,HIGH);
    keyrightflag=1;
    delay(KEYPRESSTIME);
    digitalWrite(19,LOW);
    pinMode(19, INPUT);
    delay(1);
  }
  else if (keyrightflag)
  {
     Keyboard.release(KEY_RIGHT_ARROW);
     keyrightflag=0;
  }
  
  if (up > average) 
  {
    Keyboard.press(KEY_UP_ARROW);
    pinMode(20, OUTPUT);
    digitalWrite(20,HIGH);
    keyupflag=1;
    delay(KEYPRESSTIME);
    digitalWrite(20,LOW);
    pinMode(20, INPUT);
    delay(1);
  }
  else if (keyupflag)
  {
     Keyboard.release(KEY_UP_ARROW);
     keyupflag=0;
  }
  
  if (down > average) 
  {
    Keyboard.press(KEY_DOWN_ARROW);
    pinMode(21, OUTPUT);
    digitalWrite(21,HIGH);
    keydownflag=1;
    delay(KEYPRESSTIME);
    digitalWrite(21,LOW);
    pinMode(21, INPUT);
    delay(1);
  }
  else if (keydownflag)
  {
     Keyboard.release(KEY_DOWN_ARROW);
     keydownflag=0;
  }
  
  if (space > average) 
  {
    Keyboard.press(' ');
    pinMode(8, OUTPUT);
    digitalWrite(8,HIGH);
    keyspaceflag=1;
    delay(KEYPRESSTIME);
    digitalWrite(8,LOW);
    pinMode(8, INPUT);
    delay(1);
  }
    else if (keyspaceflag)
  {
     Keyboard.release(' ');
     keyspaceflag=0;
  }
  
  if (leftclick > average) 
  {
    Mouse.press(MOUSE_LEFT);
    pinMode(9, OUTPUT);
    digitalWrite(9,HIGH);
    clickleftflag=1;
    delay(KEYPRESSTIME);
    digitalWrite(9,LOW);
    pinMode(9, INPUT);
    delay(1);
  }
  else if (clickleftflag)
  {
     Mouse.release(MOUSE_LEFT);
     clickleftflag=0;
  }
  
  if (keyreturn > average) 
  {
    Keyboard.press(KEY_RETURN);
    pinMode(4, OUTPUT);
    digitalWrite(4,HIGH);
    keyreturnflag=1;
    delay(KEYPRESSTIME);
    digitalWrite(4,LOW);
    pinMode(4, INPUT);
    delay(1);
  }
  else if (keyreturnflag)
  {
     Keyboard.release(KEY_RETURN);
     keyreturnflag=0;
  }
  
  if (keyD > average) 
  {
    Keyboard.press('W');
    pinMode(6, OUTPUT);
    digitalWrite(6,HIGH);
    delay(KEYPRESSTIME);
    Keyboard.release('W');
    digitalWrite(6,LOW);
    pinMode(6, INPUT);
    delay(10);
  }  
  if (keyE > average) 
  {
    Keyboard.press('T');
    pinMode(10, OUTPUT);
    digitalWrite(10,HIGH);
    delay(KEYPRESSTIME);
    Keyboard.release('T');
    digitalWrite(10,LOW);
    pinMode(10, INPUT);
    delay(10);
  }  
}
