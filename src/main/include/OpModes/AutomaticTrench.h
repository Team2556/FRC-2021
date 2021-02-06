// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "OpMode.h"

class AutomaticTrench : public OpMode {
 public:
  AutomaticTrench();

  void Start() override;
  void Run() override;
  bool Complete() override;

  float distanceToTrench(); //Get distance to trench
  float angleOffVertical(); //Get angle between current direction of robot and direction to go through trench
  bool correctAngle(); //If angleOffVertical is not close to 0, rotate drivebase to get closer. Return true if close to 0.
  float angleToTrench(); //Get angle that the robot needs to move in to get directly in front of trench.
  void moveToTrench(); //Move robot at angleToTrench to decrease distanceToTrench
  bool navigateTrench(); //Go through trench when distance to trench is 0ish and angleOffVertical is 0ish. Return true when through trench.


  int timesRun;
};
