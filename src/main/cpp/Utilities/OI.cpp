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

// positive is forward
float OI::fMoveForward()
{
    float speed = Xbox1.GetY(frc::XboxController::kLeftHand);
    OIDebug.PutNumber("Forward", speed);
    return speed;
}

// positive is right
float OI::fMoveSideways()
{
    float speed =  Xbox1.GetX(frc::XboxController::kLeftHand);
    OIDebug.PutNumber("Forward", speed);
    return speed;
}

// positive is clockwise
float OI::fRotate()
{
    float speed = Xbox1.GetX(frc::XboxController::kRightHand);
    OIDebug.PutNumber("Forward", speed);
    return speed;
}

bool OI::bManualRotate()
{
    bool x;
    if ((fRotate() > 0.05) || (fRotate() < -0.05))
    {
        x = true;
    }
    else
    {
        x =  false;
    }
    OIDebug.PutBoolean("Manual Rotate", x);
    return x;
}



// ----------------------------------------------------------------------------
// Codriver commands
// ----------------------------------------------------------------------------

//Extend and retract intake when Xbox2 X button is pressed.
bool OI::IntakeExtension()
{
    static bool extended = false;
    if (Xbox2.GetXButtonPressed())
    {
        extended = !extended;
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