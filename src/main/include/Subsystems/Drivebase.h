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
  void Drive(float fForward, float fStrafe, float rotate, float gyro);
  
  void PolarDrive(float speed, float direction, float rotate, float gyro);
  void GyroDrive();
  void FieldOrientedDrive();

  Debug DrivebaseDebug{"/Subsystems/Drivebase"};

  // Aim Functions
  bool Aim();
  bool IsAimed();
  void RotateDrivebase(float speed);

  rev::CANEncoder GetEncoderLF();
  rev::CANEncoder GetEncoderRF();
  rev::CANEncoder GetEncoderLR();
  rev::CANEncoder GetEncoderRR();



 private:
  //Drivebase motors
  rev::CANSparkMax  rightFront{DRIVE_RIGHT_FRONT, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax  leftFront{DRIVE_LEFT_FRONT, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax  rightBack{DRIVE_RIGHT_REAR, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANSparkMax  leftBack{DRIVE_LEFT_REAR, rev::CANSparkMaxLowLevel::MotorType::kBrushless};

 private:
  //Drivebase Object
  frc::MecanumDrive  MecanumDrive{leftFront, leftBack, rightFront, rightBack};
};
