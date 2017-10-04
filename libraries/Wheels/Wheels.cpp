#include "Wheels.h"
#include "Arduino.h"
#include "math.h"

Wheels::Wheels(uint8_t l1, uint8_t l2, uint8_t r1, uint8_t r2) {
    left1 = l1;
    left2 = l2;
    right1 = r1;
    right2 = r2;

    pinMode(left1, OUTPUT);
    pinMode(left2, OUTPUT);
    pinMode(right1, OUTPUT);
    pinMode(right2, OUTPUT);
}

void Wheels::setSpeeds(uint8_t sl1, uint8_t sl2, uint8_t sr1, uint8_t sr2) {
    analogWrite(left1, sl1);
    analogWrite(left2, sl2);
    analogWrite(right1, sr1);
    analogWrite(right2, sr2);
}

void Wheels::move(char direction, float speed) {
    uint8_t currSpeed = (uint8_t) speed*255;
    switch(direction) {
        case 's':
            // Move in straight line
            setSpeeds(currSpeed, 0, currSpeed, 0);
            break;
        case 't':
            // Rotate
            setSpeeds(-currSpeed, 0, 0, currSpeed);
            break;
        case 'x':
            // Stop
            setSpeeds(0, 0, 0, 0);
            break;
    }
}

void Wheels::update() {
    switch(wheelsDir) {
        case DIR_STOP:
            move('x', wheelsSpeed);
            break;
        case DIR_FORWARD:
            move('s', wheelsSpeed);
            break;
        case DIR_TURN:
            move('t', wheelsSpeed);
            break;
    }
}