#include <msp430.h>
#include "timerLib/libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"



int main(void) {

  switch_init();
  led_init();
  buzzer_init();
  configureClocks();
  enableWDTInterrupts();
  or_sr(0x18);
}
