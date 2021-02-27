// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "OpMode.h"
#include "frc/geometry/Pose2d.h"
#include "Odometry/Odometry.h"
#include "Robot.h"
#include "Subsystems/Drivebase.h"
#include "Utilities/Debug.h"

class AutomaticPath : public OpMode {
 public:
  AutomaticPath(Robot * pRobot, std::vector<frc::Pose2d*> waypoints, Drivebase * MecanumDrive, Odometry * OdometryController, float speedMultiplier = 0.5, float rotationMultiplier = 0.5);

  std::vector<frc::Pose2d*> waypoints;
  Robot * pRobot;
  Drivebase * MecanumDrive;
  Odometry * OdometryController;

  void Start() override;
  void Run() override;
  bool Complete() override;


 private:

  float speedMultiplier;
  float rotationMultiplier;
  bool complete;
  int timesRun;
  int waypointIndex;

  float distanceToNextWaypoint(frc::Pose2d * waypoint);
  float angleToNextWaypoint(frc::Pose2d * waypoint);
  bool atHeading(frc::Pose2d * waypoint);
  bool moveToNextWaypoint();

  Debug * PathDebug;
};
