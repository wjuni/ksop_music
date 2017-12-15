#include "ksop.h"

void sample_play() {
  stepper1(END);
  stepper2(END);

  stepper1(500);
  stepper2(500);
  delay(1000);
}
