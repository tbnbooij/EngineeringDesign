#ifndef Gimbal_h
#define Gimbal_h

#include "Arduino.h"
#include "Servo.h"

#define GIMBAL_STOP 0
#define GIMBAL_LEFT 1
#define GIMBAL_RIGHT 2
#define GIMBAL_UP 3
#define GIMBAL_DOWN 4



class Gimbal
{
private:
    Servo xServo;
    Servo yServo;
    int xReset = 73;
    int yReset = 50;
    int xAngles[2] = {0,145};
    int yAngles[2] = {0,150};
    int xCurr = 73;
    int yCurr = 50;
    int gimbalStep = 1;
public:
    Gimbal(uint8_t x, uint8_t y);
    void reset();
    void move(char servo, bool dir);
    void update();
    byte gimbalState = 0;
};

#endif