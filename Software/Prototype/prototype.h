/* 
 * Header file for prototype.c 
 * Author: Andreas Fröderberg
 */

#ifndef PROTOTYPE_H
#define PROTOTYPE_H 

/* Defines */
#define PEDAL_COUNT 3 /* Number of pedals and amp channels that are controlled */
#define PORT_ON(reg, p) reg |= _BV(p)
#define PORT_OFF(reg, p) reg &= ~_BV(p)
/* Pedal ports */
#define P1_PORT PORTC
#define P1_DD DDRC
#define P1 PC5
#define P2_PORT PORTB
#define P2_DD DDRB
#define P2 PB0
#define P3_PORT PORTC
#define P3_DD DDRC
#define P3 PC3
/* Button debounce */
#define BUT_REG PORTD /* Button register */
#define BUT PD1 /* Button pin */
#define DEBOUNCE_MS 5 /* ms between button reads */
#define F_CLK 8000000UL /* Internal clock frequency [Hz] */
#define PRESCALER 1024 /* Prescaler used in debouncing */
#define OCNT_MAX F_CLK/PRESCALER*DEBOUNCE_MS/1000-1 /* Compare counter max value before interrupt is generated */

/* Includes */
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>


/* Typedefs */
typedef enum pedalstates {ON, OFF} pedalstates;

/* Function prototypes */
void setupPins(void);
void changePreset(pedalstates *); /* Engages pedals according to preset */
inline void buttonRead(void); /* Debounced read of a button */
void setupTimerInterrupt(void); /* Setup timer interrupt used in button db*/


#endif /* ifndef PROTOTYPE_H */
