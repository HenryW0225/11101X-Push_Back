#include "lemlib/chassis/odom.hpp"
#include "lemlib/subsystems/intake.hpp"
#include "lemlib/timer.hpp"
#include "main.h"
#include "pros/device.hpp"
#include "pros/rtos.hpp"
//

void odomTest() {
    /*chassis.setPose(0, 0, 0);
    pros::Task printCoordsTask([]() {
        while (true) {
            lemlib::Pose pose = chassis.getPose();
            pros::screen::print(pros::E_TEXT_MEDIUM, 0, "x: %.2f",pose.x);
            pros::screen::print(pros::E_TEXT_MEDIUM, 1, "y: %.2f", pose.y);
            pros::screen::print(pros::E_TEXT_MEDIUM, 2, "theta: %.2f", pose.theta);
            pros::delay(20);
        }
    });
    pros::delay(1000);
    //chassis.resetWithDistance(66.5);
    
    double error = chassis.resetAngleWithSelfCorrectionInches();
    while(fabs(error) > 1.0) { // 1 degree threshold
        lemlib::Pose pose = chassis.getPose();
        double targetHeading = pose.theta + error;
        chassis.turnToHeading(targetHeading, 4000, {.maxSpeed = 40, .minSpeed = 5});
        pros::delay(50);
        error = chassis.resetAngleWithSelfCorrectionInches();
    }*/
    //chassis.calibrate(true);
    chassis.setPose(0, 0, 0);
    //chassis.moveToPoint(0, 48, 5000);
    //chassis.moveToPoint(0, 48, 5000, {.forwards = false});
    chassis.turnToHeading(90, 5000);
    //chassis.moveToPoint(0, 48, 5000);
    /*chassis.setPose(0,0,0);
    chassis.moveToPoint(0, 48, 5000);
    chassis.turnToPoint(48, 48, 5000);
    chassis.moveToPoint(48, 48, 5000);
    chassis.turnToPoint(48, 0, 3000);
    chassis.moveToPoint(48, 0, 5000);
    chassis.turnToPoint(0, 0, 3000);
    chassis.moveToPoint(0, 0, 5000);
    chassis.turnToHeading(0, 3000);*/
    
}
void leftFourLongFourMiddle() {
    chassis.setPose(-18.1, -3.6, 270);
    chassis.moveToPoint(-47.4, -3.6, 1500);
    matchload.matchloadV(1);
    chassis.turnToPoint(-48.3, -12.5, 1500, {.minSpeed = 25, .earlyExitRange = 1});
    intake.intakeBlock();
    chassis.moveToPoint(-48.3, -12.5, 925, {.maxSpeed = 75, .minSpeed = 40});
    pros::delay(925);
    //matchload #1
    chassis.moveToPoint(-48.5, 19.75, 2000, {.forwards = false, .minSpeed = 35});
    chassis.waitUntil(24);
    matchload.matchloadV(0);
    intake.scoreHighGoal();
    pros::delay(900);
    chassis.moveToPoint(-48.5, 11.5, 1500, {.minSpeed = 30, .earlyExitRange = 2});
    chassis.turnToPoint(-23, 24, 1500, {.minSpeed = 10});
    chassis.moveToPoint(-23, 24, 2000,{.maxSpeed = 35, .minSpeed = 5, .earlyExitRange = 2});
    intake.intakeBlock();
    intake.moveTopIntake(20);
    chassis.turnToPoint(-40.25, 38, 2000, {.minSpeed = 15});
    chassis.moveToPoint(-40.25, 38, 2000, {.minSpeed = 15});
    chassis.moveToPoint(-26, 22, 2000, {.forwards = false, .minSpeed = 15});
    chassis.turnToPoint(-12.25, 34, 1500, {.forwards = false, .minSpeed = 15});
    intake.outtakeBlock();
    pros::delay(100);
    intake.stopIntake();
    chassis.moveToPoint(-12.25, 34, 2000, {.forwards = false, .minSpeed = 35});
    chassis.waitUntil(12.6);
    intake.intakePneumaticV(1);
    intake.intakeOutAuton();
}

void leftFourLongFourMiddleWing() {
    chassis.setPose(-18.1, -3.6, 270);
    chassis.moveToPoint(-47.4, -3.6, 1500);
    matchload.matchloadV(1);
    chassis.turnToPoint(-48.3, -12.5, 1500, {.minSpeed = 25, .earlyExitRange = 1});
    intake.intakeBlock();
    chassis.moveToPoint(-48.3, -12.5, 925, {.maxSpeed = 75, .minSpeed = 40});
    pros::delay(925);
    //matchload #1
    chassis.moveToPoint(-48.5, 19.75, 2000, {.forwards = false, .minSpeed = 35});
    chassis.waitUntil(24);
    matchload.matchloadV(0);
    intake.scoreHighGoal();
    pros::delay(900);
    chassis.moveToPoint(-48.5, 11.5, 1500, {.minSpeed = 30, .earlyExitRange = 2});
    //chassis.swingToPoint(24, 24.4, DriveSide::RIGHT, 2000, {.maxSpeed = 100, .minSpeed = 5});
    chassis.turnToPoint(-23, 24, 1500, {.minSpeed = 10});
    chassis.moveToPoint(-27, 20, 2000,{.minSpeed = 35, .earlyExitRange = 2});
    chassis.moveToPoint(-23, 24, 2000,{.maxSpeed = 35, .minSpeed = 5, .earlyExitRange = 2});
    intake.intakeBlock();
    intake.moveTopIntake(20);
    chassis.turnToPoint(-40.25, 38, 2000, {.minSpeed = 15});
    chassis.moveToPoint(-40.25, 38, 2000, {.minSpeed = 15});
    chassis.moveToPoint(-26, 22, 2000, {.forwards = false, .minSpeed = 15});
    chassis.turnToPoint(-12.25, 34, 1500, {.forwards = false, .minSpeed = 15});
    intake.outtakeBlock();
    pros::delay(100);
    intake.stopIntake();
    chassis.moveToPoint(-12.25, 34, 2000, {.forwards = false, .minSpeed = 35});
    chassis.waitUntil(12.6);
    intake.intakePneumaticV(1);
    intake.intakeOutAuton();
    pros::delay(1000);
    chassis.turnToPoint(-37, 20, 1500, {.minSpeed = 25, .earlyExitRange = 2});
    wing.wingV(1);
    chassis.moveToPoint(-37, 20, 1500, {.minSpeed = 20, .earlyExitRange = 2});
    intake.stopIntake();
    chassis.turnToPoint(-37.3, 32, 1500, {.forwards = false, .minSpeed = 20, .earlyExitRange = 2});
    chassis.waitUntilDone();
    wing.wingV(0);
    pros::delay(100);
    chassis.moveToPoint(-37.3, 32, 1500, {.forwards = false, .maxSpeed = 90, .minSpeed = 60});
    chassis.turnToHeading(195, 2000, {.minSpeed = 40});
}

void leftFourLong() {
    chassis.setPose(-18.1, -3.6, 270);
    chassis.moveToPoint(-47.4, -3.6, 1500);
    matchload.matchloadV(1);
    chassis.turnToPoint(-48.3, -12.5, 1500, {.minSpeed = 25, .earlyExitRange = 1});
    intake.intakeBlock();
    chassis.moveToPoint(-48.3, -12.5, 925, {.maxSpeed = 75, .minSpeed = 40});
    pros::delay(925);
    //matchload #1
    chassis.moveToPoint(-48.5, 19.75, 2000, {.forwards = false, .minSpeed = 35});
    chassis.waitUntil(24);
    matchload.matchloadV(0);
    intake.scoreHighGoal();
    pros::delay(900);
    //chassis.moveToPoint(-38.5, 16, 1500, {.minSpeed = 25, .earlyExitRange = 2, .pidSelector = 1});
    chassis.swingToPoint(-24, 8, DriveSide::LEFT, 2000, {.minSpeed = 45, .earlyExitRange = 5});
    chassis.turnToPoint(-37.5, 32, 1500, {.forwards = false, .minSpeed = 25, .earlyExitRange = 2});
    chassis.moveToPoint(-37.5, 32, 1500, {.forwards = false, .minSpeed = 60});
    chassis.turnToHeading(195, 2000, {.minSpeed = 40});
}

void leftSevenLong() {
    chassis.setPose(9.5, 1.7, 0);
    intake.intakeBlock();
    chassis.turnToPoint(3, 24.5, 1500, {.minSpeed = 5, .pidSelector = 1});
    chassis.moveToPoint(3, 24.5, 2500);
    chassis.waitUntil(12);
    matchload.matchloadV(1);
    chassis.turnToPoint(14.25, 36.3, 1500, {.forwards = false, .minSpeed = 10});
    chassis.moveToPoint(14.25, 36.3, 1500, {.forwards = false});
    intake.moveBottomIntake(-600);
    pros::delay(150);
    intake.stopIntake();
    pros::delay(550);
    intake.intakePneumaticV(1);
    intake.intakeOut();
    chassis.turnToPoint(-23.5, -2, 2000);
    pros::delay(1400);
    intake.intakePneumaticV(0);
    chassis.moveToPoint(7, 35.3, 1500, {.forwards = false, .minSpeed = 10});
    chassis.moveToPoint(14.5, 36.3, 1500, {.forwards = false, .minSpeed = 25});
    chassis.turnToPoint(-23.5, -2, 2000);
    //score middle goal
    chassis.moveToPoint(-23.5, -2, 3000);
    intake.intakeBlock();
    chassis.turnToPoint(-23.2, -13.75, 1500, {.minSpeed = 5});
    pros::delay(650);
    matchload.matchloadV(1);
    pros::delay(150);
    chassis.moveToPoint(-23.2, -13.75, 975, {.maxSpeed = 50, .minSpeed = 40});
    pros::delay(975);
    //chassis.moveToPoint(-23.2, -7, 1200, {.maxSpeed = 80, .minSpeed = 20});
    //chassis.moveToPoint(-23.2, -13.5, 1200, {.maxSpeed = 50, .minSpeed = 40});
    //pros::delay(200);
    //finish matchload #1
    chassis.turnToPoint(-23, 21, 1500, {.forwards = false, .minSpeed = 5});
    chassis.moveToPoint(-23, 21, 2500, {.forwards = false});
    pros::delay(1200);
    matchload.matchloadV(0);
    intake.scoreHighGoal();
    pros::delay(2100);
    intake.stopIntake();
    //finish score high goal
    /*chassis2.moveToPoint(-14.3, 12, 3000, {.minSpeed = 25, .earlyExitRange = 1});
    chassis2.turnToPoint(-13.2, 31.5, 2000, {.forwards = false, .minSpeed = 20, .earlyExitRange = 1});
    chassis2.moveToPoint(-13.2, 31.5, 2000, {.forwards = false, .maxSpeed = 65, .minSpeed = 60, .earlyExitRange = 1});*/
}

void rightFourLongThreeLow() {
    //new swp
    chassis.setPose(18.1, -3.6, 90);
    chassis.moveToPoint(46.9, -3.6, 1500);
    matchload.matchloadV(1);
    chassis.turnToPoint(47.5, -12.5, 1500, {.minSpeed = 25, .earlyExitRange = 1});
    intake.intakeBlock();
    chassis.moveToPoint(47.5, -12.5, 950, {.maxSpeed = 55, .minSpeed = 40});
    pros::delay(1000);
    //matchload #1
    chassis.moveToPoint(47.7, 19.75, 2000, {.forwards = false, .minSpeed = 30});
    chassis.waitUntil(24);
    matchload.matchloadV(0);
    intake.scoreHighGoal();
    pros::delay(950);
    chassis.moveToPoint(47.75, 14, 1500, {.minSpeed = 25, .earlyExitRange = 2});
    intake.outtakeBlock();
    //chassis.swingToPoint(24, 24.4, DriveSide::RIGHT, 2000, {.maxSpeed = 100, .minSpeed = 5});
    chassis.turnToPoint(23.75, 24, 1500, {.minSpeed = 10});
    chassis.moveToPoint(23.75, 24, 2000,{.maxSpeed = 70, .minSpeed = 5, .earlyExitRange = 2});
    intake.intakeBlock();
    chassis.waitUntil(13.9);
    matchload.matchloadV(1);
    chassis.turnToPoint(14.2, 35.5, 1500, {.minSpeed = 10});
    pros::delay(500);
    matchload.matchloadV(0);
    chassis.moveToPoint(14.2, 35.5, 1500);
    chassis.waitUntil(10);
    intake.moveBottomIntake(-250);
    pros::delay(1200);
    chassis.turnToPoint(36.5, 20, 2000, {.forwards = false, .minSpeed = 20, .earlyExitRange = 3});
    chassis.moveToPoint(36.5, 20, 1500, {.forwards = false});
    intake.stopIntake();
    chassis.turnToPoint(37, 32, 2000, {.minSpeed = 10});
    chassis.moveToPoint(37, 32, 1500, {.maxSpeed = 65, .minSpeed = 50});
    chassis.turnToHeading(340, 2000, {.minSpeed = 40});
}

void rightFourLong() {
    chassis.setPose(18.1, -3.6, 90);
    chassis.moveToPoint(47.75, -3.6, 1500);
    matchload.matchloadV(1);
    chassis.turnToPoint(47.8, -12.5, 1500, {.minSpeed = 30, .earlyExitRange = 1.5});
    intake.intakeBlock();
    chassis.moveToPoint(47.8, -12.5, 950, {.maxSpeed = 65, .minSpeed = 40});
    pros::delay(950);
    //matchload #1
    chassis.moveToPoint(48, 19.75, 2000, {.forwards = false, .minSpeed = 30});
    chassis.waitUntil(24);
    matchload.matchloadV(0);
    intake.scoreHighGoal();
    pros::delay(1000);
    chassis.swingToPoint(72, 8, DriveSide::LEFT, 2000, {.minSpeed = 45, .earlyExitRange = 5});
    chassis.turnToPoint(58, 33, 1500, {.forwards = false, .minSpeed = 25, .earlyExitRange = 2});
    chassis.moveToPoint(58, 33, 1500, {.forwards = false, .minSpeed = 60});
    chassis.turnToHeading(195, 2000, {.minSpeed = 40});

}

void rightSevenLong() {
    chassis.setPose(15.5, 1.5, 45);
    intake.intakeBlock();
    chassis.moveToPoint(18, 20, 2000, {.minSpeed = 35, .earlyExitRange = 1});
    chassis.moveToPoint(22, 24.5, 2000, {.maxSpeed = 35, .earlyExitRange = 1});
    matchload.matchloadV(1);
    //grab 3 stack
    chassis.turnToPoint(47.75, -1, 1500, {.minSpeed = 25, .earlyExitRange = 2});
    chassis.moveToPoint(47.75, -1, 2000);
    chassis.turnToPoint(47.8, -12.5, 1500, {.minSpeed = 30, .earlyExitRange = 2});
    intake.intakeBlock();
    chassis.moveToPoint(47.8, -12.5, 1100, {.maxSpeed = 70, .minSpeed = 40});
    pros::delay(1100);
    //matchload #1
    chassis.moveToPoint(48.2, 19.5, 2000, {.forwards = false, .minSpeed = 35});
    chassis.waitUntil(24);
    matchload.matchloadV(0);
    intake.scoreHighGoal();
    pros::delay(1300);
    //score long goal
    chassis.swingToPoint(72, 8, DriveSide::LEFT, 2000, {.minSpeed = 45, .earlyExitRange = 5});
    chassis.turnToPoint(58, 33, 1500, {.forwards = false, .minSpeed = 25, .earlyExitRange = 2});
    chassis.moveToPoint(58, 33, 1500, {.forwards = false, .minSpeed = 60});
    chassis.turnToHeading(195, 2000, {.minSpeed = 40});
    //wing push
}

void rightNineLong() {
    chassis.setPose(15.5, 1.5, 45);
    intake.intakeBlock();
    chassis.moveToPoint(18, 20, 2000, {.minSpeed = 35, .earlyExitRange = 1});
    chassis.moveToPoint(22, 24.5, 2000, {.maxSpeed = 35, .earlyExitRange = 1});
    matchload.matchloadV(1);
    //grab 3 stack
    chassis.moveToPoint(41, 38, 2000, {.minSpeed = 20});
    matchload.matchloadV(0);
    //grab 4th ball
    chassis.moveToPoint(24, 21, 2000, {.forwards = false, .minSpeed = 50, .earlyExitRange = 5});
    chassis.moveToPoint(48, 2, 2000, {.forwards = false, .minSpeed = 15});
    chassis.turnToPoint(48.2, 19.5, 1500, {.forwards = false, .minSpeed = 20, .earlyExitRange = 1});
    chassis.moveToPoint(48.2, 19.5, 2000, {.forwards = false, .minSpeed = 35});
    chassis.waitUntil(7);
    intake.scoreHighGoal();
    pros::delay(1300);
    chassis.turnToPoint(47.8, -12.5, 1500, {.minSpeed = 30, .earlyExitRange = 2});
    intake.intakeBlock();
    chassis.moveToPoint(47.8, -12.5, 1900, {.maxSpeed = 70, .minSpeed = 40});
    pros::delay(1900);
    //matchload #1
    chassis.moveToPoint(48.2, 19.5, 2000, {.forwards = false, .minSpeed = 35});
    chassis.waitUntil(24);
    matchload.matchloadV(0);
    intake.scoreHighGoal();
    //score long goal

}

void soloWinPoint() {
        //new swp
        chassis.setPose(18.1, -3.6, 90);
        chassis.moveToPoint(47.5, -3.6, 1500);
        matchload.matchloadV(1);
        chassis.turnToPoint(47.8, -12.5, 1500, {.minSpeed = 30, .earlyExitRange = 2});
        intake.intakeBlock();
        chassis.moveToPoint(47.8, -12.5, 875, {.maxSpeed = 80, .minSpeed = 40});
        pros::delay(875);
        //matchload #1
        chassis.moveToPoint(48.2, 19.5, 2000, {.forwards = false, .minSpeed = 35});
        chassis.waitUntil(24);
        matchload.matchloadV(0);
        intake.scoreHighGoal();
        pros::delay(925);
        chassis.moveToPoint(48.2, 13, 1500, {.minSpeed = 25, .earlyExitRange = 2});
        //chassis.swingToPoint(24, 24.4, DriveSide::RIGHT, 2000, {.maxSpeed = 100, .minSpeed = 5});
        chassis.turnToPoint(24.5, 26, 1500, {.minSpeed = 15, .earlyExitRange = 1});
        chassis.moveToPoint(24.5, 26, 2000,{.maxSpeed = 60, .minSpeed = 5, .earlyExitRange = 2});
        intake.intakeBlock();
        intake.moveTopIntake(20);
        //chassis.moveToPoint(-24, 24.5, 2000, {.maxSpeed = 100, .pidSelector = 1});
        chassis.turnToPoint(-24, 26.5, 2000, {.minSpeed = 15, .earlyExitRange = 4});
        chassis.moveToPoint(-24, 26.5, 2000, {.maxSpeed = 100});
        chassis.waitUntil(28.1);
        matchload.matchloadV(1);
        chassis.turnToPoint(-11.75, 37, 1500, {.forwards = false, .minSpeed = 25, .earlyExitRange = 2, .pidSelector = 1});
        intake.outtakeBlock();
        pros::delay(150);
        intake.stopIntake();
        chassis.moveToPoint(-11.75, 37, 2000, {.forwards = false, .minSpeed = 35});
        chassis.waitUntil(12.9);
        intake.intakePneumaticV(1);
        intake.intakeOutAuton();
        chassis.turnToPoint(-46.9, -0.5, 800, {.minSpeed = 15, .earlyExitRange = 1});
        pros::delay(900);
        intake.stopIntake();
        chassis.moveToPoint(-46.9, -0.5, 2000, {.maxSpeed = 105, .minSpeed = 10, .earlyExitRange = 2});
        pros::delay(300);
        intake.intakePneumaticV(0);
        intake.intakeBlock();
        chassis.turnToPoint(-48, -12.5, 1500,{.minSpeed = 25, .earlyExitRange = 1});
        chassis.moveToPoint(-48, -12.5, 1100, {.maxSpeed = 80, .minSpeed = 40});
        pros::delay(1100);
        //matchload #1
        chassis.moveToPoint(-48.35, 20, 2000, {.forwards = false, .minSpeed = 30});
        chassis.waitUntil(24);
        intake.scoreHighGoal();
}

void skills() {
        chassis.setPose(17.1, -4.1, 90);
        chassis.moveToPoint(47.5, -4.1, 1500);
        matchload.matchloadV(1);
        wing.wingV(1);
        chassis.turnToPoint(47.8, -12.5, 1500, {.minSpeed = 30, .earlyExitRange = 2});
        intake.intakeBlock();
        chassis.moveToPoint(47.8, -12.5, 2000, {.maxSpeed = 70, .minSpeed = 40});
        pros::delay(2000);
        //matchload #1
        chassis.moveToPoint(48.2, -5, 2000, {.forwards = false, .minSpeed = 35});
        matchload.matchloadV(0);
        intake.stopIntake();
        chassis.turnToPoint(59.5, 20, 2000, {.forwards = false, .minSpeed = 35});
        chassis.moveToPoint(59.5, 20, 2000, {.forwards = false, .minSpeed = 35});

        chassis.turnToPoint(59.5, 70, 2000, {.forwards = false});
        chassis.moveToPoint(59.5, 70, 2000, {.forwards = false});

        chassis.turnToPoint(48, 85, 2000, {.forwards = false});
        chassis.moveToPoint(48, 85, 2000, {.forwards = false});

        chassis.turnToPoint(48, 70, 2000, {.forwards = false});
        chassis.moveToPoint(48, 70, 2000, {.forwards = false});
        pros::delay(3000);
        intake.scoreHighGoal();

        chassis.turnToPoint(48, 106, 2000);
        matchload.matchloadV(1);
        chassis.moveToPoint(48, 106, 2000);

        pros::delay(3000);
        /*
        //new swp
        chassis.setPose(18.1, -3.6, 90);
        chassis.moveToPoint(47.5, -3.6, 1500);
        matchload.matchloadV(1);
        chassis.turnToPoint(47.8, -12.5, 1500, {.minSpeed = 30, .earlyExitRange = 2});
        intake.intakeBlock();
        chassis.moveToPoint(47.8, -12.5, 2000, {.maxSpeed = 70, .minSpeed = 40});
        pros::delay(2000);
        //matchload #1
        chassis.moveToPoint(48.2, 19.5, 2000, {.forwards = false, .minSpeed = 35});
        chassis.waitUntil(24);
        matchload.matchloadV(0);
        intake.scoreHighGoal();
        pros::delay(2500);
        chassis.moveToPoint(48.2, 13, 1500, {.minSpeed = 25, .earlyExitRange = 2});
        //chassis.swingToPoint(24, 24.4, DriveSide::RIGHT, 2000, {.maxSpeed = 100, .minSpeed = 5});
        chassis.turnToPoint(25.5, 26.5, 1500, {.minSpeed = 15, .earlyExitRange = 1});
        chassis.moveToPoint(25.5, 26.5, 2000,{.maxSpeed = 30, .minSpeed = 5, .earlyExitRange = 2});
        intake.intakeBlock();
        intake.moveTopIntake(20);
        //chassis.moveToPoint(-24, 24.5, 2000, {.maxSpeed = 100, .pidSelector = 1});
        chassis.turnToPoint(-24, 25.75, 2000, {.minSpeed = 15, .earlyExitRange = 4});
        chassis.moveToPoint(-24, 25.75, 2000, {.maxSpeed = 50});
        chassis.waitUntil(27.4);
        //matchload.matchloadV(1);
        chassis.turnToPoint(-11.75, 37, 1500, {.forwards = false, .minSpeed = 25, .earlyExitRange = 2, .pidSelector = 1});
        intake.outtakeBlock();
        pros::delay(100);
        intake.stopIntake();
        chassis.moveToPoint(-11.75, 37, 2000, {.forwards = false, .minSpeed = 30});
        chassis.waitUntil(12.9);
        intake.intakePneumaticV(1);
        intake.intakeOutAuton();
        chassis.turnToPoint(-46.4, -0.5, 800, {.minSpeed = 15, .earlyExitRange = 1});
        pros::delay(900);
        intake.stopIntake();
        chassis.moveToPoint(-46.4, -0.5, 2000, {.maxSpeed = 105, .minSpeed = 10, .earlyExitRange = 2});
        pros::delay(300);
        intake.intakePneumaticV(0);
        intake.intakeBlock();
        chassis.turnToPoint(-48, -12.5, 1500,{.minSpeed = 25, .earlyExitRange = 1});
        chassis.moveToPoint(-48, -12.5, 2000, {.maxSpeed = 70, .minSpeed = 40});
        pros::delay(2000);
        //matchload #1
        chassis.moveToPoint(-48.3, 20, 2000, {.forwards = false, .minSpeed = 30});
        chassis.waitUntil(24);
        intake.scoreHighGoal();
    /*
    chassis.setPose(17.5, -48.375, 90);
    chassis.moveToPoint(47, -48.375, 2000);
    wing.wingV(1);
    chassis.turnToPoint(47, -60, 2000);
    intake.intakeBlock();
    pros::delay(700);
    matchload.matchloadV(1);
    pros::delay(200);
    chassis.moveToPoint(47, -58.5, 2000, {.maxSpeed = 50, .minSpeed = 40});
    pros::delay(3000);
    chassis.moveToPoint(47, -50, 2000, {.forwards = false, .minSpeed = 20});
    chassis.moveToPoint(47, -58.5, 2000, {.maxSpeed = 50, .minSpeed = 40});
    pros::delay(2000);
    chassis.moveToPoint(47, -48, 2000, {.forwards = false});
    chassis.turnToPoint(60, -48, 2000, {.minSpeed = 5});
    matchload.matchloadV(0);
    intake.stopIntake();
    chassis.moveToPoint(61, -48, 2000, {.minSpeed = 5});
    chassis.turnToPoint(61, 32, 2000, {.minSpeed = 5});
    chassis.moveToPoint(60.5, 32, 4000, {.maxSpeed = 100, .minSpeed = 5});

    chassis.turnToPoint(48, 48, 2000, {.minSpeed = 10});
    chassis.moveToPoint(48, 48, 4000, {.minSpeed = 10});

    chassis.turnToPoint(48, 26, 3000, {.forwards = false, .minSpeed = 5});
    chassis.moveToPoint(48, 26, 3000, {.forwards = false, .minSpeed = 5});
    pros::delay(700);
    intake.scoreHighGoal();
    pros::delay(7000);
    matchload.matchloadV(1);
    pros::delay(200);
    intake.intakeBlock();
    chassis.turnToPoint(48, 58.5, 2000, {.minSpeed = 5});
    chassis.moveToPoint(48, 58.5, 2000, {.maxSpeed = 50, .minSpeed = 40});
    pros::delay(3000);
    chassis.moveToPoint(47.75, 50, 2000, {.forwards = false, .minSpeed = 20});
    chassis.moveToPoint(47.75, 58.5, 2000, {.maxSpeed = 50, .minSpeed = 40});
    pros::delay(2000);
    chassis.turnToPoint(47.75, 26, 3000, {.forwards = false, .minSpeed = 5});
    chassis.moveToPoint(47.75, 26, 3000, {.forwards = false, .minSpeed = 5});
    pros::delay(700);
    intake.scoreHighGoal();
    pros::delay(7000);

    chassis.moveToPoint(47.75, 48, 3000, {.forwards = true, .minSpeed = 5});

    chassis.turnToPoint(61, 32, 2000, { .forwards = false, .minSpeed = 5,});
    chassis.moveToPoint(60.5, 32, 4000, {.forwards = false, .maxSpeed = 100, .minSpeed = 5});

    chassis.turnToPoint(60.5, -48, 2000, { .forwards = false, .maxSpeed = 100, .minSpeed = 5, });
    chassis.moveToPoint(60.5, -48, 4000, {.forwards = false, .maxSpeed = 90, .minSpeed = 5});

    matchload.matchloadV(0);

    chassis.turnToPoint(24, -48, 2000, { .forwards = false, .minSpeed = 5});
    chassis.moveToPoint(24, -48, 4000, {.forwards = false, .maxSpeed = 100, .minSpeed = 5});


    chassis.turnToPoint(24, -65.5, 3000, {.forwards = false, .minSpeed = 5});
    chassis.moveToPoint(24, -65.5, 3000, {.forwards = false, .minSpeed = 5});

    chassis.turnToPoint(-3, -65, 3000, {.forwards = false});
    chassis.moveToPoint(-3, -65, 2100, {.forwards = false, .minSpeed = 40});
     */
}