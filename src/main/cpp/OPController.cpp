// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "OPController.h"

OPController::OPController(std::vector<OpMode*> opModes, std::vector<Trigger*> triggers)
{
    OpModes = opModes;
    Triggers = triggers;
}

OpMode * OPController::nextOp() {
    Trigger * startTrigger;
    Trigger * tempTrigger;
    std::string name;
    startTrigger = NULL;
    for(int i = 0; i < Triggers.size(); i++) 
    {
        if(Triggers[i]->Start())
        {
            startTrigger = Triggers[i];
            break;
        }
    }

    if(!startTrigger)
    {
        name = "manual";
    }
    else
    {
        name = startTrigger->name;
    }

    OpMode * nextOpMode;
    for(int i = 0; i < OpModes.size(); i++)
    {
        if(OpModes[i]->name == name)
        {
            nextOpMode = OpModes[i];
            break;
        }
    }
    return nextOpMode;
}

void OPController::test()
{
    printf("pleasework");
}