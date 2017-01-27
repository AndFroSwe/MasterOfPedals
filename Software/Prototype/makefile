# Makefile for prototype project

# Compiler options
CC = avr-gcc
MCU_TARGET = atmega328p
OPTIMIZE = -O2
CFLAGS = -Wall -pedantic -mmcu=$(MCU_TARGET) -g $(OPTIMIZE)

# Compilations
prototype.o: prototype.c prototype.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o
