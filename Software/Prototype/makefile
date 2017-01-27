# Makefile for prototype project

# Compiler options
CC = avr-gcc
MCU_TARGET = atmega328p
OPTIMIZE = -O2
CFLAGS = -Wall -pedantic -mmcu=$(MCU_TARGET) -g $(OPTIMIZE)
OBJCOPY = avr-objcopy
# AVRDUDE options
PART = m328p
PROGRAMMER = atmelice_isp

# Compilations
all: prototype.elf prototype.hex flash

build: prototype.elf prototype.hex flash

clean:
	rm -f *.o *.elf *.hex

flash:
	avrdude -p $(PART) -c $(PROGRAMMER) -U flash:w:prototype.hex

prototype.o: prototype.c prototype.h
	$(CC) $(CFLAGS) -c -o $@ $<

prototype.elf: prototype.o
	$(CC) $(CFLAGS) -o $@ $<

prototype.hex: prototype.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

.PHONY: all clean flash
