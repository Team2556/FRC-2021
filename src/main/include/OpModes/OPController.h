// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "Utilities/OI.h"
#include "OpModes/OpMode.h"
#include "Triggers/Trigger.h"

class OPController {
 public:
  OPController(OI * OIObjectParam, std::vector<OpMode*> opModes, std::vector<Trigger*> triggers);
  std::vector<OpMode*> OpModes;
  std::vector<Trigger*> Triggers;
  OI * DriverCMD;

  OpMode * nextOp();

  void ControllerPeriodic();

  OpMode * CurrOp;

};
