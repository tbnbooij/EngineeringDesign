#ifndef Wheels_h
#define Wheels_h

#include "Arduino.h"

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
    void setSpeeds(uint8_t sl1, uint8_t sl2, uint8_t sr1, uint8_t sr2);
public:
    Wheels(uint8_t l1, uint8_t l2, uint8_t r1, uint8_t r2, uint8_t leften, uint8_t righten);
    void update(uint8_t vert, uint8_t horz);
};

#endif