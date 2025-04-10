#include <msp430.h>

#include "libTimer.h"



#define LED_RED BIT6               // P1.0

#define LED_GREEN BIT0             // P1.6

#define LEDS (LED_RED | LED_GREEN)



#define SW1 BIT0   // P2.0

#define SW2 BIT1   // P2.1

#define SW3 BIT2   // P2.2

#define SW4 BIT3   // P2.3



#define SWITCHES (SW1 | SW2 | SW3 | SW4)



void switch_init() {

  P2REN |= SWITCHES;    /* Enables resistors for switches */

  P2IE |= SWITCHES;     /* Enable interrupts from switches */

  P2OUT |= SWITCHES;    /* Pull-ups for switches */

  P2DIR &= ~SWITCHES;   /* Set switches' bits for input */

  P2IFG &= ~SWITCHES;   /* Clear pending interrupts */

}



void led_init() {

  P1DIR |= LEDS;

  P1OUT &= ~LEDS;    /* LEDs initially off */

}



void wdt_init() {

  configureClocks();    /* Setup master oscillator, CPU & peripheral clocks */

  enableWDTInterrupts(); /* Enable periodic interrupt */

}



void main(void)

{

  switch_init();

  led_init();

  wdt_init();



  or_sr(0x8);  // CPU on, enable interrupts

}

void switch_interrupt_handler()
{
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES);   /* If switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);  /* If switch down, sense up */

  if (!(p2val & SW1)) P1OUT ^= LED_GREEN;  // Toggle green LED on SW1 press
  if (!(p2val & SW2)) P1OUT ^= LED_RED;    // Toggle red LED on SW2 press
  if (!(p2val & SW3)) P1OUT |= LED_GREEN;  // Turn green LED on SW3 press
  if (!(p2val & SW4)) P1OUT |= LED_GREEN; // Turn green LED off SW4 press
}

void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {         /* Did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;           /* Clear pending switch interrupts */
    switch_interrupt_handler();   /* Single handler for all switches */
  }
}
