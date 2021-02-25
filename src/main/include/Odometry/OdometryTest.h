// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "Odometry/Odometry.h"
#include "Utilities/Debug.h"


class OdometryTest{
 public:
  OdometryTest();

  float getX();
  float getY();

  //void setCommandYaw() override;
  float getYaw();
  //float getCommandYaw() override;
  //float error() override;
  //float getRotate() override;


  Debug Test{"/Test"};
};
