// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Subsystems/Drivebase.h"

Drivebase::Drivebase(Robot * pRobot)
{
    this->pRobot = pRobot;
}

float Drivebase::MaxRotate(float rotate)
{
    if (rotate < -MAX_ROTATE)
    {
        rotate = -MAX_ROTATE;
    }
    if (rotate > MAX_ROTATE)
    {
        rotate = MAX_ROTATE;
    }
    return rotate;
}

float Drivebase::MaxStrafe(float xSpeed)
{
    if (xSpeed < -MAX_STRAFE)
    {
        xSpeed = -MAX_STRAFE;
    }
    if (xSpeed > MAX_STRAFE)
    {
        xSpeed = MAX_STRAFE;
    }
    return xSpeed;
}

float Drivebase::MaxForward(float ySpeed)
{
    if (ySpeed < -MAX_FORWARD)
    {
        ySpeed = -MAX_FORWARD;
    }
    if (ySpeed > MAX_FORWARD)
    {
        ySpeed = MAX_FORWARD;
    }
    return ySpeed;
}

void Drivebase::PolarDrive(float speed, float direction, float rotate, float gyro)
{
    return;
}

void Drivebase::GyroDrive(float commandXSpeed, float commandYSpeed, float rotate, bool allowRotate, float gyroError)
{
    frc::SmartDashboard::PutNumber("Error", gyroError); 
    float correction; //Code that finds the error and how much the robot needs to turn to fix it
    if (allowRotate)
    {
    MecanumDrive.DriveCartesian(commandXSpeed, commandYSpeed, rotate);
    }
    else if (allowRotate == false)
    {
        if (gyroError > -10)
        {
            correction = 0.1;
        }
        else if (gyroError < 10)
        {
            correction = -0.1;
        }
        else
        {
            correction = 0;
        }
    MecanumDrive.DriveCartesian(commandXSpeed, commandYSpeed, correction);
    }
}


void Drivebase::FieldOrientedDrive(float xSpeed, float ySpeed, float rotate, float gyro)
{
    MecanumDrive.DriveCartesian(xSpeed, ySpeed, rotate, gyro);
}

void Drivebase::InvertMotors()
{
  MecanumDrive.SetRightSideInverted(true);
 
}