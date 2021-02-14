// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "string"
#include "Utilities/OI.h"

class Trigger {
 public:
  Trigger();
  
  std::string name;
  
  virtual bool Start();
};
