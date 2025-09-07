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
pros::Rotation verticalEnc(15);
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
    chassis.moveToPoint(0, 26, 5000, {.maxSpeed = 100});
    pros::delay(500);
    matchload.matchload_v(1);
    pros::delay(150);
    chassis.moveToPoint(-17.75, 41, 5000, {.maxSpeed = 80});
    pros::delay(150);
    matchload.matchload_v(0);
    pros::delay(350);
    matchload.matchload_v(1);
    pros::delay(200);
    chassis.moveToPoint(-12, 8, 5000, {.forwards = false});
    chassis.moveToPoint(-27, 4, 1000, {.forwards = false});
    chassis.turnToPoint(-25.5, -24, 1000);
    chassis.moveToPoint(-27, 24, 1000, {.forwards = false});
    pros::delay(400);
    intake.outtake_block();
    pros::delay(100);
    intake.score_high_goal();
    pros::delay(2000);
    //chassis.turnToPoint(-24, 24, 1000);
    intake.stop_intake();
    intake.intake_block();
    chassis.moveToPoint(-25, -16, 1250, {.maxSpeed = 70});
    pros::delay(1650);
    chassis.moveToPoint(-26, 24, 5000, {.forwards = false});
    pros::delay(1000);
    intake.score_high_goal();
    pros::delay(1250);
    chassis.moveToPoint(-25, 16, 1000);
    chassis.moveToPoint(-25, 24, 1000, {.forwards = false});
    /*matchload.matchload_v(0);
    chassis.moveToPoint(24, 12, 5000);
    chassis.moveToPoint(24, 18, 5000, {.forwards = false});*/
}



void autonomous() {
    chassis.setBrakeMode(MOTOR_BRAKE_HOLD);
    //odomTest();
    leftElim();
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



