#ifndef Doors_h
#define Doors_h

#include "Arduino.h"
#include "Servo.h"

#define DOOR_STOP 0
#define DOOR_OUT 1
#define DOOR_IN 2

class Doors
{
private:
    Servo leftServo;
    Servo rightServo;
    int leftReset = 90;
    int rightReset = 90;
    int leftCurr = 90;
    int rightCurr = 90;
    int doorStep = 2;
public:
    Doors(uint8_t left, uint8_t right);
    void reset();
    void move(char door, bool dir);
    void update();
    byte leftState = 0;
    byte rightState = 0;
};

#endif