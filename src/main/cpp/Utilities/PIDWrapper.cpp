// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Utilities/PIDWrapper.h"

PIDWrapper::PIDWrapper(double p, double i, double d, double f, double * outputLocation, frc::PIDSource * source)
{
    this->output = new PIDOutputWrapper(outputLocation);
    this->controller = new frc::PIDController(p, i, d, f, source, output);
}
