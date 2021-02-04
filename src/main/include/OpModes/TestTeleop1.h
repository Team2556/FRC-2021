// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "OpMode.h"

class TestTeleop1 : public OpMode {
 public:
  TestTeleop1();
  
  void Start() override;
  void Run() override;
  bool Complete() override;

  int timesRun;
};
