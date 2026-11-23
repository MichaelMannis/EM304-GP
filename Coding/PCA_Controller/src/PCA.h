#ifndef PCA_H
#define PCA_H

#include <Arduino.h>

class PCA {
  private:
  int pin;
  static unsigned long time;
  static int x;
  int last_position=1600;
  int target_position;
  public:
  static void begin();
  static bool timer;
  static int angle;
  static bool serialRecieved;
  PCA(int _pin);
  void moveServo(int serialData, int lag);
  static void readSerial();
  static void timeSerial(int ms, bool trueFalse);
};


#endif
