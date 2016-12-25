#include "ksop.h"
#define KS 136

void sample_play() {
 hit(5*KS);
 delay(300);
 hit(1*KS);
 hit(-1*KS);
 hit(-2*KS);
 delay(300);
 hit(2*KS);
 delay(300);
 hit(1*KS);
 hit(-1.5*KS);
 hit(-1.5*KS);
 
 hit(5.5*KS);
 delay(300);
 hit(0*KS);
 delay(150);
 hit(-2*KS);
 hit(1*KS);
 delay(300);
 hit(0);
 delay(100);
 hit(-3*KS);

 stepper1(END);
}
