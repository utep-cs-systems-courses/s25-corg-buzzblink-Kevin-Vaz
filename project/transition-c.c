#include <msp430.h>
#include "switches.h"
#include "state_machine.h"

// Transition 1: cycles sw1 from 1 to 4
void transition1() {
  if (sw1 >= 4) {
    sw1 = 1;
  } else {
    sw1++;
  }
}

// Transition 2: cycles sw2 from 1 to 5
void transition2() {
  if (sw2 >= 5) {
    sw2 = 1;
  } else {
    sw2++;
  }
}

// Transition 3: cycles sw3 from 1 to 6
void transition3() {
  if (sw3 >= 6) {
    sw3 = 1;
  } else {
    sw3++;
  }
}

// Transition 4: cycles sw4 from 1 to 8
void transition4() {
  if (sw4 >= 8) {
    sw4 = 1;
  } else {
    sw4++;
  }
}
