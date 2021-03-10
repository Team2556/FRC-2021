// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Odometry/Odometry.h"

Odometry::Odometry(Robot * pRobot, Drivebase * pDrivebase) 
{
    this->pDrivebase = pDrivebase;
    this->pRobot = pRobot;

    this->init();
    currPose.store(newPose);
    //OdometryDebug.PutNumber("Y length", negY.to<float>());
    // OdometryPeriodicThread = std::thread(&Odometry::odometryPeriodic, this);
    // OdometryPeriodicThread.detach();
    printWheelSpeeds(mecKinematics.ToWheelSpeeds(frc::ChassisSpeeds::FromFieldRelativeSpeeds(1_mps, 0_mps, 0_rad_per_s, startingPosition.Rotation()), startingPosition.Translation()));
}

void Odometry::init()
{
    float wheelRadius = 3; //Inches
    float countToDistanceMultiplier = 2 * 3.14159265 * wheelRadius * 0.0254 * (1.0/60); //This may need to be divided by 256, needs testing
    // frontRightEncoder.SetDistancePerPulse(countToDistanceMultiplier);
    // frontLeftEncoder.SetDistancePerPulse(countToDistanceMultiplier);
    // backRightEncoder.SetDistancePerPulse(countToDistanceMultiplier);
    // backLeftEncoder.SetDistancePerPulse(countToDistanceMultiplier);
    pDrivebase->GetEncoderLF().SetVelocityConversionFactor(countToDistanceMultiplier);
    pDrivebase->GetEncoderRF().SetVelocityConversionFactor(countToDistanceMultiplier);
    pDrivebase->GetEncoderLR().SetVelocityConversionFactor(countToDistanceMultiplier);
    pDrivebase->GetEncoderRR().SetVelocityConversionFactor(countToDistanceMultiplier);
}
//Runs on a separate thread to update odometry things
void Odometry::odometryPeriodic()
{
    

    //not sketch I swear
    while(true)
    {
        updatePose();
        OdometryDebug.PutNumber("X", this->getX());
        OdometryDebug.PutNumber("Y", this->getY());
        OdometryDebug.PutNumber("Yaw", this->getYaw());
    }
}



//Returns the horizontal distance from the origin in meters
float Odometry::getX()
{
    return currPose.load().Translation().X().to<float>();
}

//Returns the vertical distance from the origin in meters
float Odometry::getY()
{
    
    return currPose.load().Y().to<float>();
}

//Returns robot's current position data
frc::Pose2d Odometry::getCurrentPose()
{
    return currPose.load();
}

float Odometry::getYaw()
{
    return currPose.load().Rotation().Radians().to<float>() * (180/ M_PI);
    //return pRobot->Nav.getYaw();
}



//Private method used to update current pose
void Odometry::updatePose()
{
    // frc::MecanumDriveWheelSpeeds    wheelSpeeds {
    //     (units::meters_per_second_t)(frontLeftEncoder.GetRate()),
    //     (units::meters_per_second_t)(frontRightEncoder.GetRate()),
    //     (units::meters_per_second_t)(backLeftEncoder.GetRate()),
    //     (units::meters_per_second_t)(backRightEncoder.GetRate())
    // };
    frc::MecanumDriveWheelSpeeds    wheelSpeeds {
        (units::meters_per_second_t)(pDrivebase->GetEncoderLF().GetVelocity()),
        (units::meters_per_second_t)(pDrivebase->GetEncoderRF().GetVelocity()),
        (units::meters_per_second_t)(pDrivebase->GetEncoderLR().GetVelocity()),
        (units::meters_per_second_t)(pDrivebase->GetEncoderRR().GetVelocity())
    };
    OdometryDebug.PutNumber("front left", wheelSpeeds.frontLeft.to<float>());
    OdometryDebug.PutNumber("front right", wheelSpeeds.frontRight.to<float>());
    OdometryDebug.PutNumber("rear right", wheelSpeeds.rearRight.to<float>());
    OdometryDebug.PutNumber("rear left", wheelSpeeds.rearLeft.to<float>());
    frc::Rotation2d gyroAngle{units::degree_t(pRobot->Nav.getYaw())}; //may need to use -yaw instead of positive, needs testing
    frc::Pose2d fakePose = mecOdometry.Update(gyroAngle, wheelSpeeds);

    currPose.store(mecOdometry.Update(gyroAngle, wheelSpeeds));

    OdometryDebug.PutNumber("X", currPose.load().X().to<float>());
    OdometryDebug.PutNumber("Y", currPose.load().Y().to<float>());
    OdometryDebug.PutNumber("Yaw", currPose.load().Rotation().Radians().to<float>());
}

void Odometry::SetStartX(float X)
{

}

void Odometry::SetStartY(float Y)
{

}

void Odometry::SetStartYaw(float Yaw)
{

}

float Odometry::GetStartX()
{
    return 0;
}

float Odometry::GetStartY()
{
    return 0;
}

float Odometry::GetStartYaw()
{
    return 0;
}

void Odometry::printWheelSpeeds(frc::MecanumDriveWheelSpeeds wheelSpeeds)
{
    OdometryDebug.PutNumber("test front left", wheelSpeeds.frontLeft.to<float>());
    OdometryDebug.PutNumber("test front right", wheelSpeeds.frontRight.to<float>());
    OdometryDebug.PutNumber("test rear right", wheelSpeeds.rearRight.to<float>());
    OdometryDebug.PutNumber("test rear left", wheelSpeeds.rearLeft.to<float>());
}