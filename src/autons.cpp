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
    //chassis.moveToPoint(0, 48, 4000);
    //chassis.turnToHeading(90, 5000);
   /* chassisShort.turnToHeading(45, 5000);
    pros::delay(4000);
    chassisShort.turnToHeading(90, 5000);
    pros::delay(4000);
    chassis.turnToHeading(180, 5000);*/
    //chassis.turnToPoint(-48,0, 5000);
    chassis.setPose(0, 0, 180);
    chassis.moveToPoint(0, 48, 5000, {.forwards = false});
    //chassis.turnToPoint(48, 0, 5000);
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
void simpleQual() {
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

void leftElim() {
        chassis.setPose(9.5, 1.7, 0);
        intake.intakeBlock();
        chassis.turnToPoint(2.75, 24.5, 1500, {.minSpeed = 30, .earlyExitRange = 5});
        chassis.moveToPoint(2.75, 24.5, 2000, {.minSpeed = 25, .earlyExitRange = 1});
        pros::delay(390);
        matchload.matchloadV(1);
        //chassis.moveToPoint(-3, 24.5, 2500, {.maxSpeed = 15, .minSpeed = 10});
        chassis.turnToPoint(-23.8, 5, 2000, {.minSpeed = 20, .earlyExitRange = 2});
        chassis.moveToPoint(-23.8, 5, 3000, {.minSpeed = 15, .earlyExitRange = 1});
        //finish matchload #1
        chassis.turnToPoint(-23.4, 21, 1500, {.forwards = false, .minSpeed = 20, .earlyExitRange = 2});
        chassis.moveToPoint(-23.4, 21, 2500, {.forwards = false});
        pros::delay(700);
        intake.scoreHighGoal();
        matchload.matchloadV(0);
        pros::delay(1100);
        intake.stopIntake();
        //finish score high goal
        //chassisSwing.moveToPoint(-14.95, 13, 3000, {.minSpeed = 25, .earlyExitRange = 1});
        //chassisSwing.turnToPoint(-13.6, 32, 2000, {.forwards = false, .minSpeed = 30, .earlyExitRange = 2});
        //chassisSwing.moveToPoint(-13.6, 32, 2000, {.forwards = false, .maxSpeed = 75, .minSpeed = 70, .earlyExitRange = 1});
        //chassisSwing.turnToPoint(0, 96, 2000, {.forwards = false});
        intake.moveBottomIntake(-600);
        pros::delay(100);
        intake.stopIntake();
        pros::delay(550);
        intake.intakePneumaticV(0);
        intake.intakeOut();
}

void rightElim() {
    chassis.setPose(-9.5, 1.5, 0);
    intake.intakeBlock();
    chassis.turnToPoint(-3, 24.5, 1500, {.minSpeed = 30, .earlyExitRange = 4});
    chassis.moveToPoint(-3, 24.5, 2000, {.minSpeed = 20, .earlyExitRange = 1});
    pros::delay(400);
    matchload.matchloadV(1);
    //chassis.moveToPoint(-3, 24.5, 2500, {.maxSpeed = 15, .minSpeed = 10});
    chassis.turnToPoint(24.75, 0, 2000, {.minSpeed = 10, .earlyExitRange = 1});
    chassis.moveToPoint(24.75, 0, 3000);
    //finish matchload #1
    chassis.turnToPoint(24, 21, 1500, {.forwards = false, .minSpeed = 15, .earlyExitRange = 1});
    chassis.moveToPoint(24, 21, 2500, {.forwards = false});
    pros::delay(1200);
    matchload.matchloadV(0);
    intake.scoreHighGoal();
    pros::delay(1000);
    intake.stopIntake();
    //finish score high goal
    //chassisSwing.moveToPoint(33.15, 12, 3000, {.minSpeed = 30, .earlyExitRange = 1});
    //chassisSwing.turnToPoint(33.9, 31.5, 2000, {.forwards = false, .minSpeed = 30, .earlyExitRange = 2});
    //chassisSwing.moveToPoint(33.9, 31.5, 2000, {.forwards = false, .maxSpeed = 65, .minSpeed = 60, .earlyExitRange = 1});
}

void soloWinPoint() {
        //new swp
        chassis.setPose(18.6, -3.6, 90);
        chassis.moveToPoint(47.2, -3.6, 1500);
        matchload.matchloadV(1);
        chassis.turnToPoint(47.5, -12.5, 1500,{.minSpeed = 25});
        intake.intakeBlock();
        chassis.moveToPoint(47.5, -12.5, 950, {.maxSpeed = 55, .minSpeed = 30});
        pros::delay(950);
        //matchload #1
        chassis.moveToPoint(47.7, 19.75, 2000, {.forwards = false, .minSpeed = 30});
        chassis.waitUntil(24);
        matchload.matchloadV(0);
        intake.scoreHighGoal();
        pros::delay(950);
        intake.stopIntake();
        chassis.moveToPoint(47.75, 13.5, 1500, {.minSpeed = 30, .earlyExitRange = 1});
        //chassis.swingToPoint(24, 24.4, DriveSide::RIGHT, 2000, {.maxSpeed = 100, .minSpeed = 5});
        chassis.turnToPoint(24, 24, 1500, {.minSpeed = 5});
        intake.intakeBlock();
        chassis.moveToPoint(24, 24, 2000,{.maxSpeed = 70, .minSpeed = 5, .earlyExitRange = 2});
        intake.moveTopIntake(20);
        //chassis.moveToPoint(-24, 24.5, 2000, {.maxSpeed = 100, .pidSelector = 1});
        chassis.turnToPoint(-24, 24.5, 2000, {.minSpeed = 25, .earlyExitRange = 2});
        chassis.moveToPoint(-24, 24.5, 2000, {.maxSpeed = 90});
        chassis.waitUntil(27.9);
        matchload.matchloadV(1);
        chassis.turnToPoint(-11, 37.9, 1500, {.forwards = false, .minSpeed = 15, .pidSelector = 1});
        intake.outtakeBlock();
        pros::delay(200);
        intake.stopIntake();
        chassis.moveToPoint(-11, 37.9, 2000, {.forwards = false, .minSpeed = 25});
        chassis.waitUntil(12.75);
        intake.intakePneumaticV(1);
        intake.intakeOutAuton();
        chassis.turnToPoint(-46, -2.5, 800, {.minSpeed = 10});
        pros::delay(800);
        intake.stopIntake();
        chassis.moveToPoint(-46, -2.5, 2000, {.maxSpeed = 75, .minSpeed = 10});  
        pros::delay(300);
        intake.intakePneumaticV(0);
        intake.intakeBlock();
        chassis.turnToPoint(-47.5, -12.5, 1500,{.minSpeed = 25, .earlyExitRange = 1});
        chassis.moveToPoint(-47.5, -12.5, 1100, {.maxSpeed = 55, .minSpeed = 30});
        pros::delay(1100);
        //matchload #1
        chassis.moveToPoint(-48.2, 19.75, 2000, {.forwards = false, .minSpeed = 30});
        chassis.waitUntil(24);
        intake.scoreHighGoal();
}

void skills() {
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
}