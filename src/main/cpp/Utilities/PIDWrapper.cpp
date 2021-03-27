// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Utilities/PIDWrapper.h"

PIDWrapper::PIDWrapper(double p, double i, double d, double f, double * outputLocation, frc::PIDSource * source)
{
    this->p = p;
    this->i = i;
    this->d = d;
    this->f = f;
    this->outputLocation = outputLocation;
    this->source = source;
    this->output = new PIDOutputWrapper(outputLocation);
    this->controller = new frc::PIDController(p, i, d, f, source, output);
}

void PIDWrapper::SetP(double p)
{
    if(this->p != p)
    {
        this->p = p;
        delete controller;
        controller = new frc::PIDController(this->p, this->i, this->d, this->f, this->source, this->output);
    }
}
void PIDWrapper::SetI(double i)
{
    if(this->i != i)
    {
        this->i = i;
        delete controller;
        controller = new frc::PIDController(this->p, this->i, this->d, this->f, this->source, this->output);
    }
}
void PIDWrapper::SetD(double d)
{
    if(this->d != d)
    {
        this->d = d;
        delete controller;
        controller = new frc::PIDController(this->p, this->i, this->d, this->f, this->source, this->output);
    }
}
void PIDWrapper::SetF(double f)
{
    if(this->f != f)
    {
        this->f = f;
        delete controller;
        controller = new frc::PIDController(this->p, this->i, this->d, this->f, this->source, this->output);
    }
}
void PIDWrapper::SetOutput(double * outputLocation)
{
    if(this->outputLocation != outputLocation)
    {
        this->outputLocation = outputLocation;
        delete controller;
        delete output;
        output = new PIDOutputWrapper(outputLocation);
        controller = new frc::PIDController(this->p, this->i, this->d, this->f, this->source, this->output);
    }
}
void PIDWrapper::SetSource(frc::PIDSource * source)
{
    if(this->source != source)
    {
        this->source = source;
        delete controller;
        controller = new frc::PIDController(this->p, this->i, this->d, this->f, this->source, this->output);
    }
}

double PIDWrapper::GetP()
{
    return this->p;
}
double PIDWrapper::GetI()
{
    return this->i;
}
double PIDWrapper::GetD()
{
    return this->d;
}
double PIDWrapper::GetF()
{
    return this->f;
}
double * PIDWrapper::GetOutput()
{
    return this->outputLocation;
}
frc::PIDSource * PIDWrapper::GetSource()
{
    return this->source;
}