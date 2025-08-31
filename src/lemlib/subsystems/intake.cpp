#include "main.h"


Intake::Intake(pros::Motor bottomIntakeMotors, pros::Motor topIntakeMotors, pros::Optical colorSensor, pros::adi::DigitalOut intakePneumatic)
    : bottomIntakeMotors(bottomIntakeMotors),
      topIntakeMotors(topIntakeMotors),
      colorSensor(colorSensor),
      intakePneumatic(intakePneumatic) {}
      

void Intake::calibrate(bool red) {
    colorSortActive = true;
    if (red) { red_color_sort(); }
    else { blue_color_sort(); }
}

void Intake::move_bottom_intake(double velocity){
    bottomIntakeMotors.move_velocity(velocity);
}

void Intake::move_top_intake(double velocity){
    topIntakeMotors.move_velocity(velocity);
}

void Intake::intakePneumatic_v(int value) {
    intakePneumatic.set_value(value);
}

void Intake::intake_block() {
    move_bottom_intake(600);
    move_top_intake(50);
}

void Intake::outtake_block() {
    move_bottom_intake(-600);
    move_top_intake(600);
}

void Intake::score_middle_goal() {
    move_bottom_intake(600);
    move_top_intake(600);
}

void Intake::score_high_goal() {
    move_bottom_intake(600);
    move_top_intake(-600);
}

void Intake::stop_intake() {
    move_bottom_intake(0);
    move_top_intake(0);
}

void Intake::spit_out() {
    move_bottom_intake(600);
    move_top_intake(600);
}

bool Intake::color_detected(bool red) {
    if (red) {
        // red alliance - detecting against blue
        if ((colorSensor.get_hue() >= 350 || colorSensor.get_hue() <= 10) 
        /*&& (colorSensor.get_saturation() >= 0.6 && colorSensor.get_saturation() <= 1) 
        && (colorSensor.get_proximity() >= 250)*/) {
            return true;
        }
    }
    else {
        // blue alliance - detecting against red
        if ((colorSensor.get_hue() >= 200 && colorSensor.get_hue() <= 240) 
        /*&& (colorSensor.get_saturation() >= 0.5 && colorSensor.get_saturation() <= 0.9) 
        && (colorSensor.get_proximity() >= 250)*/) {
            return true;
        }
    }
    return false;
}

void Intake::red_color_sort() {
    colorSensor.set_led_pwm(100);
    colorSensor.set_integration_time(5);
    while (colorSortActive) {
        if (color_detected(true)) {
            while (color_detected(true)) {
                spit_out();
                pros::delay(10);
            } 
            pros::delay(250);
            stop_intake();
        } 
        pros::delay(10);
    }
}



void Intake::blue_color_sort() {
    colorSensor.set_led_pwm(100);
    colorSensor.set_integration_time(5);
    while (colorSortActive) {
        if (color_detected(false)) {
            while (color_detected(false)) {
                spit_out();
                pros::delay(10);
            } 
            pros::delay(250);
            stop_intake();
        } 
        pros::delay(10);
    }
}


