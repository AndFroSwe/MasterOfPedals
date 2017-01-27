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

int main(int argc, char *argv[])
{
    setupTimerInterrupt();
    while(1){}
    return 0;
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
    static uint16_t read_mask = 0xe000; /* Masks out unwanted values */
    static uint16_t state = 0x00; /* Pin history */
    /* Shift | read button | mask away ignored values */
    state = (state << 1) | (BUT_REG & _BV(BUT)) >> BUT | (read_mask << 1);
    if (state == read_mask) {
        changePreset(preset1);
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
