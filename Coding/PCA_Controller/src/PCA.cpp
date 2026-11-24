#include "PCA.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//using existing library
static Adafruit_PWMServoDriver pca;

//static variables
unsigned long PCA::time=0;
int PCA::x=0;
int PCA::angle=0;
bool PCA::serialRecieved=false;
bool PCA::timer=false;

//constructor
PCA::PCA(int _pin) {
  pin=_pin;
}

//setup board
void PCA::begin() {
  pca.begin();
  pca.setPWMFreq(50);
}

//move servo
void PCA::moveServo(int angle, int lag) {
  angle=constrain(angle, 0, 180);
  target_position=map(angle, 0, 180, 2600, 600);
  if (last_position>target_position) {
    for (int i=last_position; i>target_position ; i-=10){
      pca.writeMicroseconds(pin, i);
      delay(lag);
    }
  }
  if (last_position<target_position) {
    for (int i=last_position; i<target_position; i+=10){
      pca.writeMicroseconds (pin, i);
      delay(lag);
    }
  }
  pca.writeMicroseconds(pin, target_position);
  last_position=target_position;
}

//read angle from serial
void PCA::readSerial(){
  if (Serial.available()>0) {
    angle=Serial.parseInt();
    while (Serial.available()>0) {
      Serial.read();
    }
    serialRecieved=true;
  }
  else{
  serialRecieved=false;
  }
}

//time between serial inputs
void PCA::timeSerial(int ms, bool trueFalse) {
  if (trueFalse) {
    time=millis();
    x=1;
    timer=false;
  }
  if ((millis()-time)>=ms && x==1) {  
    x=0;
    timer=true;
    }
}

