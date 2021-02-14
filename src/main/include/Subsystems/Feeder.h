// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "Robot.h"
#include "Utilities/RobotMap.h"

#include "Utilities/Debug.h"
class Feeder {
 public:
  Feeder();

  // Intake
  void SetIntake(bool Extended);
  bool IsExtended();
  void KeepExtending(); // used to keep intake moving to target. Only needed if we use a motor to exend rather than pistons

  void RunIntake();
  void RunIntake(float speed); // positive speed is pulling in, negative is out

  // Hopper
  void SpinHopper();
  void SpinHopper(float speed);

  void KickUp();
  void KickUp(float Speed); // positive is into the shooter, negative is out

  private:
  WPI_TalonSRX      Feeder_High_Motor{FEEDER_HIGH};
  WPI_TalonSRX      Feeder_Low_Motor{FEEDER_LOW};
  WPI_TalonSRX      Intake_Motor{CAN_INTAKE};
  WPI_TalonSRX      Hopper_Spinner{HOPPER_MOTOR};
  WPI_TalonSRX      Hopper_Kickup{HOPPER_KICKUP};

  frc::DoubleSolenoid   Intake_Solenoid{CAN_PCM, INTAKE_OUT, INTAKE_IN};
  Debug FeederDebug{"/Subsystems/Feeder"};
};
