#include "Slope.h"
#include "Arduino.h"
#include "math.h"

Slope::Slope(uint8_t pin) {
    slopeServo.attach(pin);
}

void Slope::move(bool dir) {
    if(dir) {
        if(slopeCurr + slopeStep > slopeAngles[1]) {
            slopeCurr = slopeAngles[1];
            slopeState = SLOPE_STOP;
        }
        else {
            slopeCurr += slopeStep;
        }
    }
    else {
        if(slopeCurr - slopeStep < slopeAngles[0]) {
            slopeCurr = slopeAngles[0];
            slopeState = SLOPE_STOP;
        }
        else {
            slopeCurr -= slopeStep;
        }
    }
    slopeServo.write(slopeCurr);
}

void Slope::reset() {
    slopeServo.write(slopeReset);
}

void Slope::update() {
    switch(slopeState) {
        case SLOPE_UP:
            move(true);
            break;
        case SLOPE_DOWN:
            move(false);
            break;
    }
}