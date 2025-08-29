#include "main.h"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::MotorGroup leftMotors({-9, -19, -20}, pros::MotorGearset::blue); 
pros::MotorGroup rightMotors({11, 12, 14}, pros::MotorGearset::blue); 
pros::Motor bottomIntakeMotors(13, pros::MotorGearset::blue);
pros::Motor topIntakeMotors(18, pros::MotorGearset::blue);

pros::adi::DigitalOut matchLoadPneumatic('h');
pros::adi::DigitalOut colorSortPneumatic('a');


pros::Imu imu(10);

pros::Optical colorSensor(1);


// horizontal tracking wheel encoder. Rotation sensor, port 20, not reversed
pros::Rotation horizontalEnc(20);
// vertical tracking wheel encoder. Rotation sensor, port 11, reversed
pros::Rotation verticalEnc(-11);
// horizontal tracking wheel. 2.75" diameter, 5.75" offset, back of the robot (negative)
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_275, -5.75);
// vertical tracking wheel. 2.75" diameter, 2.5" offset, left of the robot (negative)
lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_275, -2.5);

lemlib::Drivetrain drivetrain(&leftMotors, 
                              &rightMotors, 
                              10, // 10 inch track width
                              lemlib::Omniwheel::NEW_4, // using new 4" omnis
                              360, // drivetrain rpm is 360
                              2 // horizontal drift is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
lemlib::ControllerSettings linearController(10, // (kP)
                                            0, // (kI)
                                            3, // (kD)
                                            3, //
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            20 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(2, // (kP)
                                             0, // (kI)
                                             10, // (kD)
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
lemlib::ExpoDriveCurve throttleCurve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steerCurve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

// create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);

Intake intake(bottomIntakeMotors, topIntakeMotors, colorSensor, colorSortPneumatic);

Matchload matchload(matchLoadPneumatic);

void initialize() {
    pros::lcd::initialize(); 
    chassis.calibrate(); 
}

void disabled() {}

void competition_initialize() {}

// get a path used for pure pursuit
ASSET(example_txt); // '.' replaced with "_" to make c++ happy


void autonomous() {
}


void opcontrol() {
    while (true) {
        int vert = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int horz = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
        chassis.arcade(vert, horz);
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) { intake.score_high_goal(); }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) { intake.outtake_block(); }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) { intake.intake_block(); }
        else { intake.stop_intake(); }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
            matchload.matchload_v(1);
        }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
            matchload.matchload_v(0);
        }

        pros::delay(10);
    }
}
