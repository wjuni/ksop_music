/* 
 *  KSOP 2017 Winter Camp Music Library
 *  Hwijoon Lim (wjuni@kaist.ac.kr)
 */
 
#pragma once
#ifndef __KSOP_H_
#define __KSOP_H_

// ============= MOTOR CONFIGURATION ================
#define STEPPER1_DIRECTION 0
#define STEPPER2_DIRECTION 1

// ============== PIN CONFIGURATION ================
#define SERVO1 10
#define SERVO2 11
#define SERVO3 12
#define SERVO4 9
#define STEPPER1_SENSOR 2
#define STEPPER2_SENSOR 3
// ============== MISC CONFIGURATION ===============
#define STEPPER_OCR 64
#define STEPPER_UNIT_STEP 100
#define STEPPER_MAX_MOVE_MIL 10000
#define POST_INIT_DELAY 200
// =================================================

#include<Servo.h>
#include<SoftwareSerial.h>
#include<Arduino.h>
#define END 0x7FFFFFFFL

void stepper1(long steps);
void stepper2(long steps);
void servo1(int angle);
void servo2(int angle);
void servo3(int angle);
void servo4(int angle);
void stepper1_end();
void stepper2_end();



#endif
