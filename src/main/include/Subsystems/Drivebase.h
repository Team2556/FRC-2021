// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "Robot.h"
#include "rev/CANSparkMax.h"
#include "frc/drive/MecanumDrive.h"
#include "frc/Encoder.h"


#include "Utilities/Debug.h"


class Drivebase {
 public:
  Drivebase(Robot * pRobot);
  Robot * pRobot;

  // reference frame for robot is: +X Right, +Y Forward, +theta
  void Drive(float xSpeed, float ySpeed, float rotate, float gyro);
  
  void PolarDrive(float speed, float direction, float rotate, float gyro);
  void GyroDrive();
  void FieldOrientedDrive();

  // rev::CANSparkMax  rightFront{DRIVE_RIGHT_FRONT, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  // rev::CANSparkMax  leftFront{DRIVE_RIGHT_FRONT, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  // rev::CANSparkMax  rightBack{DRIVE_RIGHT_FRONT, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  // rev::CANSparkMax  leftBack{DRIVE_RIGHT_FRONT, rev::CANSparkMaxLowLevel::MotorType::kBrushless};

  // frc::MecanumDrive  MecanumDrive{leftFront, leftBack, rightFront, rightBack};
  Debug DrivebaseDebug{"/Subsystems/Drivebase"};

  // Aim Functions
  bool Aim();
  bool IsAimed();
  void RotateDrivebase(float speed);
};
