// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "Robot.h"
#include "rev/CANSparkMax.h"
#include "frc/drive/MecanumDrive.h"
#include "frc/Encoder.h"
#include "Odometry/Limelight.h"

#include "Utilities/Debug.h"

#define MAX_SPEED 4
#define PI 3.14159265358979323

class Drivebase {
 public:
  Drivebase(Robot * pRobot);
  Robot * pRobot;
  // reference frame for robot is: +X Right, +Y Forward, +theta
  void Drive(float fForward, float fStrafe, float rotate, float gyro);
  void DriveMPS(float direction, float speed, float rotate, float gyro);
  void PolarDrive(float speed, float direction, float rotate, float gyro);
  void GyroDrive(bool fieldOriented);
  void FieldOrientedDrive();

  Debug DrivebaseDebug{"/Subsystems/Drivebase"};

  // Aim Functions
  bool Aim(float error);
  bool IsAimed();
  void RotateDrivebase(float speed);

  rev::CANEncoder GetEncoderLF();
  rev::CANEncoder GetEncoderRF();
  rev::CANEncoder GetEncoderLR();
  rev::CANEncoder GetEncoderRR();

  void testDrive(bool go, float speed);

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


  void SetMotorSpeed(rev::CANSparkMax * motor, float speed);
  float GetRotate();
  void DriveLowLevel(float FrontLeftMPS, float FrontRightMPS, float RearLeftMPS, float RearRightMPS);
};
