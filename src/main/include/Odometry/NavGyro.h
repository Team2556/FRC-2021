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
    void setCommandYaw(float yaw);
    float getYaw();
    float getYawSpeed();
    float getCommandYaw();
    float GetYawError();
    float GetRotate();

    void ResetYaw();

  private:
    AHRS * pNavX;
    // Values for the navX
    float CommandYaw;

    Debug NavXDebug{"Subsystems/NavX"};

    float CurrentYaw;
    float PrevYaw;
    float Speed;
    
};
