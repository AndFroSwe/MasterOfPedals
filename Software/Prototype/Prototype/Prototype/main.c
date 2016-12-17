/*
 * Prototype.c
 * Simulates a small scale version of the full guitar rig. Controls two pedal switches with two
 * buttons.
 * Function:
 * - 2 pedal switching relays
 * - Two buttons for choosing preset 
 * - 1 button for customizing preset
 * - External USART connection
 *
 * Created: 11/28/2016 10:18:24 PM
 * Author : Andreas Fröderberg
 *
 * Inputs
 **************************
 * Preset_1:	PB0
 * Set_1:		PC0
 * Set_2:		PC1
 **************************
 * Outputs
 **************************
 * PED_1:		PC4
 * PED_2:		PC5
 * USART RX:	PD0
 * USART TX		PD1
 * USART XCK	PD4
 *************************
 * TODO: Button interrupt
 * TODO: USART setup
 * TODO: Preset setup function
 * TODO: Go into preset interrupt
 * TODO: Enable external crystal
 */ 

#include "main.h"

void setupInputs(void) 
{
	/* Enables input pins */
	DDRB &= ~_BV(PRESET);
	DDRC &= ~_BV(SET_1) & ~_BV(SET_2);
}

void setupOutputs(void)
{
	DDRC |= _BV(PED_1) | _BV(PED_2);
}

int main(void)
{
	setupInputs();
	setupOutputs();
	mode = 0; // Start in hot mode
	current_preset = 0;
	// Starting settings for pedals
	for (int i = 0; i < PEDALS; ++i)
	{
		pedals_hot1[i] = 1;
	}
	for (int i = 0; i < PEDALS; ++i)
	{
		pedals_hot2[i] = 0;
	}
    while (1) // Main event loop
    {
		// Read buttons
		if (!((PINB >>  SET_1) & 1)) // Set 1 is pressed
		{
			_delay_ms(DEBOUNCE_MS);
			current_preset = 1; // Toggle preset mode
		} else if (!((PINB >>  SET_2) & 1)) {// Set 2 is pressed
			_delay_ms(DEBOUNCE_MS);
			current_preset = 0; // Toggle preset mode
		}
		// Set appropriate settings
		if (current_preset == 0)
		{
			PORTC &= ~_BV(PED_1) & ~_BV(PED_2);
		} else if (current_preset == 1)
		{
			PORTC |= _BV(PED_1) | _BV(PED_2);
		}

    }
}

