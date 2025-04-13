#ifndef led_included
#define led_included
#include <msp430.h>

#define LED_RED BIT0
#define LED_GREEN BIT6
#define LEDS (BIT0 | BIT6)

void led_init();  // Initialize LED

#endif

