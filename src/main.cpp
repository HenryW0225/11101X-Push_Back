#pragma once
#include "main.h"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::MotorGroup leftMotors({-11, -12, -13}, pros::MotorGearset::blue); 
pros::MotorGroup rightMotors({20, 19, 18}, pros::MotorGearset::blue); 
pros::Motor bottomIntakeMotors(10, pros::MotorGearset::blue);
pros::Motor topIntakeMotors(15, pros::MotorGearset::blue);

pros::adi::DigitalOut matchLoadPneumatic('g');
pros::adi::DigitalOut intakePneumatic('h');
pros::adi::DigitalOut wingPneumatic('e');
pros::adi::DigitalOut parkPneumatic('f');

pros::Imu imu(17);

pros::Optical colorSensor(1);

// horizontal tracking wheel encoder. Rotation sensor, port 20, not reversed
pros::Rotation horizontalEnc(14);
// vertical tracking wheel encoder. Rotation sensor, port 11, reversed
pros::Rotation verticalEnc(4);
// horizontal tracking wheel. 2.75" diameter, 5.75" offset, back of the robot (negative)
lemlib::TrackingWheel horizontal(&horizontalEnc, 2, 5.13);
// vertical tracking wheel. 2.75" diameter, 2.5" offset, left of the robot (negative)
lemlib::TrackingWheel vertical(&verticalEnc, 2, 0.5);

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

Wing wing(wingPneumatic);

Park park(parkPneumatic);

void initialize() {
    pros::lcd::initialize(); 
    chassis.calibrate(); 

    // red alliance - true, blue alliance - false
    intake.calibrate(true);
}

void disabled() {}

void competitionInitialize() {}

// get a path used for pure pursuit
ASSET(example_txt); // '.' replaced with "_" to make c++ happy

//autons
void odomTest() {
    chassis.setPose(0, 0, 0);
    chassis.moveToPoint(0, 96, 10000, {.maxSpeed = 30});
}

void leftElim() {
    chassis.setPose(9, 1.5, 0);
    intake.intakeBlock();
    chassis.moveToPoint(0, 26, 5000, {.maxSpeed = 95});
    pros::delay(425);
    matchload.matchloadV(1);
    pros::delay(100);
    chassis.moveToPoint(-18.25, 40.15, 5000, {.maxSpeed = 70});
    pros::delay(150);
    matchload.matchloadV(0);
    pros::delay(400);
    chassis.moveToPoint(-12, 12, 5000, {.forwards = false});
    chassis.moveToPoint(-25, 8, 1000, {.forwards = false});
    chassis.turnToPoint(-23, -24, 1000);
    chassis.moveToPoint(-25, 24, 1200, {.forwards = false, .maxSpeed = 60});
    pros::delay(500);
    intake.outtakeBlock();
    pros::delay(200);
    intake.scoreHighGoal();
    pros::delay(2250);
    intake.stopIntake();
    intake.intakeBlock();
    matchload.matchloadV(1);
    chassis.moveToPoint(-24, -15, 1250, {.maxSpeed = 55});
    pros::delay(1565);
    chassis.moveToPoint(-25, 24, 1000, {.forwards = false, .maxSpeed = 70});
    pros::delay(1000);
    intake.scoreHighGoal();
    pros::delay(1350);
    chassis.moveToPoint(-25, 12, 1000, {.minSpeed = 10, .earlyExitRange = 3});
    chassis.moveToPoint(-25, 24, 1000, {.forwards = false, .minSpeed = 70});
}

void swp() {
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

void autonomous() {
    chassis.setBrakeMode(MOTOR_BRAKE_HOLD);
    odomTest();
    //leftElim();
    //swp();
    //rightElim();
    //simpleQual();
    //skills();
}

void opcontrol() {
    intake.colorSortActive = false;
    while (true) {
        int vert = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int horz = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
        chassis.arcade(vert, horz);

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) { intake.scoreHighGoal(); }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) { intake.outtakeBlock(); }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) { intake.intakeBlock(); }
        else { intake.stopIntake(); }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
            intake.colorSortActive = !intake.colorSortActive;
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
            matchload.matchloadChange();
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
            intake.intakePneumaticChange();
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
            wing.wingChange();
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
            park.parkChange();
        }

        pros::delay(10);
    }
}
