// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "Utilities/Debug.h"
#include "Robot.h"
#include "Feeder.h"

class Shooter {
 public:
  Shooter(Robot * pRobot, Feeder * pFeeder);

  // Wheel Functions
  bool SpinUp();
  void SetSpinSpeed(float speed/*speed in rpm*/);
  void StopSpin();
  bool TargetSpeed();

  //Hood
  void MoveHood(); //Talon SRX Motor
  bool SetHood(int angle /*units is encoder ticks*/);
  bool HoodAimed();
  void RotateHood(float speed);

  Robot *pRobot;
  Feeder *pFeeder;

  Debug ShooterDebug{"/Subsystems/Shooter"};

 private:
  
  //CHECK ROBOT MAP (In Utilities) FOR MOTOR NAMES
  //Define two falcon 500s here. These will be the motors spinning the wheel that actually shoots the balls

  //Define a talon SRX here. This will move the hood

};
