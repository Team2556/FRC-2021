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
    //OdometryDebug.PutNumber("Y length", negY.to<double>());
    // OdometryPeriodicThread = std::thread(&Odometry::odometryPeriodic, this);
    // OdometryPeriodicThread.detach();
    printWheelSpeeds(mecKinematics.ToWheelSpeeds(frc::ChassisSpeeds::FromFieldRelativeSpeeds(1_mps, 0_mps, 0_rad_per_s, startingPosition.Rotation()), startingPosition.Translation()));
}

void Odometry::init()
{
    double wheelRadius = 3; //Inches
    double countToDistanceMultiplier = 2 * 3.14159265 * wheelRadius * 0.0254 * (1.0/60); //This may need to be divided by 256, needs testing
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
        //Periodic stuff goes here
        updatePose();
        if(canReset())
        {
            //Y value is either 40.3181 inches or 55.3181 inches. The X value is approximately 133.049 inches.
            double yOption1 = 40.3181 * 0.0254;
            double yOption2 = 55.3181 * 0.0254;
            double currentY = getY();
            double realY;
            /* Whichever side the robot thinks it should be closer to is probably the correct one. If this doesn't work
            we'll need to store the last y value and figure out which direction we're going */
            if(abs(currentY - yOption1) < abs(currentY - yOption2))
            {
                realY = yOption1;
            }
            else
            {
                realY = yOption2;
            }
            double x = 133.049 * 0.0254;
            mecOdometry.ResetPosition(frc::Pose2d{(units::meter_t) x, (units::meter_t) realY, 0_deg}, units::degree_t(getYaw())); //Probably shouldn't be 0 degrees
        }
        OdometryDebug.PutNumber("X", this->getX());
        OdometryDebug.PutNumber("Y", this->getY());
        OdometryDebug.PutNumber("Yaw", this->getYaw());
    }
}



//Returns the horizontal distance from the origin in meters
double Odometry::getX()
{
    return currPose.load().Translation().X().to<double>();
}

//Returns the vertical distance from the origin in meters
double Odometry::getY()
{
    
    return currPose.load().Y().to<double>();
}

//Returns robot's current position data
frc::Pose2d Odometry::getCurrentPose()
{
    return currPose.load();
}

double Odometry::getYaw()
{
    return currPose.load().Rotation().Radians().to<double>() * (180/ 3.14159265359);
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
    OdometryDebug.PutNumber("front left", wheelSpeeds.frontLeft.to<double>());
    OdometryDebug.PutNumber("front right", wheelSpeeds.frontRight.to<double>());
    OdometryDebug.PutNumber("rear right", wheelSpeeds.rearRight.to<double>());
    OdometryDebug.PutNumber("rear left", wheelSpeeds.rearLeft.to<double>());
    frc::Rotation2d gyroAngle{units::degree_t(pRobot->Nav.getYaw())}; //may need to use -yaw instead of positive, needs testing

    currPose.store(mecOdometry.Update(gyroAngle, wheelSpeeds));
    OdometryDebug.PutNumber("Field X Position", getX());
    OdometryDebug.PutNumber("Field Y Position", getY());
}


//Normalizes an angle (in degrees) to be from 0 to 360
double Odometry::normalize360(double angle)
{
    double newAngle = angle + 3600;
    newAngle = fmod(newAngle, 360);
    return newAngle;
}

bool Odometry::canReset()
{
    //distance from floor to bottom of trench is 28 inches.
    double trenchHeight = 28;
    double ultraToTrench = trenchHeight - ULTRASONICHEIGHT;
    double ultraSeen = trenchUltrasonic.GetRangeInches();
    if(ultraSeen < ultraToTrench + 2 && ultraSeen > ultraToTrench - 2)
    {
        //We're inside the trench pog
        return true;
    }
    else
    {
        return false;
    }
}


void Odometry::SetStartX(double X)
{

}

void Odometry::SetStartY(double Y)
{

}

void Odometry::SetStartYaw(double Yaw)
{

}

double Odometry::GetStartX()
{
    return 0;
}

double Odometry::GetStartY()
{
    return 0;
}

double Odometry::GetStartYaw()
{
    return 0;
}

void Odometry::printWheelSpeeds(frc::MecanumDriveWheelSpeeds wheelSpeeds)
{
    OdometryDebug.PutNumber("test front left", wheelSpeeds.frontLeft.to<double>());
    OdometryDebug.PutNumber("test front right", wheelSpeeds.frontRight.to<double>());
    OdometryDebug.PutNumber("test rear right", wheelSpeeds.rearRight.to<double>());
    OdometryDebug.PutNumber("test rear left", wheelSpeeds.rearLeft.to<double>());
}