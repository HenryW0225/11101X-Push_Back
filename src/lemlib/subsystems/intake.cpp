#include "main.h"

Intake::Intake(pros::Motor bottomIntakeMotors, pros::Motor topIntakeMotors, pros::Optical colorSensor, pros::adi::DigitalOut colorSortPneumatic)
    : bottomIntakeMotors(bottomIntakeMotors),
      topIntakeMotors(topIntakeMotors),
      colorSensor(colorSensor),
      colorSortPneumatic(colorSortPneumatic) {}
      

void Intake::move_bottom_intake(double velocity){
    bottomIntakeMotors.move_velocity(velocity);
}

void Intake::move_top_intake(double velocity){
    topIntakeMotors.move_velocity(velocity);
}

void Intake::intake_block() {
    move_bottom_intake(600);
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

void Intake::color_sort(bool red) {

}
