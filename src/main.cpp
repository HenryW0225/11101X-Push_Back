#include "main.h"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::MotorGroup leftMotors({-11, -12, -13}, pros::MotorGearset::blue); 
pros::MotorGroup rightMotors({20, 19, 18}, pros::MotorGearset::blue); 
pros::Motor bottomIntakeMotors(9, pros::MotorGearset::blue);
pros::Motor topIntakeMotors(2, pros::MotorGearset::blue);

pros::adi::DigitalOut matchLoadPneumatic('h');
pros::adi::DigitalOut intakePneumatic('a');

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
lemlib::ControllerSettings angularController(1.8, // (kP)
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


void autonomous() {
    chassis.setBrakeMode(MOTOR_BRAKE_HOLD);
    odomTest();
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

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
            matchload.matchload_change();
        }

        pros::delay(10);
    }
}
