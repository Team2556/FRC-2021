// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "frc/PIDController.h"
#include "frc/PIDOutput.h"
#include "frc/PIDSource.h"

class PIDOutputWrapper : public frc::PIDOutput
{
  public:
    PIDOutputWrapper(double * outputPTR)
    {
      this->outputVar = outputPTR;
    }
    void PIDWrite(double output)
    {
      *this->outputVar = output;
    }
  private:
    double * outputVar;
};


class PIDWrapper 
{
  public:
    PIDWrapper(double p, double i, double d, double f, double * outputLocation, frc::PIDSource * source);
  
    void SetP(double p);
    void SetI(double i);
    void SetD(double d);
    void SetF(double f);
    void SetOutput(double * outputLocation);
    void SetSource(frc::PIDSource * source);

    double GetP();
    double GetI();
    double GetD();
    double GetF();
    double * GetOutput();
    frc::PIDSource * GetSource();

  private:
    PIDOutputWrapper * output;
    frc::PIDController * controller;

    double p;
    double i;
    double d;
    double f;
    double * outputLocation;
    frc::PIDSource * source;
};
