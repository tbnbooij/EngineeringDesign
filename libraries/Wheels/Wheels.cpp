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

void Wheels::move(char direction, int speed) {
    float netSpeed = float(speed - 50)/50.0;
    float currSpeed = 0.0;
    uint8_t speedFront; 
    uint8_t speedBack;

    if(netSpeed > 0.0) {
        speedFront = (uint8_t) 255.0*netSpeed;
        speedBack = 0;
    }
    else if(netSpeed < 0.0) {
        speedFront = 0;
        speedBack = (uint8_t) 255.0*-1*netSpeed;
    }
    else {
        speedFront = 0;
        speedBack = 0;
    }

    switch(direction) {
        case 's':
            // Move in straight line
            setSpeeds(speedFront, speedBack, speedFront, speedBack);
            break;
        case 't':
            // Rotate
            setSpeeds(speedFront, speedBack, speedBack, speedFront);
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

void Wheels::setSpeed(int s) {
    wheelsSpeed = s;
}