#include "main.h"
//

void odomTest() {
    chassis.setPose(0, 0, 0);
    //chassis.turnToPoint(48, 0, 5000);
    //chassis.moveToPoint(0, 48, 5000);
    chassis.moveToPoint(0, 48, 5000);
    chassis.turnToPoint(48, 48, 3000);
    chassis.moveToPoint(48, 48, 5000);
    chassis.turnToPoint(48, 0, 3000);
    chassis.moveToPoint(48, 0, 5000);
    chassis.turnToPoint(0, 0, 3000);
    chassis.moveToPoint(0, 0, 5000);
    chassis.turnToPoint(0, 48, 3000);
}
void simpleQual() {
        chassis.setPose(9.5, 1.7, 0);
        intake.intakeBlock();
        chassis.turnToPoint(3, 24.5, 1500, {.minSpeed = 30, .earlyExitRange = 4});
        chassis.moveToPoint(6.25, 11, 2000, {.minSpeed = 50, .earlyExitRange = 0.5});
        chassis.moveToPoint(3, 24.5, 2500, {.maxSpeed = 15, .minSpeed = 10});
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

        
        /*chassis.moveToPoint(-23.25, 12, 2000, {.minSpeed = 20, .earlyExitRange = 1});
        chassis.turnToPoint(-14.25, 20, 2000, {.forwards = false, .minSpeed = 25, .earlyExitRange = 1});
        chassis.moveToPoint(-14.25, 20, 2000, {.forwards = false, .minSpeed = 20, .earlyExitRange = 0.5});
        chassis.turnToPoint(-12.2, 32, 2000, {.forwards = false, .minSpeed = 25, .earlyExitRange = 2});
        chassis.moveToPoint(-12.2, 32, 2000, {.forwards = false, .maxSpeed = 65, .minSpeed = 60});*/
        //chassis.setPose(-23.35, 21, 180);
        /*chassis.moveToPoint(-12.4, 11, 3000, {.minSpeed = 20, .earlyExitRange = 1});
        chassis.turnToPoint(-12.4, 32, 2000, {.forwards = false, .minSpeed = 20, .earlyExitRange = 1});
        chassis.moveToPoint(-12.4, 32, 2000, {.forwards = false, .maxSpeed = 65, .minSpeed = 60, .earlyExitRange = 1});
        /*chassis.setPose(9.5, 1.5, 0);
        intake.intakeBlock();
        chassis.turnToPoint(3.25, 24.5, 1000, {.minSpeed = 30, .earlyExitRange = 4});
        chassis.moveToPoint(6, 9, 4000, {.minSpeed = 55, .earlyExitRange = 0.5});
        chassis.moveToPoint(3.25, 24.5, 4000, {.maxSpeed = 15, .minSpeed = 10});
        chassis.turnToPoint(13, 34.3, 1500, {.forwards = false, .minSpeed = 35, .earlyExitRange = 2});
        chassis.moveToPoint(13, 34.3, 1500, {.forwards = false, .minSpeed = 10});
        intake.moveBottomIntake(-600);
        pros::delay(150);
        intake.stopIntake();
        pros::delay(600);
        intake.intakePneumaticV(1);
        intake.intakeOut();
        chassis.turnToPoint(-23, -2, 2500,{.minSpeed = 8});
        pros::delay(1150);
        intake.intakePneumaticV(0);
        //score middle goal
        chassis.moveToPoint(-22.5, -2, 3000);
        matchload.matchloadV(1);
        intake.intakeBlock();
        chassis.turnToPoint(-23.2, -12, 2500,{.minSpeed = 10});
        chassis.moveToPoint(-23.2, -12, 1200, {.maxSpeed = 50, .minSpeed = 45});
        pros::delay(1200);
        //finish matchload #1
        chassis.turnToPoint(-23.3, -12, 1200, {.forwards = false, .maxSpeed = 50, .minSpeed = 5});
        chassis.moveToPoint(-23.3, 20, 2000, {.forwards = false, .maxSpeed = 70});
        pros::delay(1300);
        matchload.matchloadV(0);
        intake.scoreHighGoal();
        pros::delay(1600);
        intake.stopIntake();
        //finish score high goal
        chassis.moveToPoint(-23.25, 12, 3000, {.minSpeed = 30, .earlyExitRange = 2});
        chassis.turnToPoint(-14.25, 20, 2000, {.forwards = false, .minSpeed = 20, .earlyExitRange = 1});
        chassis.moveToPoint(-14.25, 20, 2000, {.forwards = false, .minSpeed = 10});
        chassis.turnToPoint(-12.2, 32, 2000, {.forwards = false, .minSpeed = 20, .earlyExitRange = 1});
        chassis.moveToPoint(-12.2, 32, 2000, {.forwards = false, .maxSpeed = 65, .minSpeed = 60});
        /*chassis.moveToPoint(-23, 17, 3000, {.minSpeed = 55, .earlyExitRange = 2});
        chassis.moveToPoint(-10, 14, 3000, {.minSpeed = 35, .earlyExitRange = 1});
        chassis.turnToPoint(-12.2, 32, 2000, {.forwards = false, .minSpeed = 20, .earlyExitRange = 1});
        chassis.moveToPoint(-12.2, 32, 2000, {.forwards = false, .maxSpeed = 65, .minSpeed = 60});*/
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
        chassis2.moveToPoint(-14.95, 13, 3000, {.minSpeed = 25, .earlyExitRange = 1});
        chassis2.turnToPoint(-13.6, 32, 2000, {.forwards = false, .minSpeed = 30, .earlyExitRange = 2});
        chassis2.moveToPoint(-13.6, 32, 2000, {.forwards = false, .maxSpeed = 75, .minSpeed = 70, .earlyExitRange = 1});
        chassis2.turnToPoint(0, 96, 2000, {.forwards = false});
    /*
        chassis.setPose(9.5, 1.5, 0);
        intake.intakeBlock();
        chassis.turnToPoint(3.25, 24.5, 1500, {.minSpeed = 30, .earlyExitRange = 4});
        chassis.moveToPoint(6.75, 9, 2000, {.minSpeed = 45, .earlyExitRange = 0.5});
        chassis.moveToPoint(3.25, 24.5, 2500, {.maxSpeed = 15, .minSpeed = 10});
        chassis.turnToPoint(-24, -2, 2000, {.minSpeed = 5});
        //score middle goal
        chassis.moveToPoint(-24, -2, 3000);
        matchload.matchloadV(1);
        intake.intakeBlock();
        chassis.turnToPoint(-23.25, -15, 1500, {.minSpeed = 30});
        chassis.moveToPoint(-23.25, -15, 1100, {.maxSpeed = 65, .minSpeed = 60});
        pros::delay(1100);
        //finish matchload #1
        chassis.turnToPoint(-23.25, 21, 1500, {.forwards = false, .minSpeed = 10});
        chassis.moveToPoint(-23.25, 21, 2500, {.forwards = false});
        pros::delay(1300);
        matchload.matchloadV(0);
        intake.scoreHighGoal();
        pros::delay(2400);
        intake.stopIntake();
        //finish score high goal
        chassis2.moveToPoint(-15.15, 12, 3000, {.minSpeed = 20, .earlyExitRange = 1});
        chassis2.turnToPoint(-13.9, 31.5, 2000, {.forwards = false, .minSpeed = 20, .earlyExitRange = 1});
        chassis2.moveToPoint(-13.9, 31.5, 2000, {.forwards = false, .maxSpeed = 65, .minSpeed = 60, .earlyExitRange = 1});
        */
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
    chassis2.moveToPoint(33.15, 12, 3000, {.minSpeed = 30, .earlyExitRange = 1});
    chassis2.turnToPoint(33.9, 31.5, 2000, {.forwards = false, .minSpeed = 30, .earlyExitRange = 2});
    chassis2.moveToPoint(33.9, 31.5, 2000, {.forwards = false, .maxSpeed = 65, .minSpeed = 60, .earlyExitRange = 1});

    /*
    chassis.setPose(-9.5, 1.5, 0);
    intake.intakeBlock();
    chassis.turnToPoint(-3.25, 24.5, 1500, {.minSpeed = 30, .earlyExitRange = 4});
    chassis.moveToPoint(-6.25, 10, 2000, {.minSpeed = 45, .earlyExitRange = 0.5});
    chassis.moveToPoint(-3.25, 24.5, 2500, {.maxSpeed = 15, .minSpeed = 10});
    chassis.turnToPoint(24.75, -2, 2000, {.minSpeed = 5});
    //score middle goal
    chassis.moveToPoint(24.75, -2, 3000);
    matchload.matchloadV(1);
    intake.intakeBlock();
    chassis.turnToPoint(24, -14.25, 1500, {.minSpeed = 25});
    chassis.moveToPoint(24, -14.25, 1200, {.maxSpeed = 60, .minSpeed = 40});
    pros::delay(1200);
    //finish matchload #1
    chassis.turnToPoint(24, 21, 1500, {.forwards = false, .minSpeed = 10});
    chassis.moveToPoint(24, 21, 2500, {.forwards = false});
    pros::delay(1300);
    matchload.matchloadV(0);
    intake.scoreHighGoal();
    pros::delay(2500);
    intake.stopIntake();
    //finish score high goal
    chassis2.moveToPoint(33.15, 12, 3000, {.minSpeed = 20, .earlyExitRange = 1});
    chassis2.turnToPoint(33.9, 31.5, 2000, {.forwards = false, .minSpeed = 20, .earlyExitRange = 1});
    chassis2.moveToPoint(33.9, 31.5, 2000, {.forwards = false, .maxSpeed = 65, .minSpeed = 60, .earlyExitRange = 1});
    */

    //4ball
    
    /*chassis.setPose(-9.5, 1.5, 0);
    intake.intakeBlock();
    chassis.moveToPoint(1.5, 27, 4000, {.maxSpeed = 30, .minSpeed = 5, .earlyExitRange = 1});
    chassis.turnToPoint(24, 0, 2000);
    chassis.moveToPoint(24.5, 0, 3000);
    chassis.turnToPoint(24.5, 22.25, 2000, {.forwards = false});
    chassis.moveToPoint(24.25, 22.25, 1600, {.forwards = false, .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 1});
    pros::delay(650);
    intake.scoreHighGoal();
    pros::delay(2000);
    intake.stopIntake();
    chassis.moveToPoint(35.5, 11, 3000, {.minSpeed = 10, .earlyExitRange = 1});
    chassis.turnToPoint(35.5, 34.5, 2000, {.forwards = false, .minSpeed = 10});
    chassis.moveToPoint(35.5, 34.5, 2000, {.forwards = false, .maxSpeed = 65, .minSpeed = 60});
    chassis.moveToPoint(40, 34.5, 5000, {.forwards = false, .maxSpeed = 10, .minSpeed = 10});*/
}

void soloWinPoint() {
        //new swp
        chassis.setPose(17.5, -0.375, 90);
        intake.intakeBlock();
        chassis.moveToPoint(46, -0.375, 2000, {.minSpeed = 20, .earlyExitRange = 1});
        chassis.turnToPoint(47, -16, 2000, {.minSpeed = 20}, false);
        matchload.matchloadV(1);
        chassis.moveToPoint(47, -16, 1000, {.maxSpeed = 65, .minSpeed = 60});
        pros::delay(1000);
        //matchload #1
        chassis.moveToPoint(47.5, 20, 2000, {.forwards = false, .minSpeed = 15});
        pros::delay(1000);
        matchload.matchloadV(0);
        intake.scoreHighGoal();
        pros::delay(1300);
        intake.stopIntake();
        //high goal #1
        /*chassis.turnToPoint(-24, 24, 2000, {.minSpeed = 30, .earlyExitRange = 4});
        intake.intakeBlock();
        chassis.moveToPoint(-22.5, 24.5, 4000, {.maxSpeed = 30, .minSpeed = 5, .earlyExitRange = 2});
        //three ball #1
        chassis.turnToPoint(-11, 33.75, 2000, {.forwards = false, .minSpeed = 45, .earlyExitRange = 5});
        chassis.moveToPoint(-11, 33.75, 1200, {.forwards = false, .minSpeed = 25, .earlyExitRange = 1});
        intake.moveBottomIntake(-600);
        pros::delay(200);
        intake.stopIntake();
        pros::delay(300);
        intake.intakePneumaticV(1);
        intake.intakeOut();
        chassis.turnToPoint(-44, -1, 2500,{.minSpeed = 25, .earlyExitRange = 3});
        pros::delay(1600);
        intake.moveBottomIntake(-600);
        pros::delay(200);
        intake.stopIntake();
        intake.intakePneumaticV(0);
        //middle goal
        chassis.moveToPoint(14, 22.5, 2000, { .minSpeed = 40, .earlyExitRange = 2});
        intake.intakeBlock();
        chassis.moveToPoint(22, 23.5, 3000, {.maxSpeed = 40, .minSpeed = 20, .earlyExitRange = 2}); 
        chassis.turnToPoint(44.25, -2, 2000,{.minSpeed = 30, .earlyExitRange = 4});
        chassis.moveToPoint(44.25, -2, 3000,{.minSpeed = 30, .earlyExitRange = 2});
        chassis.turnToPoint(46.25, -14, 2000,{.minSpeed = 30, .earlyExitRange = 1});
        matchload.matchloadV(1);
        chassis.moveToPoint(46.25, -14, 1050, {.maxSpeed = 50, .minSpeed = 35, .earlyExitRange = 1});
        //finish matchload #2
        pros::delay(1050);
        chassis.moveToPoint(46.25, 22.5, 1600, {.forwards = false, .maxSpeed = 70, .minSpeed = 20, .earlyExitRange = 1});
        pros::delay(1000);
        intake.scoreHighGoal();
        matchload.matchloadV(0);
        //finish score high goal #2*/


        /*chassis.setPose(9.5, 1.5, 0);
        intake.intakeBlock();
        chassis.moveToPoint(-1.5, 25.5, 4000, {.minSpeed = 20, .earlyExitRange = 2});
        chassis.turnToPoint(15.25, 37, 2000, {.forwards = false, .minSpeed = 45, .earlyExitRange = 5});
        chassis.moveToPoint(15, 37, 1050, {.forwards = false, .minSpeed = 25, .earlyExitRange = 3});
        chassis.turnToPoint(-21, -2, 2000,{.minSpeed = 25, .earlyExitRange = 4});
        pros::delay(250);
        intake.scoreMiddleHigh();
        pros::delay(300);
        intake.stopIntake();
        //score middle goal
        chassis.moveToPoint(-21.75, -2, 3000,{.minSpeed = 30, .earlyExitRange = 2});
        matchload.matchloadV(1);
        intake.intakeBlock();
        chassis.turnToPoint(-23.5, -13.5, 2000,{.minSpeed = 30, .earlyExitRange = 1});
        chassis.moveToPoint(-23.5, -13.5, 950, {.maxSpeed = 50, .minSpeed = 35, .earlyExitRange = 1});
        pros::delay(950);
        //finish matchload #1
        chassis.moveToPoint(-23, 22, 1600, {.forwards = false, .maxSpeed = 70, .minSpeed = 20, .earlyExitRange = 1});
        pros::delay(1000);
        matchload.matchloadV(0);
        intake.scoreHighGoal();
        pros::delay(1200);
        intake.stopIntake();
        //finish score high goal
        chassis.turnToPoint(36, 22.5, 2000, {.minSpeed = 35, .earlyExitRange = 4});
        intake.intakeBlock();
        chassis.moveToPoint(34, 22.5, 2000, { .minSpeed = 40, .earlyExitRange = 2});
        chassis.moveToPoint(46, 23.5, 3000, {.maxSpeed = 40, .minSpeed = 20, .earlyExitRange = 2}); 
        chassis.turnToPoint(68.25, -2, 2000,{.minSpeed = 30, .earlyExitRange = 4});
        chassis.moveToPoint(68.25, -2, 3000,{.minSpeed = 30, .earlyExitRange = 2});
        chassis.turnToPoint(70.25, -14, 2000,{.minSpeed = 30, .earlyExitRange = 1});
        matchload.matchloadV(1);
        chassis.moveToPoint(70.25, -14, 1050, {.maxSpeed = 50, .minSpeed = 35, .earlyExitRange = 1});
        //finish matchload #2
        pros::delay(1050);
        chassis.moveToPoint(70.25, 22.5, 1600, {.forwards = false, .maxSpeed = 70, .minSpeed = 20, .earlyExitRange = 1});
        pros::delay(1000);
        intake.scoreHighGoal();
        matchload.matchloadV(0);
        //finish score high goal #2*/
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
    /*chassis.turnToPoint(47.5, 40, 3000, {.forwards = false});
    chassis.moveToPoint(47.5, 40, 3000, {.forwards = false});
    chassis.turnToPoint(47.75, 25, 2000, {.forwards = false});
    chassis.moveToPoint(47.75, 25, 2500, {.forwards = false, .maxSpeed = 60});
    pros::delay(1100);
    intake.scoreHighGoal();
    pros::delay(2500);
    matchload.matchloadV(1);
    intake.intakeBlock();
    chassis.moveToPoint(47.75, 62, 2000, {.maxSpeed = 60, .minSpeed = 40});
    pros::delay(2700);
    chassis.moveToPoint(47.75, 26, 4000, {.forwards = false, .maxSpeed = 60});
    pros::delay(1150);
    //score second time first goal
    intake.scoreHighGoal();
    //chassis.setPose(48, 28, 0);
    pros::delay(2600);
    intake.intakeBlock();
    chassis.moveToPoint(48, 40, 3000);
    chassis.turnToPoint(-47, 40, 1500);
    chassis.moveToPoint(-47, 40, 2000);
    chassis.turnToPoint(-47.5, 62, 2000);
    chassis.moveToPoint(-47.5, 62, 2500, {.maxSpeed = 60, .minSpeed = 40});
    pros::delay(2700);
    chassis.moveToPoint(-61.5, 40, 4000, {.forwards = false, .minSpeed = 25, .earlyExitRange = 2});
    chassis.turnToPoint(-61, -30, 2000, {.forwards = false});
    matchload.matchloadV(0);
    chassis.moveToPoint(-61, -30, 4000, {.forwards = false});
    chassis.moveToPoint(-47.5, -40, 3000, {.forwards = false});
    chassis.turnToPoint(-47.5, -25, 2000, {.forwards = false});
    chassis.moveToPoint(-48, -25, 2500, {.forwards = false});
    pros::delay(1100);
    intake.scoreHighGoal();
    pros::delay(2500);
    matchload.matchloadV(1);
    intake.intakeBlock();
    chassis.moveToPoint(-48, -62, 2000, {.maxSpeed = 60, .minSpeed = 40});
    pros::delay(2700);
    chassis.moveToPoint(-48, -26, 4000, {.forwards = false, .maxSpeed = 70});
    pros::delay(1150);
    intake.scoreHighGoal();
    pros::delay(2600);
    intake.stopIntake();*/

    
}


/*auton plans:
left qualification - score three in mid, pick up matchload, score in high, wing push
right qualification - score two in low, pick up matchload, score in high, wing push
solo win point - pick up matchload #1, score 3 in long, pikcup 3 balls, score 4 in mid, pick up 3 balls, pick up matchload #2, score 6 - 7 in high
elim 4 ball - pikcup three, pick up matchload, score 4 in high, wing push
elim 7 ball - pickup three, pick up matchload, score 7 in high, wing push
*/