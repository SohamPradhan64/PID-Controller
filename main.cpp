/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\tavishi                                          */
/*    Created:      Sat Nov 02 2024                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Ramp                 motor         8               
// MogoMech             digital_out   A               
// Drivetrain           drivetrain    1, 2, 6, 7      
// Intake               motor         9               
// Ramp1                digital_out   B               
// Ramp2                digital_out   C               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
//global variables
bool pneumaticActive = false;

//toggle piston on or off
void togglePneumatic() {
  pneumaticActive = !pneumaticActive;

  if (pneumaticActive) {
    MogoMech.set(true);
  }
  else {
    MogoMech.set(false);
  }
}

void toggleRamp1() {
  pneumaticActive = !pneumaticActive;

  if (pneumaticActive) {
    Ramp1.set(true);
  }
  else {
    Ramp1.set(false);
  }
}

void toggleRamp2() {
  pneumaticActive = !pneumaticActive;

  if (pneumaticActive) {
    Ramp2.set(true);
  }
  else {
    Ramp2.set(false);
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Controller1.ButtonR1.pressed(togglePneumatic);
  Controller1.ButtonL1.pressed(toggleRamp1);
  Controller1.ButtonL2.pressed(toggleRamp2);
  
}
