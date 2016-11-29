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
 * TODO: Input defines
 * TODO: Output defines
 * TODO: Button interrupt
 * TODO: USART setup
 * TODO: Preset setup function
 * TODO: Go into preset interrupt
 */ 

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}

