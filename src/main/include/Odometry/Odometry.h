// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "Utilities/Debug.h"

class Odometry {
 public:
  Odometry();

  float getX();
  float getY();

  void setCommandYaw();
  float getYaw();
  float getCommandYaw();
  float error();
  float getRotate();
  Debug OdometryDebug{"/Subsystems/Odometry"};
};
