// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Odometry/Limelight.h"

Limelight::Limelight() 
{
  table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
}

bool Limelight::HasTarget()
{
  return table->GetBoolean("tv", false);
}

double Limelight::xOffset()
{
  return table->GetNumber("tx", 0);
}