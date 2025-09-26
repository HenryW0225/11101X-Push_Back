#pragma once

#include "api.h";

class Matchload {
    public:
        //constructor
        Matchload(pros::adi::DigitalOut matchLoadPneumatic);

        //matchload pneumatic
        pros::adi::DigitalOut matchLoadPneumatic;

        //matchload Functions
        void matchloadV(int value);
        void matchloadChange();
 
        //matchload variables
        bool matchloadOut = false;
};

class Wing {
    public:
        //constructor
        Wing(pros::adi::DigitalOut wingPneumatic);

        //wing pneumatic
        pros::adi::DigitalOut wingPneumatic;

        //wing Functions
        void wingV(int value);
        void wingChange();
 
        //matchload variables
        bool wingUp = false;
};
