// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "AHRS.h"
#include "frc/SPI.h"
#include "frc/kinematics/MecanumDriveOdometry.h"
#include "frc/kinematics/MecanumDriveKinematics.h"
#include "thread"
#include "Utilities/RobotMap.h"
#include "rev/CANEncoder.h"
#include "frc/Encoder.h"
#include "Subsystems/Drivebase.h"

#include "Utilities/Debug.h"

class Odometry {
 public:
  Odometry();
  void odometryPeriodic();

  float getX();
  float getY();

  void setCommandYaw();
  float getYaw();
  float getCommandYaw();
  float error();
  float getRotate();
  frc::Pose2d getCurrentPose();

  float fNormalizeAngle360(float fAngle);
  float fNormalizeAngle180(float fAngle);
  
  float CommandYaw;
 private:
  AHRS * pNavX;

  //x and y are distances from robot center to wheel
  units::length::meter_t x = 0_m;
  units::length::meter_t y = 0_m;
  frc::Translation2d frontRight{x, y};
  frc::Translation2d backRight{x, -y};
  frc::Translation2d frontLeft{-x, y};
  frc::Translation2d backLeft{-x, -y};
  frc::MecanumDriveKinematics mecKinematics{frontLeft, frontRight, backLeft, backRight};
  //This pose2d stores our starting location relative to the origin
  frc::Pose2d startingPosition{0_m, 0_m, 0_deg};
  frc::MecanumDriveOdometry mecOdometry{mecKinematics, frc::Rotation2d{0_deg}, startingPosition};
  
  std::thread OdometryPeriodicThread;

  frc::Encoder  frontRightEncoder{0, 1};
  frc::Encoder  frontLeftEncoder{2, 3};
  frc::Encoder  backRightEncoder{4, 5};
  frc::Encoder  backLeftEncoder{6, 7};

  frc::Pose2d   currPose;

  void updatePose();

  Debug OdometryDebug{"/Subsystems/Odometry"};
};
