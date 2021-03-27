// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "string"

#include "frc/smartdashboard/SmartDashboard.h"
class OpMode {
 public:
  OpMode(); // 
  
  std::string name;
  bool interruptible = false;

  virtual void Start(); // overide this

  virtual void Run(); // overide this

  virtual bool Complete(); // override this

};
