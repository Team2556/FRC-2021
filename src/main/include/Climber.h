// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "Debug.h"
class Climber {
 public:
  Climber();

  Debug ClimberDebug{"/Subsystems/Climber"};
};
