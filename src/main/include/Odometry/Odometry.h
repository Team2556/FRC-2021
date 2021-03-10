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
#include <mutex>
#include <atomic>
#include "Subsystems/Drivebase.h"
#include "Utilities/Debug.h"
#include "frc/Ultrasonic.h"

//Ultrasonic distance from ground in inches
#define ULTRASONICHEIGHT 20

class Odometry {
 public:
  Odometry(Drivebase * pDrivebase);

  void odometryPeriodic();

  float getX();
  float getY();

  void setCommandYaw();
  float getYaw();
  float getCommandYaw();
  float error();
  float getRotate();
  
  float normalize360(float angle);

  frc::Pose2d getCurrentPose();


  std::thread OdometryPeriodicThread;

  //TESTING
  float testGetEncoder();

 private:

  Drivebase * pDrivebase;
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
  
  frc::Ultrasonic trenchUltrasonic{TRENCHULTRASONIC1, TRENCHULTRASONIC2};
  

  //Current Position pose is thread-safe for the getters
  std::atomic<frc::Pose2d>  currPose;

  void updatePose();
  bool canReset();

  Debug OdometryDebug{"/Subsystems/Odometry"};

  //mutex can lock and unlock threads to allow common functions to be called safely
  std::mutex mtx;
};
