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
            if(dir) {
                if(leftCurr + doorStep > leftAngles[1]) {
                    leftCurr = leftAngles[1];
                    leftState = DOOR_STOP;
                }
                else {
                    leftCurr += doorStep;
                }
            }
            else {
                if(leftCurr - doorStep < leftAngles[0]) {
                    leftCurr = leftAngles[0];
                    leftState = DOOR_STOP;
                }
                else {
                    leftCurr -= doorStep;
                }
            }
            break;
        case 'r':
            if(dir) {
                if(rightCurr + doorStep > rightAngles[1]) {
                    rightCurr = rightAngles[1];
                    rightState = DOOR_STOP;
                }
                else {
                    rightCurr += doorStep;
                }
            }
            else {
                if(rightCurr - doorStep < rightAngles[0]) {
                    rightCurr = rightAngles[0];
                    rightState = DOOR_STOP;
                }
                else {
                    rightCurr -= doorStep;
                }
            }
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