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
    changePreset(preset1);

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
