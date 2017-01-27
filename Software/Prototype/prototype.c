/* 
 * This file contains the main function of the program 
 * Desctiption: The prototype program controls the simple 2-pedal + 1 amp
 * channel switcher. It has 4 preset choice buttons. Pedals used in each preset
 * are hardcoded into program.
 *
 * Author: Andreas Fröderberg
 * TODO: Button input
 * TODO: Presets
 * TODO: Action on button press
 */

#include "prototype.h"

/* Presets for pedalstates
 * { pedal 1, pedal 2, amp channel }
 */
pedalstates preset1[PEDAL_COUNT] = {ON, ON, OFF};
pedalstates preset2[PEDAL_COUNT] = {OFF, ON, OFF};

int main(int argc, char *argv[])
{
    setupPins();
    setupTimerInterrupt();
    while(1)
    {
    }
    return 0;
}

void setupPins(void) 
{
    /* Set pins to output */
    PORT_ON(P1_DD, P1);
    PORT_ON(P2_DD, P2);
    PORT_ON(P3_DD, P3);
    /* Set pins to input */
    PORT_OFF(BUT_DD, BUT);
    /* Enable internal pullups */
    PORT_ON(BUT_REG, BUT);
}
void changePreset(pedalstates *preset)
{
    /* Checks all desired presets and enables needed pedals */
    /* Pedal 1 */
    if (preset[0] == ON) {
        PORT_ON(P1_PORT, P1);
    } else if (preset[0] == OFF) {
        PORT_OFF(P1_PORT, P1);
    }
    /* Pedal 2 */
    if (preset[1] == ON) {
        PORT_ON(P2_PORT, P2);
    } else if (preset[1] == OFF) {
        PORT_OFF(P2_PORT, P2);
    }
    /* Pedal 3 */
    if (preset[2] == ON) {
        PORT_ON(P3_PORT, P3);
    } else if (preset[1] == OFF) {
        PORT_OFF(P3_PORT, P3);
    }
}

inline void buttonRead(void)
{
    static read_mask = 0xf000;
	static uint16_t State = 0x00; /* Contains state history */
	/* Move state | Poll pin | Dont care */
	State = (State<<1) | ((PIND & _BV(BUT)) >> BUT) | (read_mask << 1);
	if (State == read_mask) { /* State == state comparison */
		/* Button action */
            PORTC ^= _BV(P1);
		}
}

void setupTimerInterrupt (void) 
{
    /* Starts a timer interrupt that triggers the button read */
	cli(); /* Disable interrupts */
	TCCR0A |= _BV(WGM01); /* Set to CTC mode */
	TCCR0B |= _BV(CS02) | _BV(CS00); /* Set clock source and prescaler */
	OCR0A =	OCNT_MAX; /* Set max counter value */
	TIMSK0 |= _BV(OCIE0A); /* Enable timer interrupt */
	sei(); /* Enable interrupts */
}

ISR(TIMER0_COMPA_vect)
{
    buttonRead();
}
