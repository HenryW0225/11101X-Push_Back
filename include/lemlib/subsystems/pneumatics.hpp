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
 
        //wing variables
        bool wingUp = false;
};

class Park {
    public:
        //constructor
        Park(pros::adi::DigitalOut parkPneumatic);

        //park pneumatic
        pros::adi::DigitalOut parkPneumatic;

        //park Functions
        void parkV(int value);
        void parkChange();
 
        //parking variables
        bool parkDown = false;
};