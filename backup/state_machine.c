#include <msp430.h>
#include <led.h>
#include "switches.h"
#include "buzzer.h"

//morse code for avocado. EDIT: writting it took too long
int counter = 0;
int dot = 200; //so i remember how much is for a dot
int dash = 500; //and the dash

void light_pattern(){
  //TURN LEDS depending on the pattern...WHATEVER THAT IS
  //LETTER A . -
  if(counter >= 0 & counter < 200){
    P1OUT |= LED_GREEN;
  } else if(counter >=200 & counter < 900){
    P1OUT &= ~LED_GREEN; //TURN OFF GREEN LED
    P1OUT |= LED_RED; //TURN ON RED LED
    //LETTER V . . . -
  } else if(counter >= 900 & counter < 1100){
    P1OUT &= ~LED_RED;//this is the first .
    P1OUT |= LED_GREEN; 
  } else if (counter >= 1100 & counter < 1200){
    P1OUT &= ~LEDS; //TURN OFF BOTH LEDS
  } else if(counter >= 1200 & counter < 1400){
    P1OUT |= LED_GREEN; //Second .
  } else if(counter >= 1400 & counter < 1600){
    P1OUT &= ~LED_GREEN; //TURN OFF GREEN LED
  } else if(counter >= 1600 & counter < 1800){
    P1OUT |= LED_GREEN; //third .
  } else if(counter >= 1800 & counter < 2000){
    P1OUT &= ~LED_GREEN;
  } else if (counter >= 2000 & counter < 2500){
    P1OUT |= LED_RED; //final -
  } else if(counter >= 2500 & counter < 2600){
    P1OUT &= ~LEDS;
  } else if(counter >= 2600){
    counter = 0; //starting from the bottom now we go to the top. Note: i havent slept too well
  }
}

void makeSomeNoise(){
  if(counter >= 0 & counter < 150){
    buzzer_set_period(500);
  } else if(counter >= 150 & counter < 1000){
    buzzer_set_period(1000);
  } else if(counter >= 1000 & counter < 2000){
    for(int i = 0; i < 5; i++){
      buzzer_set_period(i*100);
    }
  } else if(counter >= 2000 & counter < 2600){
    buzzer_set_period(0);
  } else if(counter>= 2600){
    counter = 0;
  }
}


static char blinkCount = 0;
static char blinkLimit = 5;
static short highLow = 250;
static short lowHigh = 1500;

void going_dim(){
  if(counter >= 250){
    counter = 0;
    buzzer_set_period(highLow);
    highLow += 250;
    blinkLimit++;
    if(blinkLimit >=9){
      blinkLimit =0;
      highLow = 250;
    }
  }
}

void going_bright(){
  if(counter >= 250){
    counter = 0;
    buzzer_set_period(lowHigh);
    lowHigh -250;
    blinkLimit--;
    if(blinkLimit <= 0){
      blinkLimit = 9;
      lowHigh = 800;
    }
  }
}

void flickerG(char sw){
  blinkCount++;
  if(blinkCount >= blinkLimit){
    blinkCount = 0;
    P1OUT |= LED_GREEN;
  }

  else{P1OUT &= ~LED_GREEN;}
  if(!sw){going_dim();}
  else{going_bright();}
}

void flickerR(char sw){
  blinkCount++;
  if(blinkCount >= blinkLimit){
    blinkCount = 0;
    P1OUT |= LED_RED;
  } else{P1OUT &= ~LED_RED;}
  if(!sw){going_dim();}
  else{going_bright();}
}

void flickering(char sw){
  blinkCount++;
  if(blinkCount >= blinkLimit){
    blinkCount = 0;
    P1OUT |= LEDS;
  }

  else{P1OUT &= ~LEDS;}
  if(!sw){going_dim();}
  else{going_bright();}
}
