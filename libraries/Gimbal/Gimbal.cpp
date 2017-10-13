#include "Gimbal.h"
#include "Arduino.h"
#include "math.h"

Gimbal::Gimbal(uint8_t x, uint8_t y) {
    // Constructor
    xServo.attach(x);
    yServo.attach(y);
}

void Gimbal::reset() {
    xServo.write(xReset);
    yServo.write(yReset);
}

void Gimbal::move(char servo, bool dir) {
    switch(servo) {
        case 'x':
            if(dir) {
                if(xCurr + gimbalStep > xAngles[1]) {
                    xCurr = xAngles[1];
                    gimbalState = GIMBAL_STOP;
                }
                else {
                    xCurr += gimbalStep;
                }
            }
            else {
                if(xCurr - gimbalStep < xAngles[0]) {
                    xCurr = xAngles[0];
                    gimbalState = GIMBAL_STOP;
                }
                else {
                    xCurr -= gimbalStep;
                }
            }
            break;
        case 'y':
            if(dir) {
                if(yCurr + gimbalStep > yAngles[1]) {
                    yCurr = yAngles[1];
                    gimbalState = GIMBAL_STOP;
                }
                else {
                    yCurr += gimbalStep;
                }
            }
            else {
                if(yCurr - gimbalStep < yAngles[0]) {
                    yCurr = yAngles[0];
                    gimbalState = GIMBAL_STOP;
                }
                else {
                    yCurr -= gimbalStep;
                }
            }
            break;
    }

    xServo.write(xCurr);
    yServo.write(yCurr);
}

void Gimbal::update() {
    switch(gimbalState) {
        case GIMBAL_LEFT:
            move('x', true);
            break;
        case GIMBAL_RIGHT:
            move('x', false);
            break;
        case GIMBAL_UP:
            move('y', true);
            break;
        case GIMBAL_DOWN:
            move('y', false);
            break;
    }
}
