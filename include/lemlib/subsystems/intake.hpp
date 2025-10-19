#pragma once

#include "api.h"

class Intake {
    public:
        //constructor
        Intake(pros::Motor bottomIntakeMotors, pros::Motor topIntakeMotors, pros::Optical colorSensor, pros::adi::DigitalOut intakePneumatic);

        //initialize
        void calibrate(bool red);

        //intake Motors
        pros::Motor bottomIntakeMotors;
        pros::Motor topIntakeMotors;

        //color sensor
        pros::Optical colorSensor;

        //color sort pneumatic
        pros::adi::DigitalOut intakePneumatic;

        //intake Functions
        void moveBottomIntake(double velocity);

        void moveTopIntake(double velocity);

        void intakeBlock();

        void outtakeBlock();
        
        void scoreMiddleGoal();

        void scoreHighGoal();

        void stopIntake();
    
        void intakeControl();

        //intake jam functions

        void intakeJam(bool async);

        //color sort functions

        void spitOut();
        
        bool colorDetected(bool red);

        void redColorSort();

        static int redColorSortTask();

        void blueColorSort();

        static int blueColorSortTask();

        //intake pneumatic functions

        void intakePneumaticV(int value);

        void intakePneumaticChange();

        //intake variables

        bool colorSortActive = true;
        
        bool intakePneumaticActive = true;

        bool driverControl = false;
};
