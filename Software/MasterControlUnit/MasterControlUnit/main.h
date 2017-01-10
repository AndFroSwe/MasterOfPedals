/*
 * main.h
 *
 * Created: 1/3/2017 5:02:14 PM
 *  Author: Andreas Fröderberg
 *
 */ 


#ifndef MAIN_H_
#define MAIN_H_

/* Defines */
#define ENC_INT_VECTOR PCINT2_vect /* Interrupt vector for encoder pulses */

/*** Includes ***/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "HSMlib/HSMlib.h" /* For state machine functionality */
#include "Encoder/encoder.h" /* For encoder reading and LEDs */
//#include "Debounce/debounce.h" /* For debouncing and reading button */

inline void make_transition(enum State_code *,enum Event_code); /* Transition wrapper */
inline void lookup_transition(enum State_code *, enum State_code, enum Event_code); /* Finds next state, if exists */

#endif /* MAIN_H_ */