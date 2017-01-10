/*
 * encoder.c
 *
 * Created: 1/5/2017 2:23:34 PM
 *  Author: Andreas Fröderberg
 */ 

#include "encoder.h"

/** Setup functions **/
void enc_setup_interrupts(void)
{
	/* 
	* Setup pin interrupts for A and B pulse of encoder
	*/

	cli(); /* Disable interrupts */
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
	ENC_LED_PORT &= ~_BV(ENC_GREEN) & ~_BV(ENC_RED);
}


/* LED functions */
void enc_green_on(void)
{
	ENC_LED_PORT |= _BV(ENC_GREEN);
}

void enc_green_off(void)
{
	ENC_LED_PORT &= ~_BV(ENC_GREEN);
}

void enc_red_on(void)
{
	ENC_LED_PORT |= _BV(ENC_RED);
}

void enc_red_off(void)
{
	ENC_LED_PORT &= ~_BV(ENC_RED);
}