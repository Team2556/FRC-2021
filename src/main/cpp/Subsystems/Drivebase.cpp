// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#define MAX_ROTATE .7
#include "Subsystems/Drivebase.h"
#include "Odometry/Limelight.h"

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
    float speedConverted = MAX_SPEED * speed;
    this->DriveMPS(speedConverted, direction, rotate, gyro);
}

bool Drivebase::Aim(float error)
{
    // float error = pRobot->limelight.xOffset();
    // float integral = 0; 

    // if ( error != 0){
                
    //     float pGain = 1; 
    //     float dGain = 1; 
    //     float iGain = 1; 
    
    //     float deriv //= error - previousError; //how do I get the previous error?
    //     integral = integral + error;
       
    //    this->RotateDrivebase(((error * pGain) + (integral * iGain) - (deriv * dGain))); 
    //    return false;

    // }
     
    // else {
    //     return true; 
    // } 
    return false;
}

float limitNumber(float initial, float max)
{
    if(fabs(initial) < max)
    {
        return initial;
    }
    else if(initial > max)
    {
        return max;
    }
    else if(initial < -1.0 * max)
    {
        return -1.0 * max;
    }
}

void Drivebase::Drive(float fForward, float fStrafe, float rotate, float gyro)
{
    rotate *= MAX_ROTATE;
    rotate = limitNumber(rotate, MAX_ROTATE);
    
    DrivebaseDebug.PutNumber("Forward", fForward);
    DrivebaseDebug.PutNumber("Strafe", fStrafe);
    DrivebaseDebug.PutNumber("Rotate", rotate);
    DrivebaseDebug.PutNumber("Gyro", gyro);

    float totalSpeed = sqrt(fStrafe * fStrafe + fForward * fForward);
    float direction = atan2(fForward, fStrafe);

    this->DriveMPS(totalSpeed, direction, rotate, gyro);
}

void Drivebase::GyroDrive(bool fieldOriented)
{
    bool bAllowRotate = false;
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

void Drivebase::testDrive(bool go, float speed)
{
    this->Drive(speed, -speed, 0, 0);
}

/*
 Drive with direction off x axis (degrees), speed (mps), rotate (deg/s), and gyro (deg).
 All other drive functions feed into this one.
 */
void Drivebase::DriveMPS(float direction, float speed, float rotate, float gyro)
{
    direction += gyro;
    float rotateScaled = rotate * ROBOT_RADIUS * PI/180;
    //Motor speeds are dependent on direction and speed. These are the functions that return correct values.
    double rightFrontSpeed = speed * sin((45 - direction) * PI/180) + rotate;
    double leftFrontSpeed = speed * sin((135 - direction) * PI/180) + rotate;
    double leftBackSpeed = speed * sin((225 - direction) * PI/180) + rotate;
    double rightBackSpeed = speed * sin((315 - direction) * PI/180) + rotate;

    //Set motor speeds to calculated values
    DriveLowLevel(leftFrontSpeed, rightFrontSpeed, leftBackSpeed, rightBackSpeed);
}


//Parameters are pointer to the motor you want to set and the speed in m/s you want it to end up at
void Drivebase::SetMotorSpeed(rev::CANSparkMax * motor, float speed)
{
    float SetPoint = speed; //This is the speed we want to be at.
    float scale = 0.02;     //This needs to change lol
    //Error is the difference between the speed we want to be at and our current speed from that motor.
    float error = SetPoint - motor->GetAlternateEncoder(rev::CANEncoder::AlternateEncoderType::kQuadrature, 8192).GetVelocity();
    float motorSpeedNow = motor->Get(); //Find current speed on the motor
    motor->Set(motorSpeedNow + error * scale); //Adjust current speed by the error
}

//Sets drive motor speeds (mps). Only function that should interact with drivebase motors.
void Drivebase::DriveLowLevel(float FrontLeftMPS, float FrontRightMPS, float RearLeftMPS, float RearRightMPS)
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