// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "OpMode.h"

class AutomaticShoot : public OpMode {
 public:
  AutomaticShoot();

  void Start() override;
  void Run() override;
  bool Complete() override;

  bool revUp(); //Runs shooter motor to prepare to shoot. Return true when revved.
  bool aim(); //Rotate turret or drivebase and the hood to prepare to shoot. Return true when aimed.
  void shoot(); //Shoot a ball. Essentially just runs the feeder. ONLY SHOOT WHEN revUp and aim ARE TRUE

  int timesRun;
};
