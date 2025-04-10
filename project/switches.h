#ifndef switches_include
#define switches_include

#define SW1 BIT0 //button s1
#define SW2 BIT1 //s2
#define SW3 BIT2 //s3
#define SW4 BIT3 //s4



#define SWITCHES (sw1|sw2|sw3|sw4)

unsigned char selector;

//transitions for state machine
unsigned char sw1;
unsigned char sw2;
unsigned char sw3;
unsigned char sw4;

static char interrupt_sense(); //update the interrupt sensing configuration

void switch_init();
void switch_interrupt_handler();

extern char switch_state_down, switch_state_changed;

#endif
