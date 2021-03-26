// -----------------------------------
// CAN Bus Devices
// -----------------------------------

// Motor Controllers

#define DRIVE_LEFT_FRONT 1
#define DRIVE_RIGHT_FRONT 2
#define DRIVE_LEFT_REAR 3
#define DRIVE_RIGHT_REAR 4

//Feeder/Intake Placeholders.
#define INTAKE_OUT 56
#define CAN_INTAKE 6
#define HOPPER_MOTOR 5 
#define FEEDER_HIGH 7
#define FEEDER_LOW 8
#define HOPPER_KICKUP 101 //Currently not on robot, when added give real value
#define CAN_PCM 102 //Is this pneumatics? Why is this on our robot??
#define INTAKE_IN 103 //Why are there 2 motors to move the intake in and out????

//Xbox Controllers
#define         XBOX_ONE                0
#define         XBOX_TWO                1
#define         XBOX_THREE              2

//Shooter Motors
#define SHOOTER_MOTOR_1 9
#define SHOOTER_MOTOR_2 10
#define HOOD_MOTOR 11

//Control Panel
#define CONTROL_PANEL_SERVO 12
#define CONTROL_PANEL_SPINNER 13

//Climber
#define CLIMBER_MOTOR 14

//Limelight
#define LIMELIGHT 15

//All DIO Things
#define TRENCHULTRASONIC1 0
#define TRENCHULTRASONIC2 1 

//Robot Details
#define ROBOT_RADIUS 0.256