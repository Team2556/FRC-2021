// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "AHRS.h"
#include "frc/SPI.h"

#include "Utilities/Debug.h"

class NavGyro {
  public:
    NavGyro();

    void Update();
    void setCommandYaw(double yaw);
    double getYaw();
    double getYawSpeed();
    double getCommandYaw();
    double GetYawError();
    double GetRotate();

    void ResetYaw();

  private:
    AHRS * pNavX;
    // Values for the navX
    double CommandYaw;

    Debug NavXDebug{"Subsystems/NavX"};

    double CurrentYaw;
    double PrevYaw;
    double Speed;
    
};
