/*
 * MasterControlUnit.c
 *
 * Created: 1/3/2017 5:01:10 PM
 * Author : Andreas Fröderberg
 */ 

#include "main.h"

/* Define states */
State s_run1 = {
	enc_green_on,
	enc_green_off
};

State s_run2 = {
	enc_red_on,
	enc_red_off
};

/* States and events */
State *states[] = {&s_run1,  &s_run2}; /* State array */
typedef enum State_code {run1, run2} State_code; /* State enumerators. Used for access */
typedef enum Event_code {enc_plus, enc_minus} Event_code; /* Available events */

typedef struct transitions { /* Standard transition format */
	State_code this_state;
	Event_code this_event;
	State_code next_state;
} Transitions;

Transitions transition_lookup[] = { /* Lookup table for all transitions */
	{run1, enc_plus, run2},
	{run1, enc_minus, run2},
	{run2, enc_plus, run1}
};

#define TRANS_COUNT (sizeof(transition_lookup)/sizeof(*transition_lookup)) /* Define number of transitions */

State_code cur_state = run1;

int main(void)
{
	enc_setup_pins();
	enc_setup_interrupts();
	states[cur_state]->entry_action();
    while (1) 
    {
    }
}



/** Interrupt service routines **/
ISR(ENC_INT_VECTOR) 
{
	/* 
	 * Interrupt service routine that handles encoder pulses.
	 */
	static int8_t lookup_table[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
	static uint8_t enc_val = 0; /* Holds encoder history */
	static int8_t enc_count = 0; /* Holds amount of encoder ticks has passed since click */

	enc_val = enc_val << 2;    /* Make room for new readings */
	/* This part will need to be changed if encoder pins are changed */
	enc_val = enc_val | ((PIND & 0x0C) >> 2); /* Mask encoder pins and move them to LSB */
	enc_count += lookup_table[enc_val & 0x0F];  // update encoder history

	/* State machine handling */
	if ((enc_count/4) == 1) { /* Enc_plus event */
		make_transition(&cur_state, enc_plus);
		enc_count = 0;
	} else if ((enc_count/4) == -1) { /* Enc_minus event */
		make_transition(&cur_state, enc_minus);
		enc_count = 0;
	}
}
/*
ISR(TIMER0_COMPA_vect)
{
	debounced_read();
}
*/

/** State functions **/
inline void make_transition(State_code *s, Event_code e)
{
	/* 
	 * Fires appropriate entry and exit actions depending on current state
	 * and current event. Also updates current event global variable.
	 * Is inline to reduce function call overhead when run in an ISR.
	 * Not that NULL_EVENT should be defined to a number that is not 
	 * present in enum for states!
	 */
	State_code next_state = NULL_EVENT;
	lookup_transition(&next_state, *s, e);
	if (next_state != NULL_EVENT) {
		states[*s]->exit_action(); /* Before leaving current state */
		*s = next_state;
		states[*s]->entry_action(); /* Enter new state */
	}
}

inline void lookup_transition(State_code *next, State_code s, Event_code e)
{
	/* 
	 * Loops throuhg transition table and updates next state variable
	 * if there is a valid transition. Otherwise, next pointer is left
	 * as it was. This algorithm is to allow for events that should 
	 * trigger no action.
	 */
	int i; /* Loop variable */
	for(i = 0; i < TRANS_COUNT; ++i)
	{
		if ((s == transition_lookup[i].this_state) && (e == transition_lookup[i].this_event)) /* Find state and event in lookup */
		{
			*next = transition_lookup[i].next_state; /* Return the next state */
		}
	}
};
