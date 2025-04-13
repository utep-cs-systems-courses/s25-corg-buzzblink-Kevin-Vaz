COMMON_OBJECTS = main.o buzzer.o state_machine.o interrupt.o switches.o led.o
CPU            = msp430g2553
CFLAGS         = -mmcu=${CPU} -I./ -L/opt/ti/msp430_gcc/include
CC             = msp430-elf-gcc
AS             = msp430-elf-as

all: toy-c.elf toy-s.elf

# ELF using C transition
toy-c.elf: ${COMMON_OBJECTS} transition-c.o timerLib/libTimer.a
	${CC} ${CFLAGS} -o $@ $^
# ELF using Assembly transition
toy-s.elf: ${COMMON_OBJECTS} transition-s.o timerLib/libTimer.a
	${CC} ${CFLAGS} -o $@ $^

# Compile C sources to .o
load-c: toy-c.elf
	msp430loader.sh $^
load-s: toy-s.elf
	msp430loader.sh $^

# Cleanup
clean:
	rm -f *.o *.elf


# Header dependencies
main.c: led.h switches.h buzzer.h
switches.c: switches.h state_machine.h led.h buzzer.h
led.c: led.h
interrupt.c: switches.h
state_machine.c: state_machine.h led.h buzzer.h
buzzer.c: buzzer.h
transition.c: switches.h state_machine.h
