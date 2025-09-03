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
}