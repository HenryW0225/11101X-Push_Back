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
    chassis.moveToPoint(-1, 26, 5000, {.maxSpeed = 95});
    pros::delay(500);
    matchload.matchloadV(1);
    pros::delay(300);
    matchload.matchloadV(0);
    pros::delay(200);
    chassis.turnToPoint(-23, 0, 5000);
    chassis.moveToPoint(-23, 0, 5000);
    chassis.turnToPoint(-23, -24, 1000);
    matchload.matchloadV(1);
    chassis.moveToPoint(-25, -24, 1300, {.maxSpeed = 75, .minSpeed = 55});
    pros::delay(1200);
    chassis.moveToPoint(-24, 24, 1500, {.forwards = false, .maxSpeed = 110});
    pros::delay(1100);
    intake.scoreHighGoal();
}

void rightElim() {
    chassis.setPose(-9, 1.5, 0);
    intake.intakeBlock();
    chassis.moveToPoint(0, 27, 5000, {.maxSpeed = 45});
    pros::delay(950);
    matchload.matchloadV(1);
    pros::delay(100);
    chassis.moveToPoint(17.75, 41, 5000, {.maxSpeed = 70});
    pros::delay(150);
    matchload.matchloadV(0);
    pros::delay(400);
    chassis.moveToPoint(12, 12, 5000, {.forwards = false});
    chassis.moveToPoint(24, 8, 1000, {.forwards = false});
    chassis.turnToPoint(22, -24, 1000);
    chassis.moveToPoint(24, 24, 1200, {.forwards = false, .maxSpeed = 60});
    pros::delay(500);
    intake.outtakeBlock();
    pros::delay(200);
    intake.scoreHighGoal();
    pros::delay(2250);
    intake.stopIntake();
    intake.intakeBlock();
    matchload.matchloadV(1);
    chassis.moveToPoint(22, -15, 1250, {.maxSpeed = 55});
    pros::delay(1500);
    chassis.moveToPoint(24, 24, 1000, {.forwards = false, .maxSpeed = 80});
    pros::delay(900);
    intake.scoreHighGoal();
    pros::delay(1350);
    chassis.moveToPoint(24, 12, 1000, {.minSpeed = 10, .earlyExitRange = 3});
    chassis.moveToPoint(24, 24, 1000, {.forwards = false, .minSpeed = 70});
}

void soloWinPoint() {
    chassis.setPose(-2, -7.75, 0);
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
}

void skills() {
    chassis.setPose(-2, -7.75, 0);
    chassis.moveToPoint(-2, 21, 5000,{.minSpeed = 5, .earlyExitRange = 1});
    matchload.matchloadV(1);
    chassis.turnToPoint(-24, 23, 5000, {.minSpeed = 5, .earlyExitRange = 1});
    intake.intakeBlock();
    chassis.moveToPoint(-11.5, 23, 1120, {.maxSpeed = 85, .minSpeed = 55});
    pros::delay(6000);
    chassis.moveToPoint(20.25, 23, 1500, {.forwards = false, .maxSpeed = 110});
    pros::delay(5000);
    intake.scoreHighGoal();
}