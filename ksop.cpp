/* 
 *  KSOP 2017 Winter Camp Music Library
 *  Hwijoon Lim (wjuni@kaist.ac.kr)
 */
 
#include "ksop.h"
static Stepper _stepper1(200, STEPPER1_1, STEPPER1_2, STEPPER1_3, STEPPER1_4);
static Stepper _stepper2(200, STEPPER2_1, STEPPER2_2, STEPPER2_3, STEPPER2_4);
static Servo _servo1, _servo2, _servo3, _servo4;
static bool initiated = false;
static void ksop(){
  _servo1.attach(SERVO1);
  _servo2.attach(SERVO2);
  _servo3.attach(SERVO3);
  _servo4.attach(SERVO4);
  
  _stepper1.setSpeed(STEPPER_SPEED);
  _stepper2.setSpeed(STEPPER_SPEED);
  pinMode(STEPPER1_SENSOR, INPUT_PULLUP);
  pinMode(STEPPER2_SENSOR, INPUT_PULLUP);
  initiated = true;
}
void stepper1(int steps){
  if(!initiated) ksop();
  if(steps==END)
    stepper1_end();
  else
      _stepper1.step(steps);
    digitalWrite(STEPPER1_1, LOW);
    digitalWrite(STEPPER1_2, LOW);
    digitalWrite(STEPPER1_3, LOW);
    digitalWrite(STEPPER1_4, LOW);
    digitalWrite(STEPPER2_1, LOW);
    digitalWrite(STEPPER2_2, LOW);
    digitalWrite(STEPPER2_3, LOW);
    digitalWrite(STEPPER2_4, LOW);
}
void stepper2(int steps){
  if(!initiated) ksop();
  if(steps==END)
    stepper2_end();
  else
      _stepper2.step(steps);
    digitalWrite(STEPPER1_1, LOW);
    digitalWrite(STEPPER1_2, LOW);
    digitalWrite(STEPPER1_3, LOW);
    digitalWrite(STEPPER1_4, LOW);
    digitalWrite(STEPPER2_1, LOW);
    digitalWrite(STEPPER2_2, LOW);
    digitalWrite(STEPPER2_3, LOW);
    digitalWrite(STEPPER2_4, LOW);
}
void servo1(int angle){
  if(!initiated) ksop();
  _servo1.write(angle);
}
void servo2(int angle){
  if(!initiated) ksop();
  _servo2.write(angle);
}
void servo3(int angle){
  if(!initiated) ksop();
  _servo3.write(angle);
}

void stepper1_end(){
  if(!initiated) ksop();
  long start = millis();
  while(digitalRead(STEPPER1_SENSOR) == HIGH){
    _stepper1.step(-STEPPER_UNIT_STEP);
    delay(1);
    if(millis()-start > STEPPER_MAX_MOVE_MIL)
      return;
  }
  delay(100);
  _stepper1.step(-STEPPER_UNIT_STEP/2);
}
void stepper2_end(){
  if(!initiated) ksop();
  long start = millis();
  while(digitalRead(STEPPER2_SENSOR) == HIGH){
    _stepper2.step(-STEPPER_UNIT_STEP);
    delay(1);
    if(millis()-start > STEPPER_MAX_MOVE_MIL)
      return;
  }
  delay(100);
  _stepper2.step(-STEPPER_UNIT_STEP/2);
}
