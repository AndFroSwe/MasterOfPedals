/*
 * MasterControlUnit.c
 *
 * Created: 1/3/2017 5:01:10 PM
 * Author : Andreas Fröderberg
 */ 

 #include "main.h"

 /* Globals */
volatile long enc_count = 0; /* Global that hold current value for encoder count */

int main(void)
{
	/* Initialize hardware to handle encoder */
	enc_setup_pins();
	enc_setup_interrupts();
	setup_debounce();
	DDRC &= ~_BV(PC0) & ~_BV(PC1);
	PORTC = _BV(PC0) | _BV(PC1);
    while (1) 
    {
	/*
		if(!(PINC & _BV(PC0))) {
			SET(ENC_LED_PORT, ENC_GREEN);
		} else {
			CLEAR(ENC_LED_PORT, ENC_GREEN);
		}
		*/
    }
}

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

ISR(ENC_INT_VECTOR) 
{
	/* 
	 * Interrupt service routine that handles encoder pulses.
	 * enc_count needs to be volatile global
	 */
	static int8_t lookup_table[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
	static uint8_t enc_val = 0;

	enc_val = enc_val << 2;    /* Make room for new readings */
	/* This part will need to be changed if encoder pins are changed */
	enc_val = enc_val | ((PIND & 0x0C) >> 2); /* Mask encoder pins and move them to LSB */

	enc_count += lookup_table[enc_val & 0x0F];  /* Update encoder history */
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
		TOGGLE(ENC_LED_PORT, ENC_GREEN);
		}
}
