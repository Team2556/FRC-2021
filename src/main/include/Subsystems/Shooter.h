// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "Utilities/Debug.h"

class Shooter {
 public:
  Shooter();

  // Wheel Functions
  bool SpinUp();
  void SetSpinSpeed(float speed/*speed in rpm*/);
  void StopSpin();
  bool TargetSpeed();

  //Hood
  void MoveHood();
  bool SetHood(int angle /*units is encoder ticks*/);
  bool HoodAimed();
  void RotateHood(float speed);

  // Turret Functions
  bool Aim();
  bool IsAimed();
  void RotateTurret(float speed);

  Debug ShooterDebug{"/Subsystems/Shooter"};

};
