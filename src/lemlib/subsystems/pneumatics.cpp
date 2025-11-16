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

void Matchload::calibrate() {
    matchloadV(0);
}

Wing::Wing(pros::adi::DigitalOut wingPneumatic)
    : wingPneumatic(wingPneumatic) {}

void Wing::wingV(int value) {
    wingPneumatic.set_value(value);
}

void Wing::wingChange() {
    if (wingUp) {
        wingV(0);
        wingUp = false;
    }
    else {
        wingV(1);
        wingUp = true;
    }
}

void Wing::calibrate() {
    wingV(0);
}