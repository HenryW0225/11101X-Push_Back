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
    topIntakeMotors.set_brake_mode(MOTOR_BRAKE_COAST);
    //if (red) { redColorSort(); }
    //else { blueColorSort(); }
}

void Intake::moveBottomIntake(double velocity){
    desiredBottomVelocity = velocity;
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

void Intake::scoreMiddleHigh() {
    moveBottomIntake(0);
    moveTopIntake(-100);
}

void Intake::intakeOut() {
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


void Intake::intakeJam(bool async) {
    if (async) {
        pros::Task task([this]() { intakeJam(false); });
        return;
    } 
    int timer = 0;
    while (!driverControl) {
        // Check if bottom intake is trying to run forward but is jammed (low actual velocity)
        if (bottomIntakeMotors.get_target_velocity() > 0 && bottomIntakeMotors.get_actual_velocity() < 25) {
            timer += 10;
        }
        else {
            timer = 0;
        }
        
        // If jam detected for 200ms, unjam by reversing bottom motors only
        if (timer > 200) {
            // Increment jam count if tracking is active
            if (jamTrackingActive) {
                jamCount++;
            }
            
            // Store the desired bottom velocity before unjamming
            double savedBottomVelocity = desiredBottomVelocity;
            
            // Reverse only the bottom motors for unjamming (don't update desiredBottomVelocity)
            bottomIntakeMotors.move_velocity(-600);
            pros::delay(150);
            
            // Restore the desired bottom velocity
            // Check if desiredBottomVelocity changed during the delay (autonomous code updated it)
            // If it did, use the new value; otherwise use the saved value
            double velocityToRestore = (desiredBottomVelocity != savedBottomVelocity) ? desiredBottomVelocity : savedBottomVelocity;
            bottomIntakeMotors.move_velocity(velocityToRestore);
            desiredBottomVelocity = velocityToRestore;
            
            // Reset timer
            timer = 0;
        }
        
        pros::delay(10);
    }
}

void Intake::startJamTracking() {
    jamTrackingActive = true;
    jamCount = 0; // Reset count when starting new tracking session
}

void Intake::stopJamTracking() {
    jamTrackingActive = false;
}

void Intake::resetJamCount() {
    jamCount = 0;
}

int Intake::getJamCount() {
    return jamCount;
}

int Intake::getJamDelay(int baseDelay) {
    // Add 200ms per jam to compensate for time lost during unjamming
    return baseDelay + (jamCount * 200);
}