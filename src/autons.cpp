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
        chassis.setPose(9.5, 1.5, 0);
        intake.intakeBlock();
        chassis.turnToPoint(3.25, 24.5, 1000, {.minSpeed = 30, .earlyExitRange = 4});
        chassis.moveToPoint(6, 9, 4000, {.minSpeed = 65, .earlyExitRange = 0.5});
        chassis.moveToPoint(3.25, 24.5, 4000, {.maxSpeed = 15, .minSpeed = 10});
        chassis.turnToPoint(13, 34.4, 1500, {.forwards = false, .minSpeed = 35, .earlyExitRange = 2});
        chassis.moveToPoint(13, 34.4, 1500, {.forwards = false, .minSpeed = 20, .earlyExitRange = 0.5});
        intake.moveBottomIntake(-600);
        pros::delay(150);
        intake.stopIntake();
        pros::delay(500);
        intake.intakePneumaticV(1);
        intake.intakeOut();
        chassis.turnToPoint(-23, -2, 2500,{.minSpeed = 8, .earlyExitRange = 1});
        pros::delay(1150);
        intake.intakePneumaticV(0);
        //score middle goal
        chassis.moveToPoint(-20.5, -2, 3000,{.minSpeed = 20, .earlyExitRange = 2});
        matchload.matchloadV(1);
        intake.intakeBlock();
        chassis.turnToPoint(-23.25, -13, 2500,{.minSpeed = 20, .earlyExitRange = 1});
        chassis.moveToPoint(-23.25, -13, 1200, {.maxSpeed = 50, .minSpeed = 35});
        pros::delay(1200);
        //finish matchload #1
        chassis.moveToPoint(-23.25, 19.5, 2000, {.forwards = false, .maxSpeed = 70});
        pros::delay(1300);
        matchload.matchloadV(0);
        intake.scoreHighGoal();
        pros::delay(1600);
        intake.stopIntake();
        //finish score high goal
        chassis.moveToPoint(-23.25, 12, 3000, {.minSpeed = 30, .earlyExitRange = 2});
        chassis.turnToPoint(-14.25, 20, 2000, {.forwards = false, .minSpeed = 15, .earlyExitRange = 1});
        chassis.moveToPoint(-14.25, 20, 2000, {.forwards = false, .minSpeed = 10});
        chassis.turnToPoint(-12.2, 32, 2000, {.forwards = false, .minSpeed = 20, .earlyExitRange = 1});
        chassis.moveToPoint(-12.2, 32, 2000, {.forwards = false, .maxSpeed = 65, .minSpeed = 60});
        /*chassis.moveToPoint(-23, 17, 3000, {.minSpeed = 55, .earlyExitRange = 2});
        chassis.moveToPoint(-10, 14, 3000, {.minSpeed = 35, .earlyExitRange = 1});
        chassis.turnToPoint(-12.2, 32, 2000, {.forwards = false, .minSpeed = 20, .earlyExitRange = 1});
        chassis.moveToPoint(-12.2, 32, 2000, {.forwards = false, .maxSpeed = 65, .minSpeed = 60});*/
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
    chassis.moveToPoint(-23, 21, 1600, {.forwards = false, .maxSpeed = 40, .minSpeed = 10});
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
    //7ball
    chassis.setPose(-9.5, 1.5, 0);
    intake.intakeBlock();
    chassis.moveToPoint(1.5, 27, 4000, {.maxSpeed = 40, .minSpeed = 5, .earlyExitRange = 1});
    chassis.turnToPoint(24, 0, 2000);
    chassis.moveToPoint(24.5, 0, 3000);
    chassis.turnToPoint(24.5, -13.5, 2000);
    matchload.matchloadV(1);
    chassis.moveToPoint(24, -13.5, 1150, {.maxSpeed = 60, .minSpeed = 35});
    pros::delay(1150);
    chassis.moveToPoint(24.25, 22.25, 1600, {.forwards = false, .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 1});
    //intake.startJamTracking();
    pros::delay(650);
    intake.scoreHighGoal();
    matchload.matchloadV(0);
    pros::delay(2300);
    //intake.getJamDelay(2300);
    //intake.stopJamTracking();
    intake.stopIntake();
    chassis.moveToPoint(35.5, 11, 3000, {.minSpeed = 10, .earlyExitRange = 1});
    chassis.turnToPoint(35.5, 34.5, 2000, {.forwards = false, .minSpeed = 10});
    chassis.moveToPoint(35.5, 34.5, 2000, {.forwards = false, .maxSpeed = 65, .minSpeed = 60});
    chassis.moveToPoint(40, 34.5, 5000, {.forwards = false, .maxSpeed = 10, .minSpeed = 10});
    

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
        chassis.setPose(14, -4, 90);
        intake.intakeBlock();
        chassis.moveToPoint(-46, -4, 4000, {.minSpeed = 30, .earlyExitRange = 3});
        chassis.turnToPoint(-46, 22.5, 2000, {.minSpeed = 10, .earlyExitRange = 1});
        matchload.matchloadV(1);
        chassis.moveToPoint(-48, -13.5, 1150, {.maxSpeed = 60, .minSpeed = 35});
        pros::delay(1150);
        //matchload #1
        chassis.moveToPoint(-48, 22, 2000, {.forwards = false, .maxSpeed = 70, .minSpeed = 20, .earlyExitRange = 1});
        pros::delay(1000);
        matchload.matchloadV(0);
        intake.scoreHighGoal();
        pros::delay(1600);
        intake.stopIntake();
        //high goal #1
        chassis.turnToPoint(-24, 22.5, 2000, {.minSpeed = 35, .earlyExitRange = 4});
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
    chassis.setPose(18.5, -51, 90);
    chassis.moveToPoint(48, -51, 3000);
    matchload.matchloadV(1);
    wing.wingV(1);
    chassis.turnToPoint(47.25, -62, 5000);
    intake.intakeBlock();
    chassis.moveToPoint(47.25, -62, 2500, {.maxSpeed = 60, .minSpeed = 40});
    pros::delay(2700);
    chassis.moveToPoint(61.5, -40, 4000, {.forwards = false,.minSpeed = 25, .earlyExitRange = 2});
    chassis.turnToPoint(61, 30, 2000, {.forwards = false});
    matchload.matchloadV(0);
    chassis.moveToPoint(61, 30, 4000, {.forwards = false});
    chassis.moveToPoint(47.75, 40, 3000, {.forwards = false});
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
    intake.stopIntake();

    
}


/*auton plans:
left qualification - score three in mid, pick up matchload, score in high, wing push
right qualification - score two in low, pick up matchload, score in high, wing push
solo win point - pick up matchload #1, score 3 in long, pikcup 3 balls, score 4 in mid, pick up 3 balls, pick up matchload #2, score 6 - 7 in high
elim 4 ball - pikcup three, pick up matchload, score 4 in high, wing push
elim 7 ball - pickup three, pick up matchload, score 7 in high, wing push
*/