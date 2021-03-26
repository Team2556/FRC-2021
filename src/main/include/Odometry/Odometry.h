// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#define _USE_MATH_DEFINES
#include "frc/kinematics/MecanumDriveOdometry.h"
#include "frc/kinematics/MecanumDriveKinematics.h"
#include "thread"
//#include "Utilities/RobotMap.h"
#include "rev/CANEncoder.h"
//#include "frc/Encoder.h"
#include <mutex>
#include <atomic>
#include "Subsystems/Drivebase.h"
//#include "Utilities/Debug.h"
#include "frc/Ultrasonic.h"
//#include "Robot.h"
#include <math.h>

//Ultrasonic distance from ground in inches
#define ULTRASONICHEIGHT 20

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
  
  float normalize360(float angle);

  frc::Pose2d getCurrentPose();


  std::thread OdometryPeriodicThread;

  void updatePose();

  // testing functions, will be removed
  void printWheelSpeeds(frc::MecanumDriveWheelSpeeds wheelSpeeds);
 private:
  Drivebase * pDrivebase;
  Robot * pRobot;
  
  bool canReset();
  

  //x and y are distances from robot center to wheel
  units::length::meter_t x{ROBOT_RADIUS};
  units::length::meter_t y{ROBOT_RADIUS};

  frc::Translation2d frontRight{x, -y};
  frc::Translation2d backRight{-x, -y};
  frc::Translation2d frontLeft{x, y};
  frc::Translation2d backLeft{-x, y};
  
  frc::MecanumDriveKinematics mecKinematics{frontLeft, frontRight, backLeft, backRight};
  
  //This pose2d stores our starting location relative to the origin
  frc::Pose2d startingPosition{0_m, 0_m, 0_deg};
  
  frc::MecanumDriveOdometry mecOdometry{mecKinematics, frc::Rotation2d{0_deg}, startingPosition};
  
  frc::Ultrasonic trenchUltrasonic{TRENCHULTRASONIC1, TRENCHULTRASONIC2};
  

  //Current Position pose is thread-safe for the getters
  std::atomic<frc::Pose2d>  currPose;

  frc::Pose2d  newPose{frc::Translation2d{1_m, 1_m}, frc::Rotation2d{0_deg}};

  void init();
  

  Debug OdometryDebug{"/Subsystems/Odometry"};

  //mutex can lock and unlock threads to allow common functions to be called safely
  std::mutex mtx;
};
