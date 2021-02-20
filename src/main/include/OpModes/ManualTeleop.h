// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "OpMode.h"
#include "Robot.h"
#include "Subsystems/Climber.h"
#include "Subsystems/Drivebase.h"
#include "Subsystems/ControlPanel.h"
#include "Subsystems/Feeder.h"
#include "Subsystems/Shooter.h"

class ManualTeleop : public OpMode {
 public:
  ManualTeleop(Robot * pRobot, Climber * pClimber, ControlPanel * pCtrlPanel, Drivebase * pDrivebase, Feeder * pFeeder, Shooter * pShooter);

  Robot * pRobot;
  Climber * pClimber;
  ControlPanel * pCtrlPanel;
  Drivebase * pDrivebase;
  Feeder * pFeeder;
  Shooter * pShooter;


  void Start() override;
  void Run() override;
  bool Complete() override;

  int timesRun;
};
