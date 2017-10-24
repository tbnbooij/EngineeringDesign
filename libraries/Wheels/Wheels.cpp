#include "Wheels.h"
#include "Arduino.h"
#include "math.h"

Wheels::Wheels(uint8_t l1, uint8_t l2, uint8_t r1, uint8_t r2, uint8_t leften, uint8_t righten) {
    left1 = l1;
    left2 = l2;
    right1 = r1;
    right2 = r2;
    leftEn = leften;
    rightEn = righten;

    pinMode(left1, OUTPUT);
    pinMode(left2, OUTPUT);
    pinMode(right1, OUTPUT);
    pinMode(right2, OUTPUT);
    pinMode(leftEn, OUTPUT);
    pinMode(rightEn, OUTPUT);
}

void Wheels::setSpeeds(bool dir, uint8_t sel, uint8_t ser) {
    digitalWrite(left1, (dir ? HIGH : LOW));
    digitalWrite(left2, (dir ? LOW : HIGH));
    analogWrite(leftEn, sel);
    digitalWrite(right1, (dir ? HIGH : LOW));
    digitalWrite(right2, (dir ? LOW : HIGH));
    analogWrite(rightEn, ser);
}

int Wheels::mapSpeed(int speed) {
    if (speed > 50)
    {
        return (int) (((float) map(speed, 50, 100, 50 + VERT_OFFSET, 100))/100.0 * 255.0);
    }
    
    if (speed < 50)
    {
        return (int) (((float) map(speed, 0, 50, 0, 50 - VERT_OFFSET))/100.0 * 255.0);
    }

    return 0;
}

void Wheels::update(int vert, int horz) {
    float horzFactor = 1.0 - ((float) abs(50 - horz))/50.0;

    if (horz > 50 + HORZ_OFFSET)
    {
        setSpeeds(vert >= 50, mapSpeed(vert), (int) mapSpeed(vert) * horzFactor);
    }
    else if (horz < 50 - HORZ_OFFSET)
    {
        setSpeeds(vert >= 50, (int) mapSpeed(vert) * horzFactor, mapSpeed(vert));
    }
    else
    {
        setSpeeds(vert >= 50, mapSpeed(vert), mapSpeed(vert));
    }

}