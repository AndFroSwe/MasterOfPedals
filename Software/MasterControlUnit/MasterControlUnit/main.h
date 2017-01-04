/*
 * main.h
 *
 * Created: 1/3/2017 5:02:14 PM
 *  Author: Andreas Fröderberg
 *
 * TODO: Encoder
 * TODO: Implement state machine
 */ 


#ifndef MAIN_H_
#define MAIN_H_

/* Includes */
#include <avr/io.h>
#include <avr/interrupt.h>

/* Defines */
#define ENC_INT_VECTOR PCINT2_vect /* Interrupt vector for encoder pulses */
#define ENC_REGISTER DDRD /* Direction register of encoder pulses */
#define ENC_PORT PORTD /* Port register of encoder */
#define ENC_A_PIN PD2 /* Encoder A pulse */
#define ENC_B_PIN PD3 /* Encoder B pulse */
#define ENC_LED_REGISTER DDRB /* Direction register for encoder leds */
#define ENC_LED_PORT PORTB /* Port register for encoder leds */
#define ENC_GREEN PB6 /* Encoder green led pin */
#define ENC_RED PB7	/* Encoder red led pin */
#define DEBOUNCE_MS 5 /* ms between button reads */
#define F_CLK 8000000UL /* Internal clock frequency [Hz] */
#define PRESCALER 1024 /* Prescaler used in debouncing */
#define OCNT_MAX F_CLK/PRESCALER*DEBOUNCE_MS/1000-1 /* Compare counter max value before interrupt is generated */

/* Macros */
#define SET(P, B) P |= _BV(B) /* Macro for setting register B on port P */
#define CLEAR(P, B) P &= ~_BV(B) /* Macro for clearing bit B on port P */
#define TOGGLE(P, B) P ^= _BV(B) /* Macro for toggling bt B on port P */

/* Prototypes */
void enc_setup_pins(void); /* Setup i/o */
void enc_setup_interrupts(void); /* Setup pin interrupts for encoder */
void setup_debounce(void); /* Setup button debouncing */

#endif /* MAIN_H_ */