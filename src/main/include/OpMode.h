// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "string"
class OpMode {
 public:
  OpMode(); // 
  
  std::string name;
  int timesRun;

  void Start(); // overide this

  void Run(); // overide this

  bool Complete(); // override this

};
