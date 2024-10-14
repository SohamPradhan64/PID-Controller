#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor leftMotorA = motor(PORT1, ratio6_1, false);
motor leftMotorB = motor(PORT2, ratio6_1, false);
motor leftMotorC = motor(PORT3, ratio6_1, true);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT4, ratio6_1, true);
motor rightMotorB = motor(PORT5, ratio6_1, true);
motor rightMotorC = motor(PORT6, ratio6_1, false);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);

// PID settings for autonomous
double kP = 0.1; // Adjust as needed
double kI = 0.0;
double kD = 0.1;

double TkP = 0.1; 
double TkI = 0.0; 
double TkD = 0.1;

int desiredValue = 200;
int desiredTurnValue = 0;

int error;
int prevError = 0;
int derivative;
int totalError = 0;
int turnError;
int turnPrevError = 0;
int turnDerivative;
int turnTotalError = 0;
bool resetDriveSensors = false;
bool enablePID = true;

bool RemoteControlCodeEnabled = true;  // Variable to control remote control code
bool DrivetrainLNeedsToBeStopped_Controller1 = true;  // Variable for left drivetrain stop control
bool DrivetrainRNeedsToBeStopped_Controller1 = true;  // Variable for right drivetrain stop control

// Function to handle drive PID control
int drivePID() {
  while (enablePID) {
    if (resetDriveSensors) {
      resetDriveSensors = false;
      LeftDriveSmart.setPosition(0, degrees);
      RightDriveSmart.setPosition(0, degrees);
    }

    int leftMotorPosition = LeftDriveSmart.position(degrees);
    int rightMotorPosition = RightDriveSmart.position(degrees);
    int averagePosition = (leftMotorPosition + rightMotorPosition) / 2;

    // PID calculations for forward/backward movement
    error = desiredValue - averagePosition;
    derivative = error - prevError;
    totalError += error;

    double lateralMotorPower = (error * kP) + (derivative * kD) + (totalError * kI);

    // PID calculations for turning
    int turnDifference = leftMotorPosition - rightMotorPosition;
    turnError = desiredTurnValue - turnDifference;
    turnDerivative = turnError - turnPrevError;
    turnTotalError += turnError;

    double turnMotorPower = (turnError * TkP) + (turnDerivative * TkD) + (turnTotalError * TkI);

    // Applying the motor power
    LeftDriveSmart.spin(forward, lateralMotorPower + turnMotorPower, voltageUnits::volt);
    RightDriveSmart.spin(forward, lateralMotorPower - turnMotorPower, voltageUnits::volt);

    prevError = error;
    turnPrevError = turnError;

    vex::task::sleep(20); // Small delay for PID loop
  }
  return 1;
}

// Pre-autonomous setup
void pre_auton(void) {
  vexcodeInit();
}

// Main function for autonomous
void autonomous(void) {
  resetDriveSensors = true;
  desiredValue = 1000; // Set your desired target distance
  desiredTurnValue = 0; // Straight line for now
  vex::task drivePIDTask(drivePID); // Start the PID task

  // Autonomous drive code using PID
  vex::task::sleep(2000); // Drive for 2 seconds (just an example)
  enablePID = false; // Stop the PID loop
}

// Remote control loop function to be used in teleop
int rc_auto_loop_function_Controller1() {
  while(true) {
    if(RemoteControlCodeEnabled) {
      int drivetrainLeftSideSpeed = Controller1.Axis3.position() + Controller1.Axis1.position();
      int drivetrainRightSideSpeed = Controller1.Axis3.position() - Controller1.Axis1.position();

      // Handle left side stopping logic
      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          LeftDriveSmart.stop();
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
      } else {
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }

      // Handle right side stopping logic
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          RightDriveSmart.stop();
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      } else {
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }

      // Set velocities and spin motors based on joystick input
      if (!DrivetrainLNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }

      if (!DrivetrainRNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }
    }

    // Add a small delay to avoid CPU overload
    vex::task::sleep(20); 
  }
  return 0;
}

// Function to initialize the system and start the teleop task
void vexcodeInit(void) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}

// Main function
int main() {
  pre_auton();
  autonomous();
}
