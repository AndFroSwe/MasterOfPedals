/*
 * debounce.h
 *
 * Created: 1/5/2017 2:42:44 PM
 *  Author: Andreas Fröderberg
 */ 


#ifndef DEBOUNCE_H_
#define DEBOUNCE_H_

/*** Defines ***/
#define DB_BUTTON_PIN_REG PINC
#define DB_BUTTON_PIN PC0
/* For timer interrupt setup */
#define DEBOUNCE_MS 5 /* ms between button reads */
#define F_CLK 8000000UL /* Internal clock frequency [Hz] */
#define PRESCALER 1024 /* Prescaler used in debouncing */
#define OCNT_MAX F_CLK/PRESCALER*DEBOUNCE_MS/1000-1 /* Compare counter max value before interrupt is generated */

/*** Includes ***/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../HSMlib/HSMlib.h"

/*** Prototypes ***/
inline void debounced_read(void); /* Action on button read interrupt */
void setup_debounce_timer(void); /* Sets up the timer that periodically reads button pin */

#endif /* DEBOUNCE_H_ */