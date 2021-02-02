// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "Trigger.h"

class TestTrigger1 : public Trigger {
 public:
  TestTrigger1(OI * OIObjectParam);
  OI * OIObject;

  bool Start() override;
};
