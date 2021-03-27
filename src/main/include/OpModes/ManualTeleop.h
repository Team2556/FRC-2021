// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "Robot.h"
#include "OpMode.h"

#include "Subsystems/Climber.h"
#include "Subsystems/Drivebase.h"
#include "Subsystems/ControlPanel.h"
#include "Subsystems/Feeder.h"
#include "Subsystems/Shooter.h"

#include "Utilities/OI.h"

class ManualTeleop : public OpMode {
 public:
  ManualTeleop(Robot * pRobot, OI * DriverCMD, Climber * pClimber, ControlPanel * pCtrlPanel, Drivebase * pDrivebase, Feeder * pFeeder, Shooter * pShooter);

  Robot * pRobot;
  OI * DriverCMD;
  Climber * pClimber;
  ControlPanel * pCtrlPanel;
  Drivebase * pDrivebase;
  Feeder * pFeeder;
  Shooter * pShooter;


  void Start() override;
  void Run() override;
  bool Complete() override;

};
