// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Odometry.h"

Odometry::Odometry() 
{
    pNavX = new AHRS(frc::SPI::Port::kMXP);
    OdometryPeriodicThread = std::thread(&Odometry::odometryPeriodic, this);
}

void Odometry::odometryPeriodic()
{
    updatePose();
}

//Returns the degree value of the robot's counterclockwise angle from vertical heading
float Odometry::getYaw()
{
    return pNavX->GetYaw();
}

//Returns the horizontal distance from the origin in meters
float Odometry::getX()
{
    return (float)currPose.Translation().X();
}

//Returns the vertical distance from the origin in meters
float Odometry::getY()
{
    return (float)currPose.Translation().Y();
}

frc::Pose2d Odometry::getCurrentPose()
{
    return currPose;
}


//Private method used to update current pose
void Odometry::updatePose()
{
    float wheelRadius = 3; //Inches
    float countToDistanceMultiplier = 2 * M_PI * wheelRadius * 0.0254; //This may need to be divided by 256, needs testing
    frontRightEncoder.SetDistancePerPulse(countToDistanceMultiplier);
    frontLeftEncoder.SetDistancePerPulse(countToDistanceMultiplier);
    backRightEncoder.SetDistancePerPulse(countToDistanceMultiplier);
    backLeftEncoder.SetDistancePerPulse(countToDistanceMultiplier);
    frc::MecanumDriveWheelSpeeds    wheelSpeeds {
        (units::meters_per_second_t)(frontLeftEncoder.GetRate()),
        (units::meters_per_second_t)(frontRightEncoder.GetRate()),
        (units::meters_per_second_t)(backLeftEncoder.GetRate()),
        (units::meters_per_second_t)(backRightEncoder.GetRate())
    };
    frc::Rotation2d gyroAngle{units::degree_t(getYaw())}; //may need to use -yaw instead of positive, needs testing
    currPose = mecOdometry.Update(gyroAngle, wheelSpeeds);
}
