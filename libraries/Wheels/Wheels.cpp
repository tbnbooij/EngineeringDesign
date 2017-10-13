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

void Wheels::setSpeeds(uint8_t sl1, uint8_t sl2, uint8_t sr1, uint8_t sr2, uint8_t sel, uint8_t ser) {
    digitalWrite(left1, sl1);
    digitalWrite(left2, sl2);
    analogWrite(leftEn, sel);
    digitalWrite(right1, sr1);
    digitalWrite(right2, sr2);
    analogWrite(rightEn, ser);
}

void Wheels::update(uint8_t vert, uint8_t horz) {
    float vertSpeed = float(vert - 50)/50.0;
    float horzSpeed = float(horz - 50)/50.0;

    byte vertState = (vertSpeed == 0.0 ? 0 : (vertSpeed > 0.0 ? 1 : -1));
    byte horzState = (horzState == 0.0 ? 0 : (horzSpeed > 0.0 ? 1 : -1));

    switch(vertState)
    {
        case 0:
            // Movements with no vertical velocity
            // Anything horizontal is then impossible
            setSpeeds(LOW, LOW, LOW, LOW, 0, 0);
            break;
        case -1:
            // Movements with negative vertical velocity
            switch(horzState)
            {
                case -1:
                    // Move BACKWARD and move to the LEFT
                    setSpeeds(LOW, HIGH, LOW, HIGH, (int) -255.0*vertSpeed + 255.0*horzSpeed, (int) -255.0*vertSpeed);
                    break;
                case 0:
                    // Move BACKWARD in a straight line
                    setSpeeds(LOW, HIGH, LOW, HIGH, (int) -255.0*vertSpeed, (int) -255.0*vertSpeed);
                    break;
                case 1:
                     // Move BACKWARD and move to the RIGHT
                     setSpeeds(LOW, HIGH, LOW, HIGH, (int) -255.0*vertSpeed, (int) -255.0*vertSpeed - 255.0*horzSpeed);
                    break;
            }
            break;
        case 1:
            // Movements with positive vertical velocity
            switch(horzState)
            {
                case -1:
                    // Move to the LEFT and FORWARD
                    setSpeeds(LOW, HIGH, HIGH, LOW, (int) 255.0*vertSpeed + 255.0*horzSpeed, (int) 255.0*vertSpeed);
                    break;
                case 0:
                    // Move FORWARD in a straight line
                    setSpeeds(HIGH, LOW, HIGH, LOW, (int) 255.0*vertSpeed, (int) 255.0*vertSpeed);
                    break;
                case 1:
                    // Move to the RIGHT and FORWARD
                    setSpeeds(HIGH, LOW, LOW, HIGH, (int) 255.0*vertSpeed, (int) 255.0*vertSpeed - 255.0*horzSpeed);
                    break;
            }
    }

}