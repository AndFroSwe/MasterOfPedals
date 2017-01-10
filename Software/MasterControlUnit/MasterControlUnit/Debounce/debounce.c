/*
 * debounce.c
 *
 * Created: 1/5/2017 2:42:36 PM
 *  Author: Andreas Fröderberg
 */ 

 #include "debounce.h"

 inline void debounced_read(void)
 {
	/* 
	 * Button debounce algorithm.
	 * Polls the state of the pin periodically and does an action when state is stable.
	 * Dont care and state comparison can be adapted to fit timing.
	 * To invert logic, pin poll can also be !(sfr & _BV(bit))
	 */

	static uint16_t State = 0x00; /* Contains state history */
	/* Move state | Poll pin | Dont care */
	State = (State<<1) | ((DB_BUTTON_PIN_REG & _BV(DB_BUTTON_PIN)) >> DB_BUTTON_PIN) | 0xe000;
	if (State == 0xf000) { /* State == state comparison */
		/* Button action */
		int a=1;
		}
}

void setup_debounce_timer(void)
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
