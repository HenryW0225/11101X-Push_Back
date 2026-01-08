#include "main.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/odom.hpp"
#include "pros/distance.hpp"
#include "pros/motors.h"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::MotorGroup leftMotors({-13, -12, -11}, pros::MotorGearset::blue); 
pros::MotorGroup rightMotors({18, 20, 19}, pros::MotorGearset::blue); 
pros::Motor bottomIntakeMotors(16, pros::MotorGearset::blue);
pros::Motor topIntakeMotors(17, pros::MotorGearset::blue);

pros::adi::DigitalOut matchLoadPneumatic('h');
pros::adi::DigitalOut intakePneumatic('g');
pros::adi::DigitalOut wingPneumatic('f');

pros::Imu imu(15);

pros::Optical colorSensor(2);

// horizontal tracking wheel encoder. Rotation sensor, port 20, not reversed
pros::Rotation horizontalEnc(14);
// vertical tracking wheel encoder. Rotation sensor, port 11, reversed
pros::Rotation verticalEnc(10);
// horizontal tracking wheel. 2.75" diameter, 5.75" offset, back of the robot (negative)
lemlib::TrackingWheel horizontal(&horizontalEnc, 2, -2.25);
// vertical tracking wheel. 2.75" diameter, 2.5" offset, left of the robot (negative)
lemlib::TrackingWheel vertical(&verticalEnc, 2, -0.4125);

pros::Distance distanceLeftBack(7);
pros::Distance distanceLeftFront(10);
pros::Distance distanceBack(10);

lemlib::Drivetrain drivetrain(&leftMotors, 
                              &rightMotors, 
                              10.325, // 11.05 inch track width
                              lemlib::Omniwheel::OLD_325, // using old 3.25" omnis
                              450, // drivetrain rpm is 450
                              2 // horizontal drift is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
lemlib::ControllerSettings linearController(4.2, // (kP) 4.067
                                            0, // (kI)
                                            4, // (kD)
                                            0, //
                                            0.8, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            300, // large error range timeout, in milliseconds
                                            10 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(1.65 , // (kP)1.7 1.6
                                             0, // (kI)
                                            11, // (kD)11 10.5
                                             0, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             2, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             10 // maximum acceleration (slew)
);


// heading motion controller
lemlib::ControllerSettings headingController(0.6, // (kP) 2 1
                                             0, // (kI)
                                             11, // (kD) 20 1
                                             0, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             2, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

// extra lateral motion controller
lemlib::ControllerSettings linearControllerExtra(4.2, // (kP) 4.067
                                                 0, // (kI)
                                                 4, // (kD)
                                                 0, //
                                                 0.8, // small error range, in inches
                                                 100, // small error range timeout, in milliseconds
                                                 3, // large error range, in inches
                                                 300, // large error range timeout, in milliseconds
                                                 10 // maximum acceleration (slew)
);

// extra angular motion controller
lemlib::ControllerSettings angularControllerExtra(1.9 , // (kP)1.7 1.6
                                                  0, // (kI)
                                                  11, // (kD)11 10.5
                                                  0, // anti windup
                                                  1, // small error range, in degrees
                                                  100, // small error range timeout, in milliseconds
                                                  2, // large error range, in degrees
                                                  500, // large error range timeout, in milliseconds
                                                  0 // maximum acceleration (slew)
);

// extra heading motion controller
lemlib::ControllerSettings headingControllerExtra(3, // (kP) 2 1
                                                  0, // (kI)
                                                  11, // (kD) 20 1
                                                  0, // anti windup
                                                  1, // small error range, in degrees
                                                  100, // small error range timeout, in milliseconds
                                                  2, // large error range, in degrees
                                                  500, // large error range timeout, in milliseconds
                                                  0 // maximum acceleration (slew)
);
/*
lemlib::ControllerSettings angularControllerLong(3, // (kP) 2
                                             0, // (kI)
                                             20, // (kD) 20
                                             0, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

lemlib::ControllerSettings angularControllerShort(1.9 , // (kP) 2
                                             0, // (kI)
                                             11, // (kD) 20
                                             0, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             2, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

lemlib::ControllerSettings angularControllerSwing(2.2, // (kP) 2
                                             0, // (kI)
                                             11, // (kD) 20
                                             0, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             2, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);
*/
// sensors for odometry
lemlib::OdomSensors sensors(&vertical, 
                            nullptr, 
                            &horizontal, 
                            nullptr,
                            &imu,
                            &distanceLeftBack,
                            &distanceLeftFront
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
lemlib::Chassis chassis(drivetrain, linearController, angularController, headingController, linearControllerExtra, angularControllerExtra, headingControllerExtra, sensors);

Intake intake(bottomIntakeMotors, topIntakeMotors, colorSensor, intakePneumatic);

Matchload matchload(matchLoadPneumatic);

Wing wing(wingPneumatic);

void initialize() {
    pros::screen::set_eraser(pros::Color::black);
    pros::screen::set_pen(pros::Color::white);
    chassis.calibrate(); 
    

    // red alliance - true, blue alliance - false
    intake.calibrate(true);
    matchload.calibrate();
    wing.calibrate();
}

void disabled() {}

void competitionInitialize() {}

// get a path used for pure pursuit
ASSET(example_txt); // '.' replaced with "_" to make c++ happy

void autonomous() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

    intake.driverControl = false;
    intake.intakeJam(true);
   
    // Start the intake jam task
    pros::Task printCoordsTask([]() {
        bool thetaExceeded90 = false; // Track if theta has ever exceeded 90
        while (true) {
            lemlib::Pose pose = chassis.getPose();
            pros::screen::print(pros::E_TEXT_MEDIUM, 0, "x: %.2f",pose.x);
            pros::screen::print(pros::E_TEXT_MEDIUM, 1, "y: %.2f", pose.y);
            pros::screen::print(pros::E_TEXT_MEDIUM, 2, "theta: %.2f", pose.theta);
            pros::screen::print(pros::E_TEXT_MEDIUM, 4, "intake temp: %.2f", intake.intakeTemperature());
           // pros::screen::print(pros::E_TEXT_MEDIUM, 3, "left voltage: %.2f", leftMotors.get_voltage_all());
            
            // Check if theta is greater than 90 degrees (only set flag, never clear it)
            if (pose.theta > 91) {
                thetaExceeded90 = true;
            }
            
            // Show warning if theta has ever exceeded 90
            if (thetaExceeded90) {
                pros::screen::print(pros::E_TEXT_MEDIUM, 3, "WARNING: Theta > 91!");
            } else {
                pros::screen::print(pros::E_TEXT_MEDIUM, 3, ""); // Clear the warning
            }
            
            pros::delay(20); // Update every 100ms
        }
    });
    //odomTest();
    leftQual();
    //rightQual();
    //soloWinPoint();
    //leftElim();
    //rightElim();
    //skills();
}

void opcontrol() {

    intake.driverControl = true;
    intake.colorSortActive = false;
    while (true) {
        int vert = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int horz = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
        if (fabs(vert) < 7) vert = 0;
       // if (fabs(horz) < 7) horz = 0;
        chassis.arcade(vert, horz);
       
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) { intake.scoreHighGoal(); }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) { intake.outtakeBlock(); }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) { intake.intakeBlock(); }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) { intake.intakeOut();}
        //else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) { intake.intakeOutSkills();}
        else { intake.stopIntake(); }

        //if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
        //    intake.colorSortActive = !intake.colorSortActive;
        //}

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
            matchload.matchloadChange();
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
            intake.intakePneumaticChange();
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
            wing.wingChange();
        }
        pros::delay(10);
    }
}

// test updates