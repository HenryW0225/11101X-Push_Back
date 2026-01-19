#include <math.h>
#include "pros/rtos.hpp"
#include "lemlib/util.hpp"
#include "lemlib/chassis/odom.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"

// tracking thread
pros::Task* trackingTask = nullptr;

// global variables
lemlib::OdomSensors odomSensors(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr); // the sensors to be used for odometry
lemlib::Drivetrain drive(nullptr, nullptr, 0, 0, 0, 0); // the drivetrain to be used for odometry
lemlib::Pose odomPose(0, 0, 0); // the pose of the robot
lemlib::Pose odomSpeed(0, 0, 0); // the speed of the robot
lemlib::Pose odomLocalSpeed(0, 0, 0); // the local speed of the robot

float prevVertical = 0;
float prevVertical1 = 0;
float prevVertical2 = 0;
float prevHorizontal = 0;
float prevHorizontal1 = 0;
float prevHorizontal2 = 0;
float prevImu = 0;

void lemlib::setSensors(lemlib::OdomSensors sensors, lemlib::Drivetrain drivetrain) {
    odomSensors = sensors;
    drive = drivetrain;
}

lemlib::Pose lemlib::getPose(bool radians) {
    if (radians) return odomPose;
    else return lemlib::Pose(odomPose.x, odomPose.y, radToDeg(odomPose.theta));
}

void lemlib::setPose(lemlib::Pose pose, bool radians) {
    if (radians) odomPose = pose;
    else odomPose = lemlib::Pose(pose.x, pose.y, degToRad(pose.theta));
}

lemlib::Pose lemlib::getSpeed(bool radians) {
    if (radians) return odomSpeed;
    else return lemlib::Pose(odomSpeed.x, odomSpeed.y, radToDeg(odomSpeed.theta));
}

lemlib::Pose lemlib::getLocalSpeed(bool radians) {
    if (radians) return odomLocalSpeed;
    else return lemlib::Pose(odomLocalSpeed.x, odomLocalSpeed.y, radToDeg(odomLocalSpeed.theta));
}

lemlib::Pose lemlib::estimatePose(float time, bool radians) {
    // get current position and speed
    Pose curPose = getPose(true);
    Pose localSpeed = getLocalSpeed(true);
    // calculate the change in local position
    Pose deltaLocalPose = localSpeed * time;

    // calculate the future pose
    float avgHeading = curPose.theta + deltaLocalPose.theta / 2;
    Pose futurePose = curPose;
    futurePose.x += deltaLocalPose.y * sin(avgHeading);
    futurePose.y += deltaLocalPose.y * cos(avgHeading);
    futurePose.x += deltaLocalPose.x * -cos(avgHeading);
    futurePose.y += deltaLocalPose.x * sin(avgHeading);
    if (!radians) futurePose.theta = radToDeg(futurePose.theta);

    return futurePose;
}

void lemlib::update() {
    // TODO: add particle filter
    // get the current sensor values
    float vertical1Raw = 0;
    float vertical2Raw = 0;
    float horizontal1Raw = 0;
    float horizontal2Raw = 0;
    float imuRaw = 0;
    if (odomSensors.vertical1 != nullptr) vertical1Raw = odomSensors.vertical1->getDistanceTraveled();
    if (odomSensors.vertical2 != nullptr) vertical2Raw = odomSensors.vertical2->getDistanceTraveled();
    if (odomSensors.horizontal1 != nullptr) horizontal1Raw = odomSensors.horizontal1->getDistanceTraveled();
    if (odomSensors.horizontal2 != nullptr) horizontal2Raw = odomSensors.horizontal2->getDistanceTraveled();
    if (odomSensors.imu != nullptr) imuRaw = degToRad(odomSensors.imu->get_rotation());

    // calculate the change in sensor values
    float deltaVertical1 = vertical1Raw - prevVertical1;
    float deltaVertical2 = vertical2Raw - prevVertical2;
    float deltaHorizontal1 = horizontal1Raw - prevHorizontal1;
    float deltaHorizontal2 = horizontal2Raw - prevHorizontal2;
    float deltaImu = imuRaw - prevImu;

    // update the previous sensor values
    prevVertical1 = vertical1Raw;
    prevVertical2 = vertical2Raw;
    prevHorizontal1 = horizontal1Raw;
    prevHorizontal2 = horizontal2Raw;
    prevImu = imuRaw;

    float heading = odomPose.theta;
    // calculate the heading using the horizontal tracking wheels

    // apply Gyro Scale
    //const float GYRO_SCALE = (360/356);
    //deltaImu *= GYRO_SCALE;

    if (odomSensors.imu != nullptr) {
        heading += deltaImu;
        //odomPose.theta = heading;
    }
    else if (!odomSensors.vertical1->getType() && !odomSensors.vertical2->getType())
        heading -= (deltaVertical1 - deltaVertical2) /
                   (odomSensors.vertical1->getOffset() - odomSensors.vertical2->getOffset());
    // else, if the inertial sensor exists, use it
    else if (odomSensors.horizontal1 != nullptr && odomSensors.horizontal2 != nullptr)
        heading -= (deltaHorizontal1 - deltaHorizontal2) /
                   (odomSensors.horizontal1->getOffset() - odomSensors.horizontal2->getOffset());
    // else, use the the substituted tracking wheels
    else
        heading -= (deltaVertical1 - deltaVertical2) /
                   (odomSensors.vertical1->getOffset() - odomSensors.vertical2->getOffset());
    float deltaHeading = heading - odomPose.theta;
    float avgHeading = odomPose.theta + deltaHeading / 2;

    // choose tracking wheels to use
    // Prioritize non-powered tracking wheels
    lemlib::TrackingWheel* verticalWheel = nullptr;
    lemlib::TrackingWheel* horizontalWheel = nullptr;
    if (!odomSensors.vertical1->getType()) verticalWheel = odomSensors.vertical1;
    else if (!odomSensors.vertical2->getType()) verticalWheel = odomSensors.vertical2;
    else verticalWheel = odomSensors.vertical1;
    if (odomSensors.horizontal1 != nullptr) horizontalWheel = odomSensors.horizontal1;
    else if (odomSensors.horizontal2 != nullptr) horizontalWheel = odomSensors.horizontal2;
    float rawVertical = 0;
    float rawHorizontal = 0;
    if (verticalWheel != nullptr) rawVertical = verticalWheel->getDistanceTraveled();
    if (horizontalWheel != nullptr) rawHorizontal = horizontalWheel->getDistanceTraveled();
    float horizontalOffset = 0;
    float verticalOffset = 0;
    if (verticalWheel != nullptr) verticalOffset = verticalWheel->getOffset();
    if (horizontalWheel != nullptr) horizontalOffset = horizontalWheel->getOffset();

    // calculate change in x and y
    float deltaX = 0;
    float deltaY = 0;
    if (verticalWheel != nullptr) deltaY = rawVertical - prevVertical;
    if (horizontalWheel != nullptr) deltaX = rawHorizontal - prevHorizontal;
    prevVertical = rawVertical;
    prevHorizontal = rawHorizontal;

    // calculate local x and y
    float localX = 0;
    float localY = 0;
    if (deltaHeading == 0) { // prevent divide by 0
        localX = deltaX;
        localY = deltaY;
    } else {
        localX = 2 * sin(deltaHeading / 2) * (deltaX / deltaHeading + horizontalOffset);
        localY = 2 * sin(deltaHeading / 2) * (deltaY / deltaHeading + verticalOffset);
    }

    // save previous pose
    lemlib::Pose prevPose = odomPose;

    // calculate global x and y
    odomPose.x += localY * sin(avgHeading);
    odomPose.y += localY * cos(avgHeading);
    odomPose.x += localX * -cos(avgHeading);
    odomPose.y += localX * sin(avgHeading);
    odomPose.theta = heading;

    // calculate speed
    odomSpeed.x = ema((odomPose.x - prevPose.x) / 0.01, odomSpeed.x, 0.95);
    odomSpeed.y = ema((odomPose.y - prevPose.y) / 0.01, odomSpeed.y, 0.95);
    odomSpeed.theta = ema((odomPose.theta - prevPose.theta) / 0.01, odomSpeed.theta, 0.95);

    // calculate local speed
    odomLocalSpeed.x = ema(localX / 0.01, odomLocalSpeed.x, 0.95);
    odomLocalSpeed.y = ema(localY / 0.01, odomLocalSpeed.y, 0.95);
    odomLocalSpeed.theta = ema(deltaHeading / 0.01, odomLocalSpeed.theta, 0.95);
}

void lemlib::init() {
    if (trackingTask == nullptr) {
        trackingTask = new pros::Task {[=] {
            while (true) {
                update();
                pros::delay(10);
            }
        }};
    }
}

double lemlib::verticalDistance() {
    if (odomSensors.vertical1 != nullptr) return odomSensors.vertical1->getDistanceTraveled();
    if (odomSensors.vertical2 != nullptr) return odomSensors.vertical2->getDistanceTraveled();
    return 0;
}

double lemlib::horizontalDistance() {
    if (odomSensors.horizontal1 != nullptr) return odomSensors.horizontal1->getDistanceTraveled();
    if (odomSensors.horizontal2 != nullptr) return odomSensors.horizontal2->getDistanceTraveled();
    return 0;
}
double lemlib::getRightDistance() {
    double sum = 0.0;  // initialize!
    for(int i = 0; i < 5; i++)
    {
        sum += odomSensors.distanceRight->get_distance();
        pros::delay(20);
    }
    return sum / 5.0 * 0.0393701;  // convert mm -> inches
}

double lemlib::getFrontDistance() {
    double sum = 0.0;  // initialize!
    for(int i = 0; i < 5; i++)
    {
        sum += odomSensors.distanceFront->get_distance();
        pros::delay(20);
    }
    return sum / 5.0 * 0.0393701;  // convert mm -> inches
}

double lemlib::getLeftDistance() {
    double sum = 0.0;  // initialize!
    for(int i = 0; i < 5; i++)
    {
        sum += odomSensors.distanceLeft->get_distance();
        pros::delay(20);
    }
    return sum / 5.0 * 0.0393701;  // convert mm -> inches
}

double lemlib::resetAngleWithSelfCorrectionInches() {
    // 1. Take initial readings (averaged, in inches)
    double L1 = getLeftDistance();   // LEFT distance sensor
    double R1 = getRightDistance();        // RIGHT distance sensor

    if (std::isnan(L1) || std::isnan(R1)) return 0.0;

    // 2. (Optional) take another reading for more accuracy
    // You can simulate a “+5° rotation” by moving the robot slightly in auton if needed.
    double L2 = getLeftDistance();
    double R2 = getRightDistance();

    if (std::isnan(L2) || std::isnan(R2)) return 0.0;

    // 3. Compute deltas
    double dL = L2 - L1;
    double dR = R2 - R1;

    double difference = dL - dR;

    // 4. Compute angle
    double angle_rad = atan(difference / BASE_WIDTH_IN);
    double angle_deg = angle_rad * (180.0 / M_PI);

    return angle_deg;  // returns the angle error in degrees
}
