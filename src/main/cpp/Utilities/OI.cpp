// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Utilities/OI.h"

OI::OI()
{

}

// ----------------------------------------------------------------------------
// Opmode commands
// ----------------------------------------------------------------------------

//Cancel Op modes when Xbox1 start button is pressed
bool OI::CancelOP()
{
    return Xbox1.GetStartButton();
}

//Pick up balls autonomously when Xbox1 A button is pressed
bool OI::AutomaticBall()
{
    return Xbox1.GetAButton();
}

//Shoot automatically when Xbox1 B button is pressed
bool OI::AutomaticShoot()
{
    return Xbox1.GetBButton();
}

//Navigate waypoints when Xbox1 X button is pressed
bool OI::AutomaticPath()
{
    return Xbox1.GetXButton();
}


// ----------------------------------------------------------------------------
// Driver commands
// ----------------------------------------------------------------------------

/*
Driver input for the forward movement of the robot.
in field oriented mode positive is away from the driver
in non-field oriented positive is forward in the robots frame of reference
*/
float OI::fMoveForward()
{
    float value = -Xbox1.GetY(frc::XboxController::kLeftHand);
    OIDebug.PutNumber("Forward", value);
    return value;
}

/*
Driver input for the strafing movement of the robot.
in field oriented mode positive is to the right in the drivers frame of reference
in non-field oriented positive is to the right in the robots frame of reference
*/
float OI::fMoveSideways()
{
    return Xbox1.GetX(frc::XboxController::kLeftHand);
}

float OI::fRotate()
{
    return Xbox1.GetX(frc::XboxController::kRightHand)*.8;
}

bool OI::bManualRotate()
{
    return fabs(this->fRotate()) > .05;
}

bool OI::bResetGyro()
{
    return Xbox1.GetAButtonPressed();
}

int OI::POV()
{
    return Xbox1.GetPOV();
}

// ----------------------------------------------------------------------------
// Codriver commands
// ----------------------------------------------------------------------------

//Extend and retract intake when Xbox2 X button is pressed.
bool OI::IntakeExtension()
{
    bool extended;
    if (Xbox2.GetYButtonPressed())
    {
        extended = false;
    }
    else if (Xbox2.GetXButtonPressed())
    {
        extended = true;
    } 
    return extended;
}

//Run intake in when Xbox2 A button is pressed, run intake out when Xbox2 B button is pressed.
float OI::IntakeRun()
{ 
    float x; 
    if (Xbox2.GetAButton())
    {
        x = -0.5;
    }
    else if (Xbox2.GetBButton())
    {
        x = 0.5;
    }
    else 
    {
        x = 0;
    }

    return x;
}

//Returns speed of hopper kickup motor using Xbox2 Dpad.
float OI::HopperKickup()
{
    float x; 
    if (Xbox2.GetPOV() == 90)
    {
        x = 0.5;
    }
    else if (Xbox2.GetPOV() == 270)
    {
        x = -0.5;
    }
    else 
    {
        x = 0;
    }

    return x;
}

//Returns hopper speed using Xbox2 Dpad
float OI::HopperRun()
{
    float x; 
    if (Xbox2.GetPOV() == 0)
    {
        x = 0.5;
    }
    else if (Xbox2.GetPOV() == 180)
    {
        x = -0.5;
    }
    else 
    {
        x = 0;
    }

    return x;
}

bool OI::StopShoot(){
    return Xbox2.GetTriggerAxis(frc::GenericHID::JoystickHand::kLeftHand);
}

// ----------------------------------------------------------------------------
// Test commands
// ----------------------------------------------------------------------------

// Designate some buttons as test buttons just to be able to test
// some functionality.
bool OI::bTestButton(int iButton)
    {
    bool    bButtonValue;
#ifdef JOYSTICK
    switch (iButton)
        {
        case 0  : bButtonValue = JStick1.GetRawButton( 2); break;   // Thumb
        case 1  : bButtonValue = JStick1.GetRawButton(11); break;
        case 2  : bButtonValue = JStick1.GetRawButton(12); break;
        case 3  : bButtonValue = JStick1.GetRawButton( 9); break;
        case 4  : bButtonValue = JStick1.GetRawButton(10); break;
        case 5  : bButtonValue = JStick1.GetRawButton( 7); break;
        default : bButtonValue = false;                    break;
        }

#else
    switch (iButton)
        {
        case 0 :
            bButtonValue = Xbox2.GetAButton();
            break;
        case 1 :
            bButtonValue = Xbox2.GetBButton();
            break;
        case 2 :
            bButtonValue = Xbox2.GetXButton();
            break;
        case 3 :
            bButtonValue = Xbox2.GetYButtonPressed();
            break;
        case 4 :
            bButtonValue = Xbox2.GetBumper(frc::XboxController::JoystickHand::kLeftHand);
            break;
        case 5 :
            bButtonValue = Xbox2.GetBumper(frc::XboxController::JoystickHand::kRightHand);
            break;
        case 6:
            bButtonValue = Xbox1.GetAButton();
            break;
        case 7:
            bButtonValue = Xbox1.GetBButton();
            break;
        case 8:
            bButtonValue = Xbox3.GetAButtonPressed();
            break;
        default :
            bButtonValue = false;
            break;
        }
#endif

    return bButtonValue;
    }
    

// ----------------------------------------------------------------------------

// Return a control test value
// From -1.0 to +1.0
float OI::fTestValue(int iControl)
{
    float   fControlValue;
    switch (iControl)
    {
        case 0 :
            fControlValue = Xbox2.GetTriggerAxis(frc::XboxController::JoystickHand::kRightHand);
            break;
        case 1 :
            fControlValue = Xbox2.GetTriggerAxis(frc::XboxController::JoystickHand::kLeftHand);
            break;
        case 2 :
            fControlValue = Xbox2.GetX(frc::XboxController::kLeftHand);
            break;
        case 3 :
            fControlValue = Xbox2.GetY(frc::XboxController::kLeftHand);
            break;
        case 4 :
            fControlValue = Xbox1.GetTriggerAxis(frc::XboxController::kRightHand);
            break;
        case 5 :
            fControlValue = Xbox1.GetY(frc::XboxController::kLeftHand);
            break;
        case 6 :
            fControlValue = Xbox2.GetX(frc::XboxController::kRightHand);
            break;
        default :
            fControlValue = 0.0;
            break;
    }

    return fControlValue;
}