// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Subsystems/Drivebase.h"

Drivebase::Drivebase(Robot * pRobot)
{
    this->pRobot = pRobot;
    rightFront.SetInverted(true);
    leftFront.SetInverted(true);
    rightBack.SetInverted(true);
    leftBack.SetInverted(true);
}

//Drives the robot using a speed, direction (rads clockwise from forward), and rotation. 
void Drivebase::PolarDrive(float speed, float direction, float rotate, float gyro)
{
    float xSpeed = sin(direction) * speed;
    float ySpeed = cos(direction) * speed;

    this->Drive(ySpeed, xSpeed, rotate, gyro);
}

void Drivebase::Drive(float fForward, float fStrafe, float rotate, float gyro)
{
    rotate *= .7;
    DrivebaseDebug.PutNumber("Forward", fForward);
    DrivebaseDebug.PutNumber("Strafe", fStrafe);
    DrivebaseDebug.PutNumber("Rotate", rotate);
    DrivebaseDebug.PutNumber("Gyro", gyro);
    RobotDrive.DriveCartesian(fStrafe, fForward, rotate, gyro);
}

void Drivebase::GyroDrive(bool fieldOriented)
{
    bool			bAllowRotate = false;
    static int stopHoldCounter = 0;

    // Get joystick inputs
    float fForward = pRobot->DriverCMD->fMoveForward();
    float fStrafe = pRobot->DriverCMD->fMoveSideways();
    float fRotate = pRobot->DriverCMD->fRotate();


    bAllowRotate = pRobot->DriverCMD->bManualRotate();

    if((pRobot->DriverCMD->POV() > -1) && !bPresetTurning)
    {
    	pRobot->Nav.setCommandYaw(pRobot->DriverCMD->POV());
    	bPresetTurning = true;
        bAllowRotate = false;
    }
    if(fabs(pRobot->Nav.GetYawError())<10)
    {
    	bPresetTurning = false;
    }
    else if(bPresetTurning == true)
    {
        bAllowRotate = false;
    }

    if(bAllowRotate == true)
    {
        bRotatePrevious = true;
    }

    if((bAllowRotate == false) && (bRotatePrevious == true) && (stopHoldCounter < 15))
    {
        stopHoldCounter++;
    }
    else if((bAllowRotate == false) && (bRotatePrevious == true) && (stopHoldCounter >= 15))
    {
        stopHoldCounter = 0;
        bRotatePrevious = false;
    }


    if (bRotatePrevious)
	{
        fRotate = pRobot->DriverCMD->fRotate();

        if (fRotate >  0.0) fRotate -= 0.05;
        if (fRotate <  0.0) fRotate += 0.05;
        if (fRotate >  0.8) fRotate  =  0.8;
        if (fRotate < -0.8) fRotate  = -0.8;

        pRobot->Nav.setCommandYaw(pRobot->Nav.getYaw());
        frc::SmartDashboard::PutBoolean("Gryo Enabled", false);
	}
    else
    {
        // Calculate a rotation rate from robot angle error
    	fRotate = this->GetRotate();
        frc::SmartDashboard::PutBoolean("Gryo Enabled", true);
    }



    if(pRobot->DriverCMD->bResetGyro())
    {
        pRobot->Nav.ResetYaw();
    }
    float gyro;
    if(fieldOriented)
    {
        gyro = -pRobot->Nav.getYaw();
    }
    else
    {
        gyro = 0.0;
    }
    
    
    this->Drive(fForward, fStrafe, fRotate, gyro);
}

void Drivebase::FieldOrientedDrive()
{
    this->GyroDrive(true);
}

// Encoder Functions

// Get the encoder for the front left motor
rev::CANEncoder Drivebase::GetEncoderLF()
{
    return leftFront.GetAlternateEncoder(rev::CANEncoder::AlternateEncoderType::kQuadrature, 8192);
}

// Get the encoder for the front right motor
rev::CANEncoder Drivebase::GetEncoderRF()
{
    return rightFront.GetAlternateEncoder(rev::CANEncoder::AlternateEncoderType::kQuadrature, 8192);
}

// Get the encoder for the back left motor
rev::CANEncoder Drivebase::GetEncoderLR()
{
    return leftBack.GetAlternateEncoder(rev::CANEncoder::AlternateEncoderType::kQuadrature, 8192);
}

// Get the encoder for the back right motor
rev::CANEncoder Drivebase::GetEncoderRR()
{
    return rightBack.GetAlternateEncoder(rev::CANEncoder::AlternateEncoderType::kQuadrature, 8192);
}

float Drivebase::GetRotate()
{
    float error = pRobot->Nav.GetYawError();
    return error * .015;
}