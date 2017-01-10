/*
 * encoder.h
 *
 * Created: 1/5/2017 2:23:23 PM
 *  Author: Andreas Fröderberg
 */ 


#ifndef ENCODER_H_
#define ENCODER_H_

/*** Defines ***/
/* Encoder pins */
#define ENC_REGISTER DDRD /* Direction register of encoder pulses */
#define ENC_PORT PORTD /* Port register of encoder */
#define ENC_A_PIN PD2 /* Encoder A pulse */
#define ENC_B_PIN PD3 /* Encoder B pulse */
/* LED pins */
#define ENC_LED_REGISTER DDRB /* Direction register for encoder leds */
#define ENC_LED_PORT PORTB /* Port register for encoder leds */
#define ENC_GREEN PB6 /* Encoder green led pin */
#define ENC_RED PB7	/* Encoder red led pin */

/*** Includes ***/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../HSMlib/HSMlib.h"

/*** Prototypes ***/
void enc_setup_interrupts(void);
void enc_setup_pins(void);
void enc_green_on(void);
void enc_green_off(void);
void enc_red_on(void);
void enc_red_off(void);

#endif /* ENCODER_H_ */