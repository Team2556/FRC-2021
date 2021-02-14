// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "OpMode.h"
#include "frc/geometry/Pose2d.h"
#include "Odometry/Odometry.h"
#include "Robot.h"
#include "Subsystems/Drivebase.h"

class AutomaticPath : public OpMode {
 public:
  AutomaticPath(Robot * pRobot, std::vector<frc::Pose2d*> waypoints, Drivebase * MecanumDrive);

  std::vector<frc::Pose2d*> waypoints;
  Robot * pRobot;
  Drivebase * MecanumDrive;
  void Start() override;
  void Run() override;
  bool Complete() override;

  float distanceToNextWaypoint(frc::Pose2d * waypoint);
  float angleToNextWaypoint(frc::Pose2d * waypoint);
  void moveToNextWaypoint();

  float normalize360(float angle);

  int timesRun;
};
