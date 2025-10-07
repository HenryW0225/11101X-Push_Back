#include "main.h"

Matchload::Matchload(pros::adi::DigitalOut matchLoadPneumatic)
    : matchLoadPneumatic(matchLoadPneumatic) {}

void Matchload::matchloadV(int value) {
    matchLoadPneumatic.set_value(value);
}

void Matchload::matchloadChange() {
    if (matchloadOut) {
        matchloadV(0);
        matchloadOut = false;
    }
    else {
        matchloadV(1);
        matchloadOut = true;
    }
}

Wing::Wing(pros::adi::DigitalOut wingPneumatic)
    : wingPneumatic(wingPneumatic) {}

void Wing::wingV(int value) {
    wingPneumatic.set_value(value);
}

void Wing::wingChange() {
    if (wingUp) {
        wingV(1);
        wingUp = false;
    }
    else {
        wingV(0);
        wingUp = true;
    }
}

Park::Park(pros::adi::DigitalOut parkPneumatic)
    : parkPneumatic(parkPneumatic) {}

void Park::parkV(int value) {
    parkPneumatic.set_value(value);
}

void Park::parkChange() {
    if (parkDown) {
        parkV(1);
        parkDown = false;
    }
    else {
        parkV(0);
        parkDown = true;
    }
}
