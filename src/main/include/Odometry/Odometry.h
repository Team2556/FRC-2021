// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "frc/kinematics/MecanumDriveOdometry.h"
#include "frc/kinematics/MecanumDriveKinematics.h"
#include "thread"
#include "Utilities/RobotMap.h"
#include "rev/CANEncoder.h"
#include "frc/Encoder.h"
#include "Subsystems/Drivebase.h"
#include <mutex>
#include <atomic>

#include "Utilities/Debug.h"
#include "Robot.h"

class Odometry {
 public:
  Odometry(Robot * pRobot, Drivebase * pDrivebase);

  void odometryPeriodic();

  float getX();
  float getY();
  float getYaw();

  void SetStartX(float X);
  void SetStartY(float Y);
  void SetStartYaw(float Yaw);

  float GetStartX();
  float GetStartY();
  float GetStartYaw();
  


  frc::Pose2d getCurrentPose();


  std::thread OdometryPeriodicThread;

  void updatePose();

  // testing functions, will be removed
  void printWheelSpeeds(frc::MecanumDriveWheelSpeeds wheelSpeeds);
 private:
  Drivebase * pDrivebase;
  Robot * pRobot;
  

  

  //x and y are distances from robot center to wheel
  units::length::meter_t x{.256};
  units::length::meter_t y{.256};

  frc::Translation2d frontRight{x, -y};
  frc::Translation2d backRight{-x, -y};
  frc::Translation2d frontLeft{x, y};
  frc::Translation2d backLeft{-x, y};
  
  frc::MecanumDriveKinematics mecKinematics{frontLeft, frontRight, backLeft, backRight};
  
  //This pose2d stores our starting location relative to the origin
  frc::Pose2d startingPosition{0_m, 0_m, 0_deg};
  
  frc::MecanumDriveOdometry mecOdometry{mecKinematics, frc::Rotation2d{0_deg}, startingPosition};
  

  frc::Encoder  frontRightEncoder{0, 1};
  frc::Encoder  frontLeftEncoder{2, 3};
  frc::Encoder  backRightEncoder{4, 5};
  frc::Encoder  backLeftEncoder{6, 7};

  //Current Position pose is thread-safe for the getters
  std::atomic<frc::Pose2d>  currPose;

  frc::Pose2d  newPose{frc::Translation2d{1_m, 1_m}, frc::Rotation2d{0_deg}};

  void init();
  

  Debug OdometryDebug{"/Subsystems/Odometry"};

  //mutex can lock and unlock threads to allow common functions to be called safely
  std::mutex mtx;
};
