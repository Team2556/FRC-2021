// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "Robot.h"
#include "rev/CANSparkMax.h"
#include "frc/drive/MecanumDrive.h"
#include "frc/Encoder.h"

#include "Utilities/Debug.h"
#include "Utilities/RobotMap.h"


class Drivebase {
 public:
  #define MAX_ROTATE  1
  #define MAX_STRAFE  1
  #define MAX_FORWARD 1
  Drivebase(Robot * pRobot);
  Robot * pRobot;
  // reference frame for robot is: +X Right, +Y Forward, +theta
  void Drive(float xSpeed, float ySpeed, float rotate, float gyro);
  
  void PolarDrive(float speed, float direction, float rotate, float gyro);
  void GyroDrive(float commandXSpeed, float commandYSpeed, float rotate, bool allowRotate, float gyroError);
  void FieldOrientedDrive(float xSpeed, float ySpeed, float rotate, float gyro);

  float MaxRotate(float rotate);
  float MaxStrafe(float xSpeed);
  float MaxForward(float ySpeed);

  void InvertMotors();
  // rev::CANSparkMax  rightFront{DRIVE_RIGHT_FRONT, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  // rev::CANSparkMax  leftFront{DRIVE_LEFT_FRONT, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  // rev::CANSparkMax  rightBack{DRIVE_RIGHT_REAR, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  // rev::CANSparkMax  leftBack{DRIVE_LEFT_FRONT, rev::CANSparkMaxLowLevel::MotorType::kBrushless};

  WPI_TalonSRX  rightFront{DRIVE_RIGHT_FRONT};
  WPI_TalonSRX  leftFront{DRIVE_LEFT_FRONT};
  WPI_TalonSRX  rightBack{DRIVE_RIGHT_REAR};
  WPI_TalonSRX  leftBack{DRIVE_LEFT_REAR};
  frc::MecanumDrive  MecanumDrive{rightFront, rightBack, leftFront, leftBack};
  
  Debug DrivebaseDebug{"/Subsystems/Drivebase"};

  // Aim Functions
  bool Aim();
  bool IsAimed();
  void RotateDrivebase(float speed);
};
