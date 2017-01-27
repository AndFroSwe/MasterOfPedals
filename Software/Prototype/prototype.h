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
#define P1 PC3
#define P2_PORT PORTC
#define P2 PC4
#define P3_PORT PORTC
#define P3 PC5


/* Includes */
#include <avr/io.h>

/* Typedefs */
typedef enum pedalstates {ON, OFF} pedalstates;

/* Function prototypes */
void changePreset(pedalstates *); /* Engages pedals according to preset */


#endif /* ifndef PROTOTYPE_H */
