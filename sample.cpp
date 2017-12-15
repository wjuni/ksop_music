#include "ksop.h"

void sample_play() {
  stepper1(END);
  stepper2(END);

  stepper1(500);
  stepper2(500);
  servo1(100);
  servo2(120);
  delay(1000);
  
  stepper1(500);
  stepper2(500);
  servo3(50);
  servo4(10);
  delay(500);
}
