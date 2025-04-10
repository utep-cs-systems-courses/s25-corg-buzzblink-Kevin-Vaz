#include <msp430.h>

int count;
void transition1();
void transition2();
void transition3();
void transition4();
void transition5();
void light_pattern();
void makeSomeNoise();
static char blinkCount;
static char blinkLimit;
static short highLow;
static short lowHigh;
void going_dim();
void going_bright();
void flickerG();
void flickerR();
void flickering();
