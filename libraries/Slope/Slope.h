#ifndef Slope_h
#define Slope_h

#include "Arduino.h"
#include "Servo.h"

#define SLOPE_STOP 0
#define SLOPE_UP 1
#define SLOPE_DOWN 2

class Slope
{
private:
    Servo slopeServo;
    uint8_t slopeCurr;
    uint8_t slopeReset;
    uint8_t slopeStep = 2;
    uint8_t slopeAngles[2] = {0,180};
public:
    Slope(uint8_t pin);
    void move(bool dir);
    void reset();
    void update();
    byte slopeState = 0;
};

#endif