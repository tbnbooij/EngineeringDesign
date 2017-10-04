#include "Slope.h"
#include "Arduino.h"
#include "math.h"

Slope::Slope(uint8_t pin) {
    slopeServo.attach(pin);
}

void Slope::move(bool dir) {
    slopeServo.write(slopeCurr += (dir ? slopeStep : -slopeStep));
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