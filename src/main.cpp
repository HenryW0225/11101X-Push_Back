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
pros::Rotation horizontalEnc(-14);
// vertical tracking wheel encoder. Rotation sensor, port 11, reversed
pros::Rotation verticalEnc(-9);
// horizontal tracking wheel. 2.75" diameter, 5.75" offset, back of the robot (negative)
lemlib::TrackingWheel horizontal(&horizontalEnc, 2, -2.2);
// vertical tracking wheel. 2.75" diameter, 2.5" offset, left of the robot (negative)
lemlib::TrackingWheel vertical(&verticalEnc, 2, -0.2);

lemlib::Drivetrain drivetrain(&leftMotors, 
                              &rightMotors, 
                              10.95, // 11 inch track width
                              lemlib::Omniwheel::OLD_325, // using old 3.25" omnis
                              450, // drivetrain rpm is 450
                              2 // horizontal drift is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
lemlib::ControllerSettings linearController(3.7, // (kP)
                                            0, // (kI)
                                            10, // (kD)
                                            0, //
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            20 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(1.9, // (kP)
                                             0, // (kI)
                                             12.5, // (kD)
                                             0, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);


// heading motion controller
lemlib::ControllerSettings headingController(1, // (kP) 2
                                             0, // (kI)
                                             20, // (kD) 20
                                             0, // anti windup
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
lemlib::Chassis chassis(drivetrain, linearController, angularController, headingController, sensors);

Intake intake(bottomIntakeMotors, topIntakeMotors, colorSensor, intakePneumatic);

Matchload matchload(matchLoadPneumatic);

Wing wing(wingPneumatic);

Park park(parkPneumatic);

void initialize() {
    pros::lcd::initialize(); 
    chassis.calibrate(); 

    // red alliance - true, blue alliance - false
    intake.calibrate(true);
    matchload.calibrate();
    wing.calibrate();
    park.calibrate();
}

void disabled() {}

void competitionInitialize() {}

// get a path used for pure pursuit
ASSET(example_txt); // '.' replaced with "_" to make c++ happy



void odomTest() {
    chassis.setPose(0, 0, 0);
    chassis.moveToPoint(0, 48, 5000);
    chassis.turnToPoint(-48, 48, 5000);
    chassis.moveToPoint(-48, 48, 5000);
    chassis.turnToPoint(-48, 0, 5000);
    chassis.moveToPoint(-48, 0, 5000);
    chassis.turnToPoint(0, 0, 5000);
    chassis.moveToPoint(0, 0, 5000);
    chassis.turnToPoint(0, 48, 5000);
}

void autonomous() {
    chassis.setBrakeMode(MOTOR_BRAKE_HOLD);
    intake.driverControl = false;
    intake.intakeJam(true); // Start the intake jam task
    //odomTest();
    //simpleQual();
    //soloWinPoint();
    //leftElim();
    //rightElim();
    skills();
}

void opcontrol() {
    intake.driverControl = true;
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