/*#pragma once
#include "main.cpp"

void odomTest() {
    chassis.moveToPoint(0, 48, 5000);
    //pros::delay(500);
    chassis.turnToPoint(48, 48, 5000);
    chassis.moveToPoint(48, 48, 5000);
    chassis.moveToPoint(0, 48, 5000, {.forwards = false}); 
    chassis.turnToPoint(0, 96, 5000);
    chassis.moveToPoint(0, 0, 5000, {.forwards = false});
    //chassis.moveToPoint(48, 0, 5000);
    //chassis.turnToPoint(0, 0, 5000);
    //chassis.moveToPoint(0, 0, 5000);
    //chassis.turnToPoint(0, 48, 5000);
    chassis.moveToPose(24, 48, 45, 5000, {.lead = 0.6});


}

void qualLeft();
void qualRight();
void elimLeft() {
    intake.intake_block();
    chassis.moveToPose(0, 20, 40, 5000, {.lead = 0.6});
    matchload.matchload_v(1);
    pros::delay(1000);
    matchload.matchload_v(0);
    chassis.moveToPose(20, 40, 70, 5000, {.lead = 0.6});
    matchload.matchload_v(1);
    pros::delay(1000);
    matchload.matchload_v(0);
    chassis.moveToPose(24, 6, 180, 5000, {.lead = 0.6});
    matchload.matchload_v(1);
    chassis.moveToPoint(24, -12, 5000, {.forwards = false, .maxSpeed = 50});
    pros::delay(1500);
    chassis.moveToPoint(24, 14, 5000, {.forwards = false});
    chassis.moveToPoint(24, 18, 5000, {.forwards = false, .maxSpeed = 50});
    pros::delay(50);
    intake.score_high_goal();
    pros::delay(4000);
    matchload.matchload_v(0);
    chassis.moveToPoint(24, 12, 5000);
    chassis.moveToPoint(24, 18, 5000, {.forwards = false});
}

void elimRight();
void soloWinPoint();*/