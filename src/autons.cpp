#include "main.h"

void simpleQual() {
    chassis.setPose(-2, -7.75, 0);
    chassis.moveToPoint(-2, 21, 5000,{.minSpeed = 5, .earlyExitRange = 1});
    matchload.matchloadV(1);
    chassis.turnToPoint(-24, 23, 5000, {.minSpeed = 5, .earlyExitRange = 1});
    intake.intakeBlock();
    chassis.moveToPoint(-11.5, 23, 1120, {.maxSpeed = 85, .minSpeed = 55});
    pros::delay(1125);
    chassis.moveToPoint(20.25, 23, 1500, {.forwards = false, .maxSpeed = 110});
    pros::delay(1000);
    intake.scoreHighGoal();
    pros::delay(1250);
    chassis.moveToPoint(10, 23, 5000, {.minSpeed = 10, .earlyExitRange = 1});
    chassis.moveToPoint(10, 10, 5000, {.minSpeed = 10, .earlyExitRange = 1});
    intake.stopIntake();
    intake.intakeBlock();
    matchload.matchloadV(0);
    chassis.moveToPoint(27, -2, 1250);
    pros::delay(400);
    matchload.matchloadV(1);
    chassis.turnToPoint(0, 29.5, 1500, {.minSpeed = 5});
    chassis.moveToPoint(37.5, -16.5, 1000, {.forwards = false, .maxSpeed = 40});
    intake.outtakeBlock();
    pros::delay(300);
    intake.stopIntake();
    intake.intakePneumaticV(1);
    intake.scoreHighGoal();
    pros::delay(4000);
    intake.stopIntake();
    matchload.matchloadV(0);
    chassis.moveToPoint(24, 0, 1800, {.minSpeed = 10, .earlyExitRange = 1});
    intake.scoreHighGoal();
    pros::delay(125);
    intake.stopIntake();
    intake.intakePneumaticV(0);
    pros::delay(100);
    intake.intakeBlock();
    chassis.moveToPoint(0, 24, 5000);
    chassis.turnToPoint(-24, 24, 5000);
}

void leftElim() {
    chassis.setPose(9.5, 1.5, 0);
    intake.intakeBlock();
    chassis.moveToPoint(-0.75, 26, 4000, {.maxSpeed = 95, .minSpeed = 10, .earlyExitRange = 1});
    pros::delay(500);
    matchload.matchloadV(1);
    chassis.turnToPoint(-24, 0, 2000,{.minSpeed = 10, .earlyExitRange = 1});
    chassis.moveToPoint(-24, 0, 3000,{.minSpeed = 10, .earlyExitRange = 1});
    chassis.turnToPoint(-23, -24, 2000,{.minSpeed = 10, .earlyExitRange = 1});
    chassis.moveToPoint(-23, -13.5, 1150, {.maxSpeed = 40, .minSpeed = 20, .earlyExitRange = 1});
    pros::delay(1150);
    chassis.moveToPoint(-23.5, 22.25, 1600, {.forwards = false, .maxSpeed = 60, .minSpeed = 10, .earlyExitRange = 1});
    pros::delay(1100);
    matchload.matchloadV(0);
    intake.scoreHighGoal();
    pros::delay(2100);
    intake.stopIntake();
    chassis.moveToPoint(-12.5, 11, 3000, {.minSpeed = 20, .earlyExitRange = 1});
    chassis.turnToPoint(-12.5, 36, 2000, {.forwards = false, .minSpeed = 20, .earlyExitRange = 1});
    chassis.moveToPoint(-12.5, 36, 2000, {.forwards = false, .maxSpeed = 65, .minSpeed = 60, .earlyExitRange = 1});
}

void rightElim() {
    chassis.setPose(-9.5, 1.5, 0);
    intake.intakeBlock();
    chassis.moveToPoint(0.75, 26, 4000, {.maxSpeed = 95, .minSpeed = 10, .earlyExitRange = 1});
    pros::delay(500);
    matchload.matchloadV(1);
    chassis.turnToPoint(24, 0, 2000,{.minSpeed = 10, .earlyExitRange = 1});
    chassis.moveToPoint(24, 0, 3000,{.minSpeed = 10, .earlyExitRange = 1});
    chassis.turnToPoint(23, -24, 2000,{.minSpeed = 10, .earlyExitRange = 1});
    chassis.moveToPoint(23, -13.5, 1150, {.maxSpeed = 40, .minSpeed = 20, .earlyExitRange = 1});
    pros::delay(1150);
    chassis.moveToPoint(23.5, 22.25, 1600, {.forwards = false, .maxSpeed = 60, .minSpeed = 10, .earlyExitRange = 1});
    pros::delay(1100);
    matchload.matchloadV(0);
    intake.scoreHighGoal();
    pros::delay(2100);
    intake.stopIntake();
    chassis.moveToPoint(12.5, 11, 3000, {.minSpeed = 20, .earlyExitRange = 1});
    chassis.turnToPoint(12.5, 36, 2000, {.forwards = false, .minSpeed = 20, .earlyExitRange = 1});
    chassis.moveToPoint(12.5, 36, 2000, {.forwards = false, .maxSpeed = 65, .minSpeed = 60, .earlyExitRange = 1});
}

void soloWinPoint() {
        chassis.setPose(9.5, 1.5, 0);
        intake.intakeBlock();
        chassis.moveToPoint(-0.75, 26, 4000, {.maxSpeed = 95, .minSpeed = 20, .earlyExitRange = 2});
        //pros::delay(475);
        //matchload.matchloadV(1);
        chassis.turnToPoint(15.25, 38, 2000, {.forwards = false, .minSpeed = 35, .earlyExitRange = 4});
        chassis.moveToPoint(15.25, 38, 1100, {.forwards = false, .minSpeed = 25, .earlyExitRange = 3});
        chassis.turnToPoint(-21, -2, 2000,{.minSpeed = 25, .earlyExitRange = 4});
        pros::delay(150);
        intake.scoreMiddleHigh();
        pros::delay(200);
        intake.stopIntake();
        chassis.moveToPoint(-21, -2, 3000,{.minSpeed = 30, .earlyExitRange = 2});
        matchload.matchloadV(1);
        intake.intakeBlock();
        chassis.turnToPoint(-23, -13.5, 2000,{.minSpeed = 30, .earlyExitRange = 3});
        chassis.moveToPoint(-22.75, -13.5, 1150, {.maxSpeed = 40, .minSpeed = 20, .earlyExitRange = 1});
        pros::delay(1150);
        chassis.moveToPoint(-22.75, 22, 1600, {.forwards = false, .maxSpeed = 70, .minSpeed = 35, .earlyExitRange = 1});
        pros::delay(1000);
        matchload.matchloadV(0);
        intake.scoreHighGoal();
        pros::delay(1200);
        intake.stopIntake();
        chassis.turnToPoint(36, 24, 2000, {.minSpeed = 35, .earlyExitRange = 4});
        intake.intakeBlock();
        chassis.moveToPoint(34, 24, 2000, { .minSpeed = 40, .earlyExitRange = 2});
        chassis.moveToPoint(48, 25, 3000, {.maxSpeed = 40, .minSpeed = 20, .earlyExitRange = 2}); 
        chassis.turnToPoint(68.5, -2, 2000,{.minSpeed = 30, .earlyExitRange = 4});
        chassis.moveToPoint(68.5, -2, 3000,{.minSpeed = 30, .earlyExitRange = 2});
        chassis.turnToPoint(69.75, -24, 2000,{.minSpeed = 30, .earlyExitRange = 2});
        matchload.matchloadV(1);
        chassis.moveToPoint(70, -14, 1150, {.maxSpeed = 50, .minSpeed = 35, .earlyExitRange = 1});
        pros::delay(1150);
        chassis.moveToPoint(71.75, 22.25, 1600, {.forwards = false, .maxSpeed = 70, .minSpeed = 35, .earlyExitRange = 1});
        pros::delay(1000);
        intake.scoreHighGoal();
        matchload.matchloadV(0);

        
        /*chassis.moveToPoint(-23.5, 8, 3000, {.minSpeed = 10, .earlyExitRange = 1});
        chassis.turnToPoint(48, 24, 2000, {.minSpeed = 10, .earlyExitRange = 1});
        chassis.moveToPoint(48, 24, 3000, {.minSpeed = 10, .earlyExitRange = 1});
        intake.intakeBlock();
        pros::delay(1100);
        matchload.matchloadV(1);
        pros::delay(100);
        chassis.turnToPoint(72, 0, 2000, {.minSpeed = 10, .earlyExitRange = 1});
        chassis.moveToPoint(72, 0, 3000,{.minSpeed = 10, .earlyExitRange = 1});
        chassis.turnToPoint(71, -24, 2000,{.minSpeed = 10, .earlyExitRange = 1});
        chassis.moveToPoint(71, -13.5, 1150, {.maxSpeed = 40, .minSpeed = 20, .earlyExitRange = 1});
        pros::delay(1150);
        chassis.moveToPoint(71, 21.5, 1600, {.forwards = false, .maxSpeed = 60, .minSpeed = 10, .earlyExitRange = 1});
        pros::delay(1100);
        matchload.matchloadV(0);
        intake.scoreHighGoal();
    /*chassis.setPose(-2, -7.75, 0);
    chassis.moveToPoint(-2, 21, 5000,{.minSpeed = 5, .earlyExitRange = 1});
    matchload.matchloadV(1);
    chassis.turnToPoint(-24, 23, 5000, {.minSpeed = 5, .earlyExitRange = 1});
    intake.intakeBlock();
    chassis.moveToPoint(-11.5, 23, 1120, {.maxSpeed = 85, .minSpeed = 55});
    pros::delay(1000);
    chassis.moveToPoint(20.25, 23, 1500, {.forwards = false, .maxSpeed = 110});
    pros::delay(800);
    intake.scoreHighGoal();
    pros::delay(1000);
    chassis.moveToPoint(10, 23, 5000, {.minSpeed = 10, .earlyExitRange = 1});
    chassis.moveToPoint(10, 10, 5000, {.minSpeed = 10, .earlyExitRange = 1});
    intake.stopIntake();
    intake.intakeBlock();
    matchload.matchloadV(0);
    chassis.moveToPoint(27, -1.25, 1250);
    pros::delay(375);
    matchload.matchloadV(1);
    chassis.turnToPoint(0, 29.5, 1500, {.minSpeed = 5});
    chassis.moveToPoint(37.5, -16.5, 1000, {.forwards = false, .maxSpeed = 40});
    intake.outtakeBlock();
    pros::delay(300);
    intake.stopIntake();
    intake.intakePneumaticV(1);
    intake.scoreMiddleGoal();
    pros::delay(1100);
    intake.stopIntake();
    matchload.matchloadV(0);
    chassis.moveToPoint(24, 0, 1800, {.minSpeed = 10, .earlyExitRange = 1});
    intake.scoreHighGoal();
    pros::delay(125);
    intake.stopIntake();
    intake.intakePneumaticV(0);
    pros::delay(100);
    intake.intakeBlock();
    chassis.turnToPoint(20, -45.5, 2000, {.maxSpeed = 80, .minSpeed = 5});
    chassis.moveToPoint(20, -45.5, 1000, {.minSpeed = 10, .earlyExitRange = 1});
    pros::delay(745);
    matchload.matchloadV(1);
    chassis.turnToPoint(0, -67.25, 2000, {.minSpeed = 10, .earlyExitRange = 1});
    chassis.moveToPoint(0, -67.25, 3000, {.minSpeed = 10, .earlyExitRange = 1});
    chassis.turnToPoint(-20, -66.5, 2000, {.minSpeed = 20, .earlyExitRange = 1});
    matchload.matchloadV(0);
    chassis.moveToPoint(19, -69, 5000, {.forwards = false, .maxSpeed = 50, .minSpeed = 10, .earlyExitRange = 1});
    pros::delay(340);
    intake.scoreHighGoal();
    pros::delay(700);
    chassis.moveToPoint(17, -68, 1000, {.minSpeed = 10, .earlyExitRange = 1});
    */
}

void skills() {
    chassis.setPose(15, -52, 90);
    chassis.moveToPoint(48, -55, 3000,{.maxSpeed = 40});
    /*matchload.matchloadV(1);
    wing.wingV(1);
    chassis.turnToPoint(47, -62, 5000, {.minSpeed = 5, .earlyExitRange = 1});
    intake.intakeBlock();
    chassis.moveToPoint(47, -62, 2500, {.maxSpeed = 40, .minSpeed = 20, .earlyExitRange = 1});*/
  
}