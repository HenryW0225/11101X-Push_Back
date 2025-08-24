#pragma once

#include "pros/motors.hpp"

class Intake {
    public:
        //constructor
        Intake(pros::Motor bottomIntakeMotors, pros::Motor middleIntakeMotors, pros::Motor topIntakeMotors);

        //intake Motors
        pros::Motor bottomIntakeMotors;
        pros::Motor middleIntakeMotors;
        pros::Motor topIntakeMotors;

        //intake Functions
        void move_bottom_intake(double velocity);

        void move_middle_intake(double velocity);

        void move_top_intake(double velocity);

        void intake_block();

        void outtake_block();

        void score_middle_goal();

        void score_high_goal();

        void stop_intake();
    
        void intake_control();
};
