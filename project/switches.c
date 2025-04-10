#include <msp430.h>
#include "timerLib/libTimer.h"
#include "switches.h"
#include "state_machine.h"
#include "led.h"
#include "buzzer.h"



static char switch_update_interrupt_sense(){
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);
  return p2val;
}

//setup switch

void switch_init(){

  P1REN |= SWITCHES;  //enable resistors for switches

  P1IE |= SWITCHES;   //enable interrupts from switches

  P1OUT|= SWITCHES;   //pull-ups for switches

  P1DIR &= SWITCHES;  //set switches
}

unsigned char select = 0;

//switch transitions
unsigned char sw1=0;
unsigned char sw2=0;
unsigned char sw3=0;
unsigned char sw4=0;



void switch_interrupt_handler(){

  char p2val = switch_update_interrupt_sense();

  if(!(p2val & sw1)){
	select = 1;
	transition1();
  }

  if(!(p2val & sw2)) {
    select =2;
    transition2();
  }
  if(!(p2val & sw3)){
    select = 3;
   transition3();
  }
  if(!(p2val & sw4)){
    select = 4;
    transition4();
  }
}

//make switch cases
void __interrupt_vec(WDT_VECTOR) WDT(){
  count++;
  switch(select){
    case 1:
      buzzer_set_period(0);
      switch(sw1){
	  case 1:
	  light_pattern();
	  break;
	  case 2:
	    P1OUT &= ~LEDS;
	    break;
	    default:
	    break;
	}
      break;

      case 2:
	P1OUT &= ~LEDS;
	switch(sw2){
	case 1:
	  makeSomeNoise();
	  break;

	case 2:
	  light_pattern();
	  makeSomeNoise();
	  break;
	default:
	break;
	}
	break;

	case 3:
	  buzzer_set_period(0);
	  switch(sw3){
	  case 1:
	    P1OUT ^= LED_GREEN;
	    buzzer_set_period(700);
	    break;
	  case 2:
	    P1OUT ^= LED_RED;
	    buzzer_set_period(1220);
	    break;
	  case 3:
	    P1OUT &= ~LEDS;
	    buzzer_set_period(0);
	    break;
	  default:
	  break;
	  }

	  case 4:
	    switch(sw4){
	    case 1:
	      flickering(1);
	      break;
	    case 2:
	       flickering(0);
	      break;
	    case 3:
	      flickering(0);
	      break;
	    case 4:
	      flickering(1);
	      break;
	    case 5:
	      P1OUT &= ~LEDS;
	      buzzer_set_period(0);
	      break;
	    default:
	      break;
	    }
	    break;
  default:
	    break;
  }
}
