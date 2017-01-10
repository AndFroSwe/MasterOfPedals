/*
 * HSMlib.h
 *
 * Created: 1/5/2017 7:08:52 AM
 *  Author: Andreas Fröderberg
 */ 


#ifndef HSMLIB_H_
#define HSMLIB_H_

/*** Defines ***/
#define NULL_EVENT 9999 /* Define large number for event when nothing should happen */
/*** Includes ***/
/* AVR libs */
#include <avr/io.h>

/*** Declarations ***/
/* State */
typedef void (*State_action) (void); /* State function declaration */
typedef struct state { /* State struct declaration */
	State_action entry_action;
	State_action exit_action;
} State;
enum State_code; /* Holder for state names. Used for state lookup */
enum Event_code; /* Holder for event names. Used for state lookup */
State *states[]; /* Holds all state structs */

/*** Function prototypes ***/

#endif /* HSMLIB_H_ */