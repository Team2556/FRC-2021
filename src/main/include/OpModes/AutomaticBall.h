// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "OpModes/OpMode.h"


class AutomaticBall : public OpMode {
 public:
  AutomaticBall();

  void Start() override;
  void Run() override;
  bool Complete() override;

  float angleOffNearestBall(); //Get angle to the nearest ball. This will need to use the pixy cam.
  void rotateToBall(); //Robot needs to be rotated so intake is in line with ball. 
  void moveToBall(); //Robot needs to move towards ball to pick it up. Also needs to run intake.
  // rotateToBall and moveToBall can be run simultaneously with holonomic drive to optimize efficiency.

  int timesRun;
};
