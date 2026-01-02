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

        void scoreMiddleHigh();
    
        void intakeControl();

        void intakeOut();

        void intakeOutAuton();

        void intakeOutSkills();

        double intakeTemperature();

        //intake jam functions

        void intakeJam(bool async);
        
        // Jam tracking functions (for extending intake time in auton)
        void startJamTracking(); // Start tracking jams for current section
        void stopJamTracking();  // Stop tracking jams
        void resetJamCount();    // Reset jam counter
        int getJamCount();       // Get number of jams that occurred
        int getJamDelay(int baseDelay); // Get extended delay based on jam count (adds 200ms per jam)

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

        double desiredBottomVelocity = 0;
        
        // Jam tracking variables
        int jamCount = 0;
        bool jamTrackingActive = false;
};
