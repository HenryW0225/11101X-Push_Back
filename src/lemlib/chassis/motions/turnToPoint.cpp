#include <cmath>
#include <optional>
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/logger/logger.hpp"
#include "lemlib/timer.hpp"
#include "lemlib/util.hpp"
#include "main.h"
#include "pros/misc.hpp"
using namespace std;

void lemlib::Chassis::turnToPoint(float x, float y, int timeout, TurnToPointParams params, bool async) {
    params.minSpeed = std::abs(params.minSpeed);
    this->requestMotionStart();
    // were all motions cancelled?
    if (!this->motionRunning) return;
    // if the function is async, run it in a new task
    if (async) {
        pros::Task task([&]() { turnToPoint(x, y, timeout, params, false); });
        this->endMotion();
        pros::delay(10); // delay to give the task time to start
        return;
    }

    // select PID settings based on pidSelector
    ControllerSettings selectedAngularSettings = (params.pidSelector == 0) ? angularSettings : angularSettingsExtra;

    // create local PIDs and exit conditions
    PID localAngularPID(selectedAngularSettings.kP, selectedAngularSettings.kI, selectedAngularSettings.kD, selectedAngularSettings.windupRange, true);
    ExitCondition localAngularLargeExit(selectedAngularSettings.largeError, selectedAngularSettings.largeErrorTimeout);
    ExitCondition localAngularSmallExit(selectedAngularSettings.smallError, selectedAngularSettings.smallErrorTimeout);

    // reset local PIDs and exit conditions
    localAngularPID.reset();
    localAngularLargeExit.reset();
    localAngularSmallExit.reset();

    float targetTheta;
    float deltaX, deltaY, deltaTheta;
    float motorPower;
    float prevMotorPower = 0;
    float startTheta = getPose().theta;
    bool settling = false;
    optional<float> prevRawDeltaTheta = nullopt;
    optional<float> prevDeltaTheta = nullopt;
    std::uint8_t compState = pros::competition::get_status();
    distTraveled = 0;
    Timer timer(timeout);

    // main loop
    while (!timer.isDone() && !localAngularLargeExit.getExit() && !localAngularSmallExit.getExit() && this->motionRunning) {
        // update variables
        Pose pose = getPose();
        pose.theta = (params.forwards) ? fmod(pose.theta, 360) : fmod(pose.theta - 180, 360);

        // update completion vars
        distTraveled = fabs(angleError(pose.theta, startTheta, false));

        deltaX = x - pose.x;
        deltaY = y - pose.y;
        targetTheta = fmod(radToDeg(M_PI_2 - atan2(deltaY, deltaX)), 360);

        // check if settling
        const float rawDeltaTheta = angleError(targetTheta, pose.theta, false);
        if (prevRawDeltaTheta == nullopt) prevRawDeltaTheta = rawDeltaTheta;
        if (sgn(rawDeltaTheta) != sgn(prevRawDeltaTheta)) settling = true;
        prevRawDeltaTheta = rawDeltaTheta;

        // calculate deltaTheta
        if (settling) deltaTheta = angleError(targetTheta, pose.theta, false);
        else deltaTheta = angleError(targetTheta, pose.theta, false, params.direction);
        if (prevDeltaTheta == nullopt) prevDeltaTheta = deltaTheta;

        // motion chaining
        if (params.minSpeed != 0 && fabs(deltaTheta) < params.earlyExitRange) break;
        if (params.minSpeed != 0 && sgn(deltaTheta) != sgn(prevDeltaTheta)) break;

        // calculate the speed
        motorPower = localAngularPID.update(deltaTheta);
        localAngularLargeExit.update(deltaTheta);
        localAngularSmallExit.update(deltaTheta);

        // cap the speed
        if (motorPower > params.maxSpeed) motorPower = params.maxSpeed;
        else if (motorPower < -params.maxSpeed) motorPower = -params.maxSpeed;
        if (fabs(deltaTheta) > 20) motorPower = slew(motorPower, prevMotorPower, selectedAngularSettings.slew);
        // enforce minimum speed only if we've reached it before
        if (fabs(prevMotorPower) >= params.minSpeed) {
            if (motorPower < 0 && motorPower > -params.minSpeed) motorPower = -params.minSpeed;
            else if (motorPower > 0 && motorPower < params.minSpeed) motorPower = params.minSpeed;
        }
        prevMotorPower = motorPower;

        infoSink()->debug("Turn Motor Power: {} ", motorPower);

        // move the drivetrain
        drivetrain.leftMotors->move(motorPower);
        drivetrain.rightMotors->move(-motorPower);

        pros::delay(10);
    }

    // stop the drivetrain
    drivetrain.leftMotors->move(0);
    drivetrain.rightMotors->move(0);
    // set distTraveled to -1 to indicate that the function has finished
    distTraveled = -1;
    this->endMotion();
}