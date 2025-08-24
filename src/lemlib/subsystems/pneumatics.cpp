#include "lemlib/subsystems/pneumatics.hpp"
#include "api.h"
#include "main.h"

Matchload::Matchload(pros::adi::DigitalOut matchloadpneumatic)
    : matchloadpneumatic(matchloadpneumatic) {}

void Matchload::matchload_v(int value) {
    matchloadpneumatic.set_value(value);
}
