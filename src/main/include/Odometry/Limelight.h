// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"

class Limelight{
  public:
    Limelight();
    
    bool HasTarget();

    double xOffset();

  private:
    std::shared_ptr<NetworkTable> table;

};
