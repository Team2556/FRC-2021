// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"

class Debug {
 public:
  Debug(std::string name);

  void PutString(std::string key, std::string value);
  void PutNumber(std::string key, float value);
  void PutBoolean(std::string key, bool value);

  std::shared_ptr<NetworkTable> table;
};
