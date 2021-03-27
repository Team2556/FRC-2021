// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "rev/CANSparkMax.h"
#include "frc/drive/MecanumDrive.h"
#include "frc/Encoder.h"

#include "Robot.h"

#include "Odometry/Limelight.h"

#include "Utilities/Debug.h"
#include "Utilities/PIDWrapper.h"

#define MAX_ROTATE .7
#define MAX_AIM_ERROR 5
#define MAX_SPEED 4
#define PI 3.14159265358979323


class AimPIDSource : public frc::PIDSource
{
  public:
    AimPIDSource(Limelight * limelightParam)
    {
      limelight = limelightParam;
    }

    double PIDGet()
    {
      return (*limelight).xOffset();
    }
  private:
    Limelight * limelight;
};

class Drivebase {
 public:
  Drivebase(Robot * pRobot);
  Robot * pRobot;
  // reference frame for robot is: +X Right, +Y Forward, +theta
  void Drive(double fForward, double fStrafe, double rotate, double gyro);
  void DriveMPS(double direction, double speed, double rotate, double gyro);
  void PolarDrive(double speed, double direction, double rotate, double gyro);
  void GyroDrive(bool fieldOriented);
  void FieldOrientedDrive();

  Debug DrivebaseDebug{"/Subsystems/Drivebase"};

  // Aim Functions
  bool Aim();
  double GetAimSpeed();
  bool IsAimed();

  rev::CANEncoder GetEncoderLF();
  rev::CANEncoder GetEncoderRF();
  rev::CANEncoder GetEncoderLR();
  rev::CANEncoder GetEncoderRR();

  void testDrive(bool go, double speed);

 private:
  //Drivebase motors
  rev::CANSparkMax  rightFront{DRIVE_RIGHT_FRONT, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax  leftFront{DRIVE_LEFT_FRONT, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax  rightBack{DRIVE_RIGHT_REAR, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax  leftBack{DRIVE_LEFT_REAR, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  //Drivebase Object
  //frc::MecanumDrive  RobotDrive{leftFront, leftBack, rightFront, rightBack};

  // is the robot using the gyro to turn to a preset location
  bool bPresetTurning = false;
  bool bRotatePrevious = false;


  void SetMotorSpeed(rev::CANSparkMax * motor, double speed);
  double GetRotate();
  void DriveLowLevel(double FrontLeftMPS, double FrontRightMPS, double RearLeftMPS, double RearRightMPS);

  AimPIDSource * source;
  PIDWrapper * AimPID;
  double * PIDOutput;
};
