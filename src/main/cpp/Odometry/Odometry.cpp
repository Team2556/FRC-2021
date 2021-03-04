// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Odometry/Odometry.h"

Odometry::Odometry(Drivebase * pDrivebase) 
{
    this->pDrivebase = pDrivebase;
    pNavX = new AHRS(frc::SPI::Port::kMXP);
    OdometryPeriodicThread = std::thread(&Odometry::odometryPeriodic, this);
    OdometryPeriodicThread.detach();
}

//Runs on a separate thread to update odometry things
void Odometry::odometryPeriodic()
{
    //Nonperiodic stuff goes here
    float wheelRadius = 3; //Inches
    float RPMToDistanceMultiplier = 2 * M_PI * wheelRadius * 0.0254 / 60; //This may need to be divided by 256, needs testing
    pDrivebase->leftFront.GetAlternateEncoder(rev::CANEncoder::AlternateEncoderType::kQuadrature, 8096).SetVelocityConversionFactor(RPMToDistanceMultiplier);
    pDrivebase->rightFront.GetAlternateEncoder(rev::CANEncoder::AlternateEncoderType::kQuadrature, 8096).SetVelocityConversionFactor(RPMToDistanceMultiplier);
    pDrivebase->leftBack.GetAlternateEncoder(rev::CANEncoder::AlternateEncoderType::kQuadrature, 8096).SetVelocityConversionFactor(RPMToDistanceMultiplier);
    pDrivebase->rightBack.GetAlternateEncoder(rev::CANEncoder::AlternateEncoderType::kQuadrature, 8096).SetVelocityConversionFactor(RPMToDistanceMultiplier);

    //not sketch I swear
    while(true)
    {
        //Periodic stuff goes here
        updatePose();
    }
}

//Returns the degree value of the robot's counterclockwise angle from vertical heading
float Odometry::getYaw()
{
    return pNavX->GetYaw();
}

//Returns the horizontal distance from the origin in meters
float Odometry::getX()
{
    return (float)currPose.load().Translation().X();
}

//Returns the vertical distance from the origin in meters
float Odometry::getY()
{
    return (float)currPose.load().Translation().Y();
}

//Returns robot's current position data
frc::Pose2d Odometry::getCurrentPose()
{
    return currPose.load();
}


//Private method used to update current pose
void Odometry::updatePose()
{
    frc::MecanumDriveWheelSpeeds    wheelSpeeds {
        (units::meters_per_second_t)(pDrivebase->leftFront.GetAlternateEncoder(rev::CANEncoder::AlternateEncoderType::kQuadrature, 8096).GetVelocity()),
        (units::meters_per_second_t)(pDrivebase->rightFront.GetAlternateEncoder(rev::CANEncoder::AlternateEncoderType::kQuadrature, 8096).GetVelocity()),
        (units::meters_per_second_t)(pDrivebase->leftBack.GetAlternateEncoder(rev::CANEncoder::AlternateEncoderType::kQuadrature, 8096).GetVelocity()),
        (units::meters_per_second_t)(pDrivebase->rightBack.GetAlternateEncoder(rev::CANEncoder::AlternateEncoderType::kQuadrature, 8096).GetVelocity())
    };
    frc::Rotation2d gyroAngle{units::degree_t(getYaw())}; //may need to use -yaw instead of positive, needs testing
    currPose.store(mecOdometry.Update(gyroAngle, wheelSpeeds));
}


//Normalizes an angle (in degrees) to be from 0 to 360
float Odometry::normalize360(float angle)
{
    float newAngle = angle + 3600;
    newAngle = fmod(newAngle, 360);
    return newAngle;
}

float Odometry::testGetEncoder()
{
    pDrivebase->rightFront.Set(0);
    float x = pDrivebase->rightFront.GetAlternateEncoder(rev::CANEncoder::AlternateEncoderType::kQuadrature, 8096).GetVelocity();
    return x;
}