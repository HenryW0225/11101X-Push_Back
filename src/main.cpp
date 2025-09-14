#pragma once
#include "main.h"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::MotorGroup leftMotors({-11, -12, -13}, pros::MotorGearset::blue); 
pros::MotorGroup rightMotors({20, 19, 18}, pros::MotorGearset::blue); 
pros::Motor bottomIntakeMotors(9, pros::MotorGearset::blue);
pros::Motor topIntakeMotors(7, pros::MotorGearset::blue);

pros::adi::DigitalOut matchLoadPneumatic('a');
pros::adi::DigitalOut intakePneumatic('b');

pros::Imu imu(17);

pros::Optical colorSensor(1);


// horizontal tracking wheel encoder. Rotation sensor, port 20, not reversed
pros::Rotation horizontalEnc(14);
// vertical tracking wheel encoder. Rotation sensor, port 11, reversed
pros::Rotation verticalEnc(4);
// horizontal tracking wheel. 2.75" diameter, 5.75" offset, back of the robot (negative)
lemlib::TrackingWheel horizontal(&horizontalEnc, 1.99, 5.013);
// vertical tracking wheel. 2.75" diameter, 2.5" offset, left of the robot (negative)
lemlib::TrackingWheel vertical(&verticalEnc, 1.99, 0);

lemlib::Drivetrain drivetrain(&leftMotors, 
                              &rightMotors, 
                              11, // 10 inch track width
                              lemlib::Omniwheel::OLD_325, // using new 4" omnis
                              450, // drivetrain rpm is 360
                              2 // horizontal drift is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
lemlib::ControllerSettings linearController(4.5, // (kP)
                                            0, // (kI)
                                            3, // (kD)
                                            3, //
                                            1, // small error range, in inches
                                            500, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            1000, // large error range timeout, in milliseconds
                                            20 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(1.9, // (kP)
                                             0, // (kI)
                                             12.5, // (kD)
                                             3, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

// sensors for odometry
lemlib::OdomSensors sensors(&vertical, 
                            nullptr, 
                            &horizontal, 
                            nullptr,
                            &imu
);

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttleCurve(10, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steerCurve(10, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

// create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);

Intake intake(bottomIntakeMotors, topIntakeMotors, colorSensor, intakePneumatic);

Matchload matchload(matchLoadPneumatic);

void initialize() {
    pros::lcd::initialize(); 
    chassis.calibrate(); 

    // red alliance - true, blue alliance - false
    intake.calibrate(true);
}

void disabled() {}

void competition_initialize() {}

// get a path used for pure pursuit
ASSET(example_txt); // '.' replaced with "_" to make c++ happy


//autons
void odomTest() {
    /*chassis.turnToPoint(24, 0, 5000);
    pros::delay(250);
    chassis.turnToPoint(0, -24, 5000);
    pros::delay(250);
    chassis.turnToPoint(-24, 0, 5000);
    pros::delay(250);
    chassis.turnToPoint(0, 24, 5000);
    pros::delay(250);
    chassis.turnToPoint(24, 0, 5000);
    pros::delay(250);
    chassis.turnToPoint(0, -24, 5000);
    pros::delay(250);
    chassis.turnToPoint(-24, 0, 5000);
    pros::delay(250);
    chassis.turnToPoint(0, 24, 5000);
    pros::delay(250);
    chassis.turnToPoint(24, 0, 5000);
    pros::delay(250);
    chassis.turnToPoint(0, -24, 5000);
    pros::delay(250);
    chassis.turnToPoint(-24, 0, 5000);
    pros::delay(250);
    chassis.turnToPoint(0, 24, 5000);
    pros::delay(250);
    chassis.turnToPoint(24, 0, 5000);
    pros::delay(250);
    chassis.turnToPoint(0, -24, 5000);
    pros::delay(250);
    chassis.turnToPoint(-24, 0, 5000);
    pros::delay(250);
    chassis.turnToPoint(0, 24, 5000);
    pros::delay(250);
    chassis.turnToPoint(24, 0, 5000);
    pros::delay(250);
    chassis.turnToPoint(0, -24, 5000);
    pros::delay(250);
    chassis.turnToPoint(-24, 0, 5000);
    pros::delay(250);
    chassis.turnToPoint(0, 24, 5000);
    pros::delay(250);*/

    /*chassis.moveToPoint(0, 24, 5000, {.maxSpeed = 67});
    chassis.turnToPoint(24, 24, 5000, {.maxSpeed = 67});
    chassis.moveToPoint(24, 24, 5000, {.maxSpeed = 67});
    //chassis.moveToPoint(0, 48, 5000, {.forwards = false}); 
    //chassis.turnToPoint(0, 96, 5000);
    //chassis.moveToPoint(0, 0, 5000, {.forwards = false});
    chassis.turnToPoint(24, 0, 5000, {.maxSpeed = 67});
    chassis.moveToPoint(24, 0, 5000, {.maxSpeed = 67});
    chassis.turnToPoint(0, 0, 5000, {.maxSpeed = 67});
    chassis.moveToPoint(0, 0, 5000, {.maxSpeed = 67});
    chassis.turnToPoint(0, 24, 5000, {.maxSpeed = 67});*/
    chassis.moveToPose(24, 24, 90, 5000, {.lead = 0.3});
}

void leftElim() {
    chassis.setPose(9, 1.5, 0);
    intake.intake_block();
    chassis.moveToPoint(0, 26, 5000, {.maxSpeed = 95});
    pros::delay(425);
    matchload.matchload_v(1);
    pros::delay(100);
    chassis.moveToPoint(-18.25, 40.15, 5000, {.maxSpeed = 70});
    pros::delay(150);
    matchload.matchload_v(0);
    pros::delay(400);
    //matchload.matchload_v(1);
    //pros::delay(150);
    chassis.moveToPoint(-12, 12, 5000, {.forwards = false});
    chassis.moveToPoint(-24, 8, 1000, {.forwards = false});
    chassis.turnToPoint(-22, -24, 1000);
    chassis.moveToPoint(-24, 24, 1200, {.forwards = false, .maxSpeed = 60});
    pros::delay(500);
    intake.outtake_block();
    pros::delay(200);
    intake.score_high_goal();
    pros::delay(2250);
    //chassis.turnToPoint(-24, 24, 1000);
    intake.stop_intake();
    intake.intake_block();
    matchload.matchload_v(1);
    chassis.moveToPoint(-22, -15, 1250, {.maxSpeed = 55});
    pros::delay(1565);
    chassis.moveToPoint(-24, 24, 1000, {.forwards = false, .maxSpeed = 80});
    pros::delay(900);
    intake.score_high_goal();
    pros::delay(1350);
    chassis.moveToPoint(-24, 12, 1000, {.minSpeed = 10, .earlyExitRange = 3});
    chassis.moveToPoint(-24, 24, 1000, {.forwards = false, .minSpeed = 70});
    /*matchload.matchload_v(0);
    chassis.moveToPoint(24, 12, 5000);
    chassis.moveToPoint(24, 18, 5000, {.forwards = false});*/
}

void SWP() {
    chassis.setPose(-2, -7.75, 0);
    chassis.moveToPoint(-2, 21, 5000,{.minSpeed = 5, .earlyExitRange = 1});
    matchload.matchload_v(1);
    chassis.turnToPoint(-24, 23, 5000, {.minSpeed = 5, .earlyExitRange = 1});
    intake.intake_block();
    chassis.moveToPoint(-11.5, 23, 1120, {.maxSpeed = 65, .minSpeed = 55});
    pros::delay(1000);
    chassis.moveToPoint(20.25, 23, 1500, {.forwards = false, .maxSpeed = 110});
    pros::delay(750);
    intake.score_high_goal();
    pros::delay(950);
    chassis.moveToPoint(10, 23, 5000, {.minSpeed = 10, .earlyExitRange = 1});
    chassis.moveToPoint(10, 10, 5000, {.minSpeed = 10, .earlyExitRange = 1});
    intake.stop_intake();
    intake.intake_block();
    matchload.matchload_v(0);
    chassis.moveToPoint(27, -1.25, 1250);
    pros::delay(375);
    matchload.matchload_v(1);
    chassis.turnToPoint(0, 30.25, 1500, {.minSpeed = 5});
    chassis.moveToPoint(37.5, -17, 1000, {.forwards = false, .maxSpeed = 40});
    intake.outtake_block();
    pros::delay(300);
    intake.stop_intake();
    intake.intakePneumatic_v(1);
    intake.score_high_goal();
    pros::delay(1100);
    intake.stop_intake();
    matchload.matchload_v(0);
    chassis.moveToPoint(24, 0, 1800, {.minSpeed = 10, .earlyExitRange = 1});
    intake.score_high_goal();
    pros::delay(125);
    intake.stop_intake();
    intake.intakePneumatic_v(0);
    pros::delay(100);
    intake.intake_block();
    chassis.turnToPoint(20, -45.5, 2000, {.maxSpeed = 80, .minSpeed = 5});
    chassis.moveToPoint(20, -45.5, 1000, {.minSpeed = 10, .earlyExitRange = 1});
    pros::delay(745);
    matchload.matchload_v(1);
    chassis.turnToPoint(0, -67.25, 2000, {.minSpeed = 10, .earlyExitRange = 1});
    chassis.moveToPoint(0, -67.25, 3000, {.minSpeed = 10, .earlyExitRange = 1});
    chassis.turnToPoint(-20, -66.5, 2000, {.minSpeed = 20, .earlyExitRange = 1});
    matchload.matchload_v(0);
    chassis.moveToPoint(19, -69, 5000, {.forwards = false, .maxSpeed = 50, .minSpeed = 10, .earlyExitRange = 1});
    pros::delay(340);
    intake.score_high_goal();
    pros::delay(700);
    chassis.moveToPoint(17, -68, 1000, {.minSpeed = 10, .earlyExitRange = 1});


}

void rightElim() {
    chassis.setPose(-9, 1.5, 0);
    intake.intake_block();
    chassis.moveToPoint(0, 26, 5000, {.maxSpeed = 95});
    pros::delay(425);
    matchload.matchload_v(1);
    pros::delay(100);
    chassis.moveToPoint(18.25, 40.15, 5000, {.maxSpeed = 70});
    pros::delay(150);
    matchload.matchload_v(0);
    pros::delay(400);
    //matchload.matchload_v(1);
    //pros::delay(150);
    chassis.moveToPoint(12, 12, 5000, {.forwards = false});
    chassis.moveToPoint(24, 8, 1000, {.forwards = false});
    chassis.turnToPoint(22, -24, 1000);
    chassis.moveToPoint(24, 24, 1200, {.forwards = false, .maxSpeed = 60});
    pros::delay(500);
    intake.outtake_block();
    pros::delay(200);
    intake.score_high_goal();
    pros::delay(2250);
    //chassis.turnToPoint(-24, 24, 1000);
    intake.stop_intake();
    intake.intake_block();
    matchload.matchload_v(1);
    chassis.moveToPoint(22, -15, 1250, {.maxSpeed = 55});
    pros::delay(1565);
    chassis.moveToPoint(24, 24, 1000, {.forwards = false, .maxSpeed = 80});
    pros::delay(900);
    intake.score_high_goal();
    pros::delay(1350);
    chassis.moveToPoint(24, 12, 1000, {.minSpeed = 10, .earlyExitRange = 3});
    chassis.moveToPoint(24, 24, 1000, {.forwards = false, .minSpeed = 70});
    /*matchload.matchload_v(0);
    chassis.moveToPoint(24, 12, 5000);
    chassis.moveToPoint(24, 18, 5000, {.forwards = false});*/
}

void simpleQual() {
    chassis.setPose(-2, -7.75, 0);
    chassis.moveToPoint(-2, 21, 5000,{.minSpeed = 5, .earlyExitRange = 1});
    matchload.matchload_v(1);
    chassis.turnToPoint(-24, 23, 5000, {.minSpeed = 5, .earlyExitRange = 1});
    intake.intake_block();
    chassis.moveToPoint(-11.5, 23, 1120, {.maxSpeed = 65, .minSpeed = 55});
    pros::delay(875);
    chassis.moveToPoint(20.25, 23, 1500, {.forwards = false, .maxSpeed = 110});
    pros::delay(750);
    intake.score_high_goal();
    pros::delay(1500);
    chassis.moveToPoint(10, 23, 5000, {.minSpeed = 10, .earlyExitRange = 1});
    chassis.moveToPoint(10, 10, 5000, {.minSpeed = 10, .earlyExitRange = 1});
    intake.stop_intake();
    intake.intake_block();
    matchload.matchload_v(0);
    chassis.moveToPoint(27, -3, /*1250*/ 5000, {.maxSpeed = 25});
    //pros::delay(400);
    //matchload.matchload_v(1);
    chassis.turnToPoint(0, 30.25, 1500, {.minSpeed = 5});
    chassis.moveToPoint(37.5, -17, 1000, {.forwards = false, .maxSpeed = 65});
    intake.outtake_block();
    pros::delay(300);
    intake.stop_intake();
    intake.intakePneumatic_v(1);
    intake.score_high_goal();
    pros::delay(3000);
    intake.stop_intake();
    //matchload.matchload_v(0);
    chassis.moveToPoint(24, 0, 1800, {.minSpeed = 10, .earlyExitRange = 1});
    intake.score_high_goal();
    pros::delay(125);
    intake.stop_intake();
    intake.intakePneumatic_v(0);
}

void skills() {
    chassis.setPose(2, -7.75, 0);
    chassis.moveToPoint(2, 21, 5000,{.minSpeed = 5, .earlyExitRange = 1});
    matchload.matchload_v(1);
    chassis.turnToPoint(24, 23, 5000, {.minSpeed = 5, .earlyExitRange = 1});
    intake.intake_block();
    chassis.moveToPoint(11.5, 23, 1120, {.maxSpeed = 65, .minSpeed = 55});
    pros::delay(2000);
    chassis.moveToPoint(-20.25, 23, 1500, {.forwards = false, .maxSpeed = 110});
    pros::delay(1500);
    intake.score_high_goal();
    pros::delay(7500);
    chassis.moveToPoint(-10, 23, 5000, {.minSpeed = 10, .earlyExitRange = 1});
    chassis.turnToPoint(12, 0, 5000);
    chassis.moveToPoint(12, 0, 5000);
    chassis.turnToPoint(12, -36, 5000);
    chassis.moveToPoint(12, -36, 15000, {.maxSpeed = 65});
}


void autonomous() {
    chassis.setBrakeMode(MOTOR_BRAKE_HOLD);
    //odomTest();
    //leftElim();
    //SWP();
    //rightElim();
    //simpleQual();
    skills();

    /*chassis.moveToPoint(0, 48, 5000);
    //pros::delay(500);
    chassis.turnToPoint(48, 48, 5000);
    chassis.moveToPoint(48, 48, 5000);
    chassis.moveToPoint(0, 48, 5000, {.forwards = false}); 
    chassis.turnToPoint(0, 96, 5000);
    chassis.moveToPoint(0, 0, 5000, {.forwards = false});*/
}


void opcontrol() {
    intake.colorSortActive = false;
    while (true) {
        int vert = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int horz = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
        chassis.arcade(vert, horz);

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) { intake.score_high_goal(); }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) { intake.outtake_block(); }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) { intake.intake_block(); }
        else { intake.stop_intake(); }


        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
            if (intake.colorSortActive) { intake.colorSortActive = false; } 
            else { intake.colorSortActive = true; }
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
            matchload.matchload_change();
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
            intake.intakePneumatic_change();
        }

        pros::delay(10);
    }
}



