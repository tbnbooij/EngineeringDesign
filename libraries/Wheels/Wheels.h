#ifndef Wheels_h
#define Wheels_h

#include "Arduino.h"

#define VERT_OFFSET 20
#define HORZ_OFFSET 15

class Wheels
{
private:
    uint8_t left1;
    uint8_t left2;
    uint8_t leftEn;
    uint8_t right1;
    uint8_t right2;
    uint8_t rightEn;
    int horzSpeed = 0;
    int vertSpeed = 0;
    void setSpeeds(bool dir, uint8_t sel, uint8_t ser);
    int mapSpeed(int speed);
public:
    Wheels(uint8_t l1, uint8_t l2, uint8_t r1, uint8_t r2, uint8_t leften, uint8_t righten);
    void update(int vert, int horz);
};

#endif