/*
 * MasterControlUnit.c
 *
 * Created: 1/3/2017 5:01:10 PM
 * Author : Andreas Fröderberg
 */ 

 #include "main.h"

 /*** Globals ***/
volatile long enc_count = 0; /* Global that hold current value for encoder count */

/** State machine variables **/
/* Function pointer array and enum must match! */
void (*states[]) (void) = {s_save, s_cancel, s_idle}; /* Function pointer array containing event entry actions */
enum state_codes {save, cancel, idle}; /* State variables */

/* Events */
enum events {e_enc_plus, e_enc_minus, e_enc_button}; /* System events */

/* Transitions */
struct transistions {
	/* Struct used in transition lookup */
	enum state_codes this_state; /* Current state */
	enum events this_event; /* Current event */
	enum state_codes next_state; /* Next event based on lookup */
};

/* Transition lookup */
struct transistions state_transitions [] = {
	/* Array that determines what happens during an event */
	{save, e_enc_plus, cancel},
	{save, e_enc_minus, cancel},
	{save, e_enc_button, idle},
	{cancel, e_enc_plus, save},
	{cancel, e_enc_minus, save},
	{cancel, e_enc_button, idle},
	{idle, e_enc_plus, idle},
	{idle, e_enc_minus, idle},
	{idle, e_enc_button, save}
};

/* State machine defines */
#define TRANS_COUNT (sizeof(state_transitions)/sizeof(*state_transitions)) /* Define number of transitions */
#define ENTRY_STATE idle /* Starting state */
/* State machine globals */
enum state_codes cur_state; /* Global containing current state */
void (*state_fun) (void); /* Global state function pointer */

int main(void)
{
	/* Initialize hardware to handle encoder */
	enc_setup_pins();
	enc_setup_interrupts();
	setup_debounce();
	DDRC &= ~_BV(PC0) & ~_BV(PC1);
	PORTC = _BV(PC0) | _BV(PC1);
	/* Setup state machine */
	cur_state = ENTRY_STATE; /* Define starting state */
	state_fun = states[cur_state]; /* Get first state function */
	state_fun(); /* Execute first state function */

    while (1) 
    {
    }
}

/** Setup functions **/
void enc_setup_interrupts(void)
{
	/* 
	 * Setup pin interrupts for A and B pulse of encoder
	 */

	PCICR = _BV(PCIE2); /* Enable interrupts on PCINT 16:23 */
	PCMSK2 = _BV(ENC_A_PIN) | _BV(ENC_B_PIN); /* Mask desired pins */
	sei(); /* Enable interrupts */
}
void enc_setup_pins(void)
{
	/* 
	 * Set direction and initial state of pins needed for encoder
	 */

	 /* Encoder pulses */
	ENC_REGISTER &= ~_BV(ENC_A_PIN) & ~_BV(ENC_B_PIN); /* Encoder as inputs */
	ENC_PORT |= _BV(ENC_A_PIN) | _BV(ENC_B_PIN); /* Enable internal pullup resistors */
	/* Encoder leds */
	ENC_LED_REGISTER |= _BV(ENC_GREEN) | _BV(ENC_RED); /* Output for LEDS */
	/* Set leds to off */
	CLEAR(ENC_LED_PORT, ENC_GREEN);
	CLEAR(ENC_LED_PORT, ENC_RED);
}
void setup_debounce(void)
{
	/* 
	 * Setup button debounce by having a timer interrupt that polls 
	 * the button pin periodically.
	 */

	 /* Setup timer interrupt */
	 cli(); /* Disable interrupts */
	TCCR0A |= _BV(WGM01); /* Set to CTC mode */
	TCCR0B |= _BV(CS02) | _BV(CS00); /* Set clock source and prescaler */
	OCR0A =	OCNT_MAX; /* Set max counter value */
	TIMSK0 |= _BV(OCIE0A); /* Enable timer interrupt */
	sei(); /* Enable interrupts */
}
/** Encoder leds **/
void enc_only_green(void)
{
	SET(ENC_LED_PORT, ENC_GREEN); /* Light green led */
	CLEAR(ENC_LED_PORT, ENC_RED); /* Turn off red led */
}
void enc_only_red(void)
{
	SET(ENC_LED_PORT, ENC_RED); /* Light red led */
	CLEAR(ENC_LED_PORT, ENC_GREEN); /* Turn off green led */
}
void enc_no_led(void)
{
	CLEAR(ENC_LED_PORT, ENC_RED); /* Turn off red led */
	CLEAR(ENC_LED_PORT, ENC_GREEN); /* Turn off green led */
}

/** Interrupt service routines **/
ISR(ENC_INT_VECTOR) 
{
	/* 
	 * Interrupt service routine that handles encoder pulses.
	 * enc_count needs to be volatile global
	 */
	static int8_t lookup_table[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
	static uint8_t enc_val = 0;
	static int8_t enc_count = 0;

	enc_val = enc_val << 2;    /* Make room for new readings */
	/* This part will need to be changed if encoder pins are changed */
	enc_val = enc_val | ((PIND & 0x0C) >> 2); /* Mask encoder pins and move them to LSB */
	enc_count += lookup_table[enc_val & 0x0F];  // update encoder history

	/* State machine handling */
	enum events cur_event;
	if ((enc_count/4) == 1) { /* Enc_plus event */
		cur_event = e_enc_plus;
		cur_state = lookup_transition(cur_state, cur_event); /* Find next state */
		state_fun = states[cur_state]; /* Get state function */
		state_fun(); /* Execute state function */
		enc_count = 0;
	} else if ((enc_count/4) == -1) {
		cur_event = e_enc_minus;
		cur_state = lookup_transition(cur_state, cur_event); /* Find next state */
		state_fun = states[cur_state]; /* Get state function */
		state_fun(); /* Execute state function */
		enc_count = 0;
	}
}
ISR(TIMER0_COMPA_vect)
{
	/* 
	 * Button debounce algorithm.
	 * Polls the state of the pin periodically and does an action when state is stable.
	 * Dont care and state comparison can be adapted to fit timing.
	 * To invert logic, pin poll can also be !(sfr & _BV(bit))
	 */

	static uint16_t State = 0x00; /* Contains state history */
	/* Move state | Poll pin | Dont care */
	State = (State<<1) | ((PINC & _BV(PC0)) >> PC0) | 0xe000;
	if (State == 0xf000) { /* State == state comparison */
		/* Action if button is pressed */
		cur_state = lookup_transition(cur_state, e_enc_button); /* Find next state */
		state_fun = states[cur_state]; /* Get state function */
		state_fun(); /* Execute state function */
		}
}

/** State functions **/
void s_save(void)
{
	enc_only_green();
}
void s_cancel(void)
{
	enc_only_red();
}
void s_idle(void)
{
	enc_no_led();
}
/* State support functions */
enum state_codes lookup_transition(enum state_codes s, enum events e)
{
	int i; /* Loop variable */
	for(i = 0; i < TRANS_COUNT; ++i)
	{
		if ((s == state_transitions[i].this_state) && (e == state_transitions[i].this_event)) /* Find state and event in lookup */
		{
			return state_transitions[i].next_state; /* Return the next state */
		}
	}
};

