#include "main.h"
#include <map>
using namespace std;

Intake::Intake(pros::Motor bottomIntakeMotors, pros::Motor topIntakeMotors, pros::Optical colorSensor, pros::adi::DigitalOut intakePneumatic)
    : bottomIntakeMotors(bottomIntakeMotors),
      topIntakeMotors(topIntakeMotors),
      colorSensor(colorSensor),
      intakePneumatic(intakePneumatic) {}
      

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

/*void Intake::color_sort(bool red) {
    map<bool, double traits[3][2]> colorTraits;
    colorTraits[true] = [[200, 240], [0.5, 0.9], [250, 255]];
    colorTraits[false] = [[350, 10], [0.6, 1], [250, 255]];
    colorSensor.set_led_pwm(100);
    colorSensor.set_integration_time(5);
    while (true) {
        if ((colorSensor.get_hue() >= colorTraits[color][0][0] && colorSensor.get_hue() <= colorTraits[color][0][1]) 
        && (colorSensor.get_saturation() >= colorTraits[color][1][0] && colorSensor.get_saturation() <= colorTraits[color][1][1]) 
        && (colorSensor.get_proximity() >= colorTraits[color][2][0])) {
            // do the color sensor thing 
        }
    }

}





int Intake::color_sort_task() {
    intake.color_sort();
    return 1;
}*/
  
