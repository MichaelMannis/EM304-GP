#include "motor.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//using existing library
static Adafruit_PWMServoDriver pca;

//static variables
unsigned long motor::time=0;
int motor::x=0;
float motor::serialData=0;
bool motor::serialRecieved=false;
bool motor::timer=false;


//constructors
motor::motor(int _pin) {
  pin=_pin;
}
motor::motor(int _IN1, int _IN2, int _IN3, int _IN4) {
  IN1=_IN1;
  IN2=_IN2;
  IN3=_IN3;
  IN4=_IN4;
}

//setup board
void motor::begin() {
  pca.begin();
  pca.setPWMFreq(50);
}


//move servo
void motor::moveServo(int angle, int lag) {
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


//move stepper
void motor::moveAntiClockwise(float seconds) {
  if (seconds<0) {
    seconds=0;
  }
  for (int i=0; i<(124*(seconds)); i+=1) {     //This for loop takes 1 second to complete when seconds=1.
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(2);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(2);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    delay(2);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(2);
  }
}


void motor::moveClockwise(float seconds) {
  if (seconds<0) {
    seconds=0;
  }
  for (int i=0; i<(124*(seconds)); i+=1) {     //This for loop takes 1 second to complete when seconds=1.
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(2);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    delay(2);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(2);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(2);
  }
}



//take serial data
void motor::readSerial(){
  if (Serial.available()>0) {
    serialData=Serial.parseFloat();
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
void motor::timeSerial(int ms, bool trueFalse) {
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
