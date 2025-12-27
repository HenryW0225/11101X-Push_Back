#include <cmath>
#include "lemlib/timer.hpp"
#include "main.h"
#include "math.h"
using namespace std;

void lemlib::Chassis::moveToPoint(float x, float y, int timeout, MoveToPointParams params, bool async) {
    params.earlyExitRange = fabs(params.earlyExitRange);
    this->requestMotionStart();
    // were all motions cancelled?
    if (!this->motionRunning) return;
    // if the function is async, run it in a new task
    if (async) {
        pros::Task task([&]() { moveToPoint(x, y, timeout, params, false); });
        this->endMotion();
        pros::delay(10); // delay to give the task time to start
        return;
    }

    // select PID settings based on pidSelector
    ControllerSettings selectedLateralSettings = (params.pidSelector == 0) ? lateralSettings : lateralSettingsExtra;
    ControllerSettings selectedHeadingSettings = (params.pidSelector == 0) ? headingSettings : headingSettingsExtra;

    // create local PIDs and exit conditions
    PID localLateralPID(selectedLateralSettings.kP, selectedLateralSettings.kI, selectedLateralSettings.kD, selectedLateralSettings.windupRange, true);
    PID localHeadingPID(selectedHeadingSettings.kP, selectedHeadingSettings.kI, selectedHeadingSettings.kD, selectedHeadingSettings.windupRange, true);
    ExitCondition localLateralLargeExit(selectedLateralSettings.largeError, selectedLateralSettings.largeErrorTimeout);
    ExitCondition localLateralSmallExit(selectedLateralSettings.smallError, selectedLateralSettings.smallErrorTimeout);

    // reset local PIDs and exit conditions
    localLateralPID.reset();
    localLateralLargeExit.reset();
    localLateralSmallExit.reset();
    localHeadingPID.reset();

    // initialize vars used between iterations
    Pose lastPose = getPose();
    distTraveled = 0;
    Timer timer(timeout);
    bool close = false;
    float prevLateralOut = 0; // previous lateral power
    float prevHeadingOut = 0; // previous heading power
    const int compState = pros::competition::get_status();
    std::optional<bool> prevSide = std::nullopt;

    // calculate target pose in standard form
    Pose target(x, y);
    target.theta = lastPose.angle(target);

    bool first = true;

    // main loop
    while (!timer.isDone() && ((!localLateralSmallExit.getExit() && !localLateralLargeExit.getExit()) || !close) &&
           this->motionRunning) {
        // update position
        const Pose pose = getPose(true, true);
        
        //get inital distance
        double initialDistance;
        if (first) {
            initialDistance = pose.distance(target);
            first = false;
        }

        // update distance traveled
        distTraveled += pose.distance(lastPose);
        lastPose = pose;

        // calculate distance to the target point
        const float distTarget = pose.distance(target);

        // check if the robot is close enough to the target to start settling
        if (distTarget < 7.5 && close == false) {
            close = true;
            params.maxSpeed = fmax(fabs(prevLateralOut), 60);
        }

        // motion chaining
        const bool side =
            (pose.y - target.y) * -sin(target.theta) <= (pose.x - target.x) * cos(target.theta) + params.earlyExitRange;
        if (prevSide == std::nullopt) prevSide = side;
        const bool sameSide = side == prevSide;
        // exit if close
        if (!sameSide && params.minSpeed != 0) break;
        prevSide = side;

        // calculate error
        const float adjustedRobotTheta = params.forwards ? pose.theta : pose.theta + M_PI;
        const float headingError = angleError(adjustedRobotTheta, target.theta);
        float lateralError = pose.distance(target) * cos(angleError(pose.theta, pose.angle(target)));

        // update exit conditions
        localLateralSmallExit.update(lateralError);
        localLateralLargeExit.update(lateralError);

        // get output from PIDs
        float lateralOut = localLateralPID.update(lateralError);
        float headingOut = localHeadingPID.update(radToDeg(headingError));
        float minHeadingPower = 4.0; // The lowest power that actually moves your bot
        if (std::fabs(radToDeg(headingError)) > 0.3) { // Only nudge if error is > 0.3 degrees
            if (std::fabs(headingOut) < minHeadingPower) {
                headingOut = (headingOut > 0) ? minHeadingPower : -minHeadingPower;
            }
        }
        //float headingScale = std::clamp(distTarget / 24.0f, 0.4f, 1.0f);
        //headingOut *= headingScale;



        // apply restrictions on heading speed
        headingOut = std::clamp(headingOut, -params.maxSpeed, params.maxSpeed);
        headingOut = slew(headingOut, prevHeadingOut, selectedHeadingSettings.slew);

        // apply restrictions on lateral speed
        lateralOut = std::clamp(lateralOut, -params.maxSpeed, params.maxSpeed);
        // constrain lateral output by max accel
        // but not for decelerating, since that would interfere with settling
        if (!close) lateralOut = slew(lateralOut, prevLateralOut, selectedLateralSettings.slew);

        // prevent moving in the wrong direction
        if (params.forwards && !close) lateralOut = std::fmax(lateralOut, 0);
        else if (!params.forwards && !close) lateralOut = std::fmin(lateralOut, 0);

        // constrain lateral output by the minimum speed
        if (params.forwards && lateralOut < fabs(params.minSpeed) && lateralOut > 0) lateralOut = fabs(params.minSpeed);
        if (!params.forwards && -lateralOut < fabs(params.minSpeed) && lateralOut < 0)
            lateralOut = -fabs(params.minSpeed);

        // update previous output
        prevHeadingOut = headingOut;
        prevLateralOut = lateralOut;

        infoSink()->debug("Heading Out: {}, Lateral Out: {}", headingOut, lateralOut);

        // ratio the speeds to respect the max speed
        float leftPower = lateralOut + headingOut;
        float rightPower = lateralOut - headingOut;
        const float ratio = std::max(std::fabs(leftPower), std::fabs(rightPower)) / params.maxSpeed;
        if (ratio > 1) {
            leftPower /= ratio;
            rightPower /= ratio;
        }

        // move the drivetrain
        drivetrain.leftMotors->move(leftPower);
        drivetrain.rightMotors->move(rightPower);

        // delay to save resources
        pros::delay(10);
    }

    // stop the drivetrain
    drivetrain.leftMotors->move(0);
    drivetrain.rightMotors->move(0);
    // set distTraveled to -1 to indicate that the function has finished
    distTraveled = -1;
    this->endMotion();

}