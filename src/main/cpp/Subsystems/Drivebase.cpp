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

    source = new AimPIDSource(&pRobot->limelight);
    AimPID = new PIDWrapper(0, 0, 0, 0, PIDOutput, source);
}

//Drives the robot using a speed, direction (rads clockwise from forward), and rotation. 
void Drivebase::PolarDrive(double speed, double direction, double rotate, double gyro)
{
    double speedConverted = MAX_SPEED * speed;
    this->DriveMPS(speedConverted, direction, rotate, gyro);
}

/*
Aim the drivebase at the target using the limelight.
This function will interfere with any other attempts to drive, if you want to get the speed from the PID loop that would be used here, use GetAimSpeed() instead.
*/
bool Drivebase::Aim()
{
    double speed;
    if (pRobot->limelight.HasTarget())
    {
        speed = *PIDOutput;
    }
    else
    {
        speed = 0;
    }
    
    Drive(0, 0, speed, 0);
    DrivebaseDebug.PutNumber("Aim Speed", speed);
    return pRobot->limelight.xOffset() < MAX_AIM_ERROR;
}

bool Drivebase::IsAimed()
{
    return pRobot->limelight.xOffset() < MAX_AIM_ERROR;
}

/*
Use this function to get the aim speed if you want to aim and call drive yourself 
*/
double Drivebase::GetAimSpeed()
{
    double speed;
    if (pRobot->limelight.HasTarget())
    {
        speed = *PIDOutput;
    }
    else
    {
        speed = 0;
    }
    DrivebaseDebug.PutNumber("Aim Speed", speed);
    return speed;
}

double limitNumber(double initial, double max)
{
    if(fabs(initial) < max)
    {
        return initial;
    }
    else if(initial > max)
    {
        return max;
    }
    else //if(initial < -1.0 * max)
    {
        return -1.0 * max;
    }
    
}

void Drivebase::Drive(double fForward, double fStrafe, double rotate, double gyro)
{
    rotate *= MAX_ROTATE;
    rotate = limitNumber(rotate, MAX_ROTATE);
    
    DrivebaseDebug.PutNumber("Forward", fForward);
    DrivebaseDebug.PutNumber("Strafe", fStrafe);
    DrivebaseDebug.PutNumber("Rotate", rotate);
    DrivebaseDebug.PutNumber("Gyro", gyro);

    double totalSpeed = sqrt(fStrafe * fStrafe + fForward * fForward);
    double direction = atan2(fForward, fStrafe);

    this->DriveMPS(totalSpeed, direction, rotate, gyro);
}

void Drivebase::GyroDrive(bool fieldOriented)
{
    bool bAllowRotate = false;
    static int stopHoldCounter = 0;

    // Get joystick inputs
    double fForward = pRobot->DriverCMD->fMoveForward();
    double fStrafe = pRobot->DriverCMD->fMoveSideways();
    double fRotate = pRobot->DriverCMD->fRotate();


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
    DrivebaseDebug.PutNumber("Yaw Speed", pRobot->Nav.getYawSpeed());
    if ((bAllowRotate == false) && (bRotatePrevious== true) && (fabs(pRobot->Nav.getYawSpeed()) < 4))
    {
        stopHoldCounter++;
    }
    else if((bAllowRotate == false) && (bRotatePrevious == true) && (stopHoldCounter >= 15))
    {
        stopHoldCounter = 0;
        bRotatePrevious = false;
    }
    // if((bAllowRotate == false) && (bRotatePrevious == true) && (stopHoldCounter < 15))
    // {
    //     stopHoldCounter++;
    // }
    // else if((bAllowRotate == false) && (bRotatePrevious == true) && (stopHoldCounter >= 15))
    // {
    //     stopHoldCounter = 0;
    //     bRotatePrevious = false;
    // }


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
    double gyro;
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

double Drivebase::GetRotate()
{
    double error = pRobot->Nav.GetYawError();
    return error * .015;
}

void Drivebase::testDrive(bool go, double speed)
{
    this->Drive(speed, -speed, 0, 0);
}

/*
 Drive with direction off x axis (degrees), speed (mps), rotate (deg/s), and gyro (deg).
 All other drive functions feed into this one.
 */
void Drivebase::DriveMPS(double direction, double speed, double rotate, double gyro)
{
    direction += gyro;
    double rotateScaled = rotate * ROBOT_RADIUS * PI/180;
    //Motor speeds are dependent on direction and speed. These are the functions that return correct values.
    double rightFrontSpeed = speed * sin((45 - direction) * PI/180) + rotateScaled;
    double leftFrontSpeed = speed * sin((135 - direction) * PI/180) + rotateScaled;
    double leftBackSpeed = speed * sin((225 - direction) * PI/180) + rotateScaled;
    double rightBackSpeed = speed * sin((315 - direction) * PI/180) + rotateScaled;

    //Set motor speeds to calculated values
    DriveLowLevel(leftFrontSpeed, rightFrontSpeed, leftBackSpeed, rightBackSpeed);
}


//Parameters are pointer to the motor you want to set and the speed in m/s you want it to end up at
void Drivebase::SetMotorSpeed(rev::CANSparkMax * motor, double speed)
{
    double SetPoint = speed; //This is the speed we want to be at.
    double scale = 0.02;     //This needs to change lol
    //Error is the difference between the speed we want to be at and our current speed from that motor.
    double error = SetPoint - motor->GetAlternateEncoder(rev::CANEncoder::AlternateEncoderType::kQuadrature, 8192).GetVelocity();
    double motorSpeedNow = motor->Get(); //Find current speed on the motor
    motor->Set(motorSpeedNow + error * scale); //Adjust current speed by the error
}

//Sets drive motor speeds (mps). Only function that should interact with drivebase motors.
void Drivebase::DriveLowLevel(double FrontLeftMPS, double FrontRightMPS, double RearLeftMPS, double RearRightMPS)
{
    DrivebaseDebug.PutNumber("RF Encoder Number", GetEncoderRF().GetVelocity());
    DrivebaseDebug.PutNumber("LF Encoder Number", GetEncoderLF().GetVelocity());
    DrivebaseDebug.PutNumber("RR Encoder Number", GetEncoderRR().GetVelocity());
    DrivebaseDebug.PutNumber("LR Encoder Number", GetEncoderLR().GetVelocity());
    SetMotorSpeed(&rightFront, FrontRightMPS);
    SetMotorSpeed(&leftFront, FrontLeftMPS);
    SetMotorSpeed(&rightBack, RearRightMPS);
    SetMotorSpeed(&leftBack, RearLeftMPS);
}