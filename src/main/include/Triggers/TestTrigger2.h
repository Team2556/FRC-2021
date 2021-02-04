// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "Trigger.h"

class TestTrigger2 : public Trigger {
 public:
  TestTrigger2(OI * OIObjectParam);
  OI * DriverCMD;

  bool Start() override;
};
