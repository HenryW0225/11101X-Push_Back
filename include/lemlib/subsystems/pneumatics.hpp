#pragma once

#include "api.h";

class Matchload {
    public:
        //constructor
        Matchload(pros::adi::DigitalOut matchloadpneumatic);

        //matchload pneumatic
        pros::adi::DigitalOut matchloadpneumatic;

        //matchload Functions
        void matchload_v(int value);
        void matchload_change();
 
        //matchload variables
        bool matchload_out = false;
};
