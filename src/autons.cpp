#include "main.cpp"

void odomTest() {
    chassis.setPose(22, 24, 0);
    chassis.moveToPose(24, 48, 45, 5000, {.lead = 0.6});

}

void qualLeft();
void qualRight();
void elimLeft();
void elimRight();
void soloWinPoint();