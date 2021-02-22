// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "OpModes/OPController.h"

OPController::OPController(OI * OIObjectParam, std::vector<OpMode*> opModes, std::vector<Trigger*> triggers)
{
    OpModes = opModes;
    Triggers = triggers;
    DriverCMD = OIObjectParam;
    this->CurrOp = NULL;
}

//Checks if a new OpMode needs to be started.
OpMode * OPController::nextOp() {
    Trigger * startTrigger;
    //the names of the opmode and trigger must be the same
    std::string name;
    startTrigger = NULL;
    for(int i = 0; i < Triggers.size(); i++) 
    {
        //check if any triggers have been called
        if(Triggers[i]->Start())
        {
            startTrigger = Triggers[i];
            break;
        }
    }
    //If there are no triggers called, name is defaulted to manual
    if(!startTrigger)
    {
        name = "manual";
    }
    else
    {
        name = startTrigger->name;
    }

    OpMode * nextOpMode;
    nextOpMode = NULL;
    for(int i = 0; i < OpModes.size(); i++)
    {
        //find the opmode corresponding to the trigger called
        if(OpModes[i]->name == name)
        {
            nextOpMode = OpModes[i];
            break;
        }
    }
    //return the opmode that needs to be run.
    return nextOpMode;
}

//Run, Cancel, and Complete OpModes
void OPController::ControllerPeriodic()
{
    if(!CurrOp or CurrOp->interruptible or DriverCMD->CancelOP())
    {
        OpMode * TempPrevOp = CurrOp;
        CurrOp = nextOp();
        if(TempPrevOp != CurrOp)
        {
            CurrOp->Start();
        }
    }

    CurrOp->Run();

    if(CurrOp->Complete())
    {
        CurrOp = NULL;
    }
}