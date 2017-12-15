#include "ksop.h"
static Servo _servo1, _servo2, _servo3, _servo4;
static bool initiated = false;
static volatile int StepA_seq = 0, StepB_seq = 0;
static volatile long StepA_Target = 0, StepB_Target = 0;
static volatile char StepA_dir = STEPPER1_DIRECTION, StepB_dir = STEPPER2_DIRECTION;
static char pattern[4] = {0b0101, 0b0110, 0b1010, 0b1001};
static void ksop(){
  _servo1.attach(SERVO1);
  _servo2.attach(SERVO2);
  _servo3.attach(SERVO3);
  _servo4.attach(SERVO4);
  pinMode(STEPPER1_SENSOR, INPUT_PULLUP);
  pinMode(STEPPER2_SENSOR, INPUT_PULLUP);
  
  PINL &= ~(0x0f);
  PINB &= ~(0x0f);
  PORTL &= ~ (0x0f);
  PORTB &= ~ (0x0f);
  // Use ATMega2560 Timer2 (8-bit), WGM=CTC(0x03), Match A Interrupt
  // Prescaler Selection = Clk/256 (0b110), Target Interrupt period 1ms, 16000kHz/256 = 62.5 kHz -> interrupt at 63
  // stop timer
  cli();
  TCCR2B &= ~((1 << CS22) | (1 << CS21) | (1 << CS20));
  TCCR2A &= ~((1 << WGM20));
  TCCR2B &= ~((1 << WGM22));
  TCCR2A |= ((1 << WGM21));
  TIMSK2 |= (1 << OCIE2A);
  OCR2A = STEPPER_OCR;
  TCCR2B |= (1 << CS32) | (1 << CS31) | (0 << CS30);
  sei();
  
  initiated = true;
}
void stepper1(long steps){
  if(!initiated) ksop();
  if(steps==END)
    stepper1_end();
  else
    StepA_Target = steps;
}
void stepper2(long  steps){
  if(!initiated) ksop();
  if(steps==END)
    stepper2_end();
  else
    StepB_Target = steps;
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
void servo4(int angle){
  if(!initiated) ksop();
  _servo4.write(angle);
}
void stepper1_end(){
  if(!initiated) ksop();
  long start = millis();
  while(digitalRead(STEPPER1_SENSOR) == HIGH){
    StepA_Target = STEPPER_UNIT_STEP;
    delay(10);
    if(millis()-start > STEPPER_MAX_MOVE_MIL)
      return;
  }
  delay(100);
  StepA_Target = -STEPPER_UNIT_STEP/2;
  delay(POST_INIT_DELAY);
}
void stepper2_end(){
  if(!initiated) ksop();
  long start = millis();
  while(digitalRead(STEPPER2_SENSOR) == HIGH){
    StepB_Target = STEPPER_UNIT_STEP;
    delay(10);
    if(millis()-start > STEPPER_MAX_MOVE_MIL)
      return;
  }
  delay(100);
  StepB_Target = -STEPPER_UNIT_STEP/2;
  delay(POST_INIT_DELAY);
}

ISR(TIMER2_COMPA_vect) {
  if(StepA_Target > 0) {
    char w = pattern[StepA_seq];
    PORTL &= ~ (0x0f);
    PORTL |= w;
    StepA_Target--;
    if(StepA_dir) {
      StepA_seq++;
      if(StepA_seq >=4) StepA_seq = 0;
    } else {
      StepA_seq--;
      if(StepA_seq < 0) StepA_seq = 3;
    }
    
  } else if (StepA_Target < 0) {
    char w = pattern[StepA_seq];
    PORTL &= ~ (0x0f);
    PORTL |= w;
    StepA_Target++;
    if(!StepA_dir) {
      StepA_seq++;
      if(StepA_seq >=4) StepA_seq = 0;
    } else {
      StepA_seq--;
      if(StepA_seq < 0) StepA_seq = 3;
    }
  } else {
      PORTL &= ~ (0x0f);
  }

  if(StepB_Target > 0) {
    char w = pattern[StepB_seq];
    PORTB &= ~ (0x0f);
    PORTB |= w;
    StepB_Target--;
    if(StepB_dir) {
      StepB_seq++;
      if(StepB_seq >=4) StepB_seq = 0;
    } else {
      StepB_seq--;
      if(StepB_seq < 0) StepB_seq = 3;
    }
    
  } else if (StepB_Target < 0) {
    char w = pattern[StepB_seq];
    PORTB &= ~ (0x0f);
    PORTB |= w;
    StepB_Target++;
    if(!StepB_dir) {
      StepB_seq++;
      if(StepB_seq >=4) StepB_seq = 0;
    } else {
      StepB_seq--;
      if(StepB_seq < 0) StepB_seq = 3;
    }
  } else {
      PORTB &= ~ (0x0f);
  }
}
