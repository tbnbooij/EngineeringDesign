#include "Doors.h"
#include "Arduino.h"
#include "math.h"

Doors::Doors(uint8_t left, uint8_t right) {
    leftServo.attach(left);
    rightServo.attach(right);
}

void Doors::reset() {
    leftServo.write(leftReset);
    rightServo.write(rightReset);
}

void Doors::move(char door, bool dir) {
    switch(door) {
        case 'l':
            // ONLY the left door
            leftCurr += (dir ? doorStep : -doorStep);
            break;
        case 'r':
            // ONLY the right door
            rightCurr += (dir ? doorStep : -doorStep);
            break;
    }

    leftServo.write(leftCurr);
    rightServo.write(rightCurr);
}

void Doors::update() {
    switch(leftState) {
        case DOOR_OUT:
            move('l', true);
            break;
        case DOOR_IN:
            move('l', false);
            break;
    }

    switch(rightState) {
        case DOOR_OUT:
            move('r', true);
            break;
        case DOOR_IN:
            move('r', false);
            break;
    }
}