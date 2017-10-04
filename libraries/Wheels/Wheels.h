#ifndef Wheels_h
#define Wheels_h

#include "Arduino.h"

#define DIR_STOP 0
#define DIR_FORWARD 1
#define DIR_TURN 2


class Wheels
{
private:
    uint8_t left1;
    uint8_t left2;
    uint8_t right1;
    uint8_t right2;
    void setSpeeds(uint8_t sl1, uint8_t sl2, uint8_t sr1, uint8_t sr2);
public:
    Wheels(uint8_t l1, uint8_t l2, uint8_t r1, uint8_t r2);
    void move(char direction, float speed);
    float wheelsSpeed = 0.5f;
    byte wheelsDir = 0;
};

#endif