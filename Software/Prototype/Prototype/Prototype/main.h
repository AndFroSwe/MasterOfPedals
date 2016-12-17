/*
 * main.h
 *
 * Created: 11/29/2016 6:09:46 AM
 *  Author: Andreas Fröderberg
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000
#define PEDALS 2 // Number of pedals in loop
#define DEBOUNCE_MS 500 // Debounce time in ms
// Define inputs
#define PRESET PB0
#define SET_1 PC0
#define SET_2 PC1
// Define outputs
#define PED_1 PC4
#define PED_2 PC5
#define USART_RX PD0
#define USART_TX PD1
#define USART_XCK PD2


#include <avr/io.h>
#include <util/delay.h>

void setupInputs(void);
void setupOutputs(void);

// Globals
int mode; // DES state variable, 0 = Hot mode, 1 = Set mode
int current_preset; // Which pedal preset is currently chosen
int pedals_hot1[PEDALS]; // Pedals engaged in hot 1
int pedals_hot2[PEDALS]; // Pedals engaged in hot 2

#endif /* MAIN_H_ */