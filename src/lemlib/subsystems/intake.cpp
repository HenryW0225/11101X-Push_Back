#include "main.h"

Intake::Intake(pros::Motor bottomIntakeMotors, pros::Motor topIntakeMotors, pros::Optical colorSensor, pros::adi::DigitalOut intakePneumatic)
    : bottomIntakeMotors(bottomIntakeMotors),
      topIntakeMotors(topIntakeMotors),
      colorSensor(colorSensor),
      intakePneumatic(intakePneumatic) {}
      
void Intake::calibrate(bool red) {
    colorSortActive = true;
    intakePneumaticV(0);
    intakePneumaticActive = true;
    topIntakeMotors.set_brake_mode(MOTOR_BRAKE_HOLD);
    //if (red) { redColorSort(); }
    //else { blueColorSort(); }
}

void Intake::moveBottomIntake(double velocity){
    bottomIntakeMotors.move_velocity(velocity);
}

void Intake::moveTopIntake(double velocity){
    topIntakeMotors.move_velocity(velocity);
}

void Intake::intakePneumaticV(int value) {
    intakePneumatic.set_value(value);
}

void Intake::intakeBlock() {
    moveBottomIntake(600);
    moveTopIntake(0);
}

void Intake::outtakeBlock() {
    moveBottomIntake(-600);
    moveTopIntake(600);
}

void Intake::scoreMiddleGoal() {
    moveBottomIntake(200);
    moveTopIntake(-200);
}

void Intake::scoreHighGoal() {
    moveBottomIntake(600);
    moveTopIntake(-600);
}

void Intake::stopIntake() {
    moveBottomIntake(0);
    moveTopIntake(0);
}

void Intake::spitOut() {
    moveBottomIntake(600);
    moveTopIntake(600);
}

void Intake::intakePneumaticChange() {
    if (intakePneumaticActive) {
        intakePneumaticV(1);
        intakePneumaticActive = false;
    }
    else {
        intakePneumaticV(0);
        intakePneumaticActive = true;
    }
}

bool Intake::colorDetected(bool red) {
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

void Intake::redColorSort() {
    colorSensor.set_led_pwm(100);
    colorSensor.set_integration_time(5);
    while (colorSortActive) {
        if (colorDetected(true)) {
            while (colorDetected(true)) {
                spitOut();
                pros::delay(10);
            } 
            pros::delay(250);
            stopIntake();
        } 
        pros::delay(10);
    }
}

void Intake::blueColorSort() {
    colorSensor.set_led_pwm(100);
    colorSensor.set_integration_time(5);
    while (colorSortActive) {
        if (colorDetected(false)) {
            while (colorDetected(false)) {
                spitOut();
                pros::delay(10);
            } 
            pros::delay(250);
            stopIntake();
        } 
        pros::delay(10);
    }
}
