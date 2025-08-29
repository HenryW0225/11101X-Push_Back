#pragma once

#include "api.h"

class Intake {
    public:
        //constructor
        Intake(pros::Motor bottomIntakeMotors, pros::Motor topIntakeMotors, pros::Optical colorSensor, pros::adi::DigitalOut intakePneumatic);

        //intake Motors
        pros::Motor bottomIntakeMotors;
        pros::Motor topIntakeMotors;

        //color sensor
        pros::Optical colorSensor;

        //color sort pneumatic
        pros::adi::DigitalOut intakePneumatic;

        //intake Functions
        void move_bottom_intake(double velocity);

        void move_top_intake(double velocity);

        void intake_block();

        void outtake_block();

        void score_middle_goal();

        void score_high_goal();

        void stop_intake();
    
        void intake_control();

        void color_sort(bool red);

        //intake pneumatic functions
        void intakePneumatic_v(int value);

};
