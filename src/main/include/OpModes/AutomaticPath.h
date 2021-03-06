// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "frc/geometry/Pose2d.h"

#include "Robot.h"
#include "OpMode.h"

#include "Subsystems/Drivebase.h"

#include "Odometry/Odometry.h"

#include "Utilities/Debug.h"

class AutomaticPath : public OpMode {
 public:
  AutomaticPath(Robot * pRobot, std::vector<frc::Pose2d*> waypoints, Drivebase * MecanumDrive, Odometry * OdometryController, double speedMultiplier = 0.5, double rotationMultiplier = 0.5);

  std::vector<frc::Pose2d*> waypoints;
  Robot * pRobot;
  Drivebase * MecanumDrive;
  Odometry * OdometryController;

  void Start() override;
  void Run() override;
  bool Complete() override;


 private:

  double speedMultiplier;
  double rotationMultiplier;
  bool complete;
  int timesRun;
  int waypointIndex;

  double distanceToNextWaypoint(frc::Pose2d * waypoint);
  double angleToNextWaypoint(frc::Pose2d * waypoint);
  bool atHeading(frc::Pose2d * waypoint);
  bool moveToNextWaypoint();


  Debug * PathDebug;
};
