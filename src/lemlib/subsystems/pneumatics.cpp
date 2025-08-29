#include "main.h"

Matchload::Matchload(pros::adi::DigitalOut matchloadpneumatic)
    : matchloadpneumatic(matchloadpneumatic) {}

void Matchload::matchload_v(int value) {
    matchloadpneumatic.set_value(value);
}

void Matchload::matchload_change() {
    if (matchload_out) {
        matchload_v(0);
        matchload_out = false;
    }
    else {
        matchload_v(1);
        matchload_out = true;
    }
}