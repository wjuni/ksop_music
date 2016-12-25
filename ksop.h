#pragma once
#ifndef __KSOP_H_
#define __KSOP_H_
// ============== PIN CONFIGURATION ================
#define STEPPER1_1 46
#define STEPPER1_2 47
#define STEPPER1_3 48
#define STEPPER1_4 49
#define STEPPER2_1 50
#define STEPPER2_2 51
#define STEPPER2_3 52
#define STEPPER2_4 53

#define SERVO1 10
#define SERVO2 11
#define SERVO3 12

#define STEPPER1_SENSOR 2
#define STEPPER2_SENSOR 3

// ============== MISC CONFIGURATION ===============
#define STEPPER_SPEED 300
#define STEPPER_UNIT_STEP 100
#define STEPPER_MAX_MOVE_MIL 10000
// =================================================

#include<Servo.h>
#include<Stepper.h>
#include<SoftwareSerial.h>
#include<Arduino.h>
#define END 0x7FFF

void stepper1(int steps);
void stepper2(int steps);
void servo1(int angle);
void servo2(int angle);
void servo3(int angle);
void stepper1_end();
void stepper2_end();

#endif
