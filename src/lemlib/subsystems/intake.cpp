#include "lemlib/subsystems/intake.hpp"
#include "pros/motors.h"
#include "main.h"

Intake::Intake(pros::Motor bottomIntakeMotors, pros::Motor topIntakeMotors)
    : bottomIntakeMotors(bottomIntakeMotors),
      //middleIntakeMotors(middleIntakeMotors),
      topIntakeMotors(topIntakeMotors) {}
      

void Intake::move_bottom_intake(double velocity){
    bottomIntakeMotors.move_velocity(velocity);
}

/*void Intake::move_middle_intake(double velocity){
    middleIntakeMotors.move_velocity(velocity);
}*/

void Intake::move_top_intake(double velocity){
    topIntakeMotors.move_velocity(velocity);
}

void Intake::intake_block() {
    move_bottom_intake(600);
    //move_middle_intake(600);
    move_top_intake(-600);
}

void Intake::outtake_block() {
    move_bottom_intake(-600);
    //move_middle_intake(-600);
    move_top_intake(-600);
}

void Intake::score_middle_goal() {
    move_bottom_intake(600);
    //move_middle_intake(-200);
    move_top_intake(-600);
}

void Intake::score_high_goal() {
    move_bottom_intake(600);
    //move_middle_intake(-600);
    move_top_intake(600);
}

void Intake::stop_intake() {
    move_bottom_intake(0);
    //move_middle_intake(0);
    move_top_intake(0);
}

