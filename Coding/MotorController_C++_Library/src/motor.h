#ifndef motor_H
#define motor_H

#include <Arduino.h>

class motor {
  private:
  int pin;
  int IN1;
  int IN2;
  int IN3;
  int IN4;
  static unsigned long time;
  static int x;
  int last_position=1600;
  int target_position;
  public:
  static void begin();
  static bool timer;
  static float serialData;
  static bool serialRecieved;
  motor(int _pin);
  motor(int _IN1, int _IN2, int _IN3, int _IN4);
  void moveServo(int angle, int lag);
  void moveClockwise(float seconds);
  void moveAntiClockwise(float seconds);
  static void readSerial();
  static void timeSerial(int ms, bool trueFalse);
};

#endif