#define INTERRUPT_HOLD_TIME_MS 500

volatile int send_message = 0;  // if 1, message is sent over serial
volatile int int_pin = 0;     // pin that was changed

/* pin interrupts */
void init_pin_interrupts() {
  cli();  // disable interrupts
  PCICR |= (1 << PCIE0);  // enable interrupts on PC0
  sei();  // enable interrupts
}

void enable_pin_interrupts() {
  PCMSK0 |= (1 << PCINT1) | (1 << PCINT2); // enable interrupts
}

ISR(PCINT0_vect) {
  /* interrupt fired on digital pin 8-13 change */
  int pinn = PINB;
  PCMSK0 = 0x00;  // disable pin interrupts
  /* sense which pin was triggered */
  if (pinn & (1 << PB1)) {
    int_pin = 9;
    send_message = 1;
  } else if (pinn & (1 << PB2)) {
    int_pin = 10;
    send_message = 1;
  }
  start_timer();  // timer to protect from too frequent switches
}
/* timer interrupts */
void init_timer() {
  /* setup 16 bit counter timer */
  cli();  // disable interrupts
  TCCR1A = 0x00;  // reset register
  TCCR1B = 0x00;  // reset register
  //TCNT1 = 0;    // reset counter
  OCR1A = 16 * INTERRUPT_HOLD_TIME_MS; // set time before interrupt
  TCCR1B |= (1 << WGM12); // set ctc mode
  TCCR1B |= (1 << CS12) | (1 << CS10); // set clock source
  //TIMSK1 |= (1 << OCIE1A);  // enable compare match on OCRA
  sei();  // enable interrupts
}

void start_timer() {
  /* start a new timer */
  TCNT1 = 0;  // reset counter
  TIMSK1 |= (1 << OCIE1A);  // start timer in CTC mode
}

ISR(TIMER1_COMPA_vect) {
  /* timer interrupt starts pin interrupts again*/
  enable_pin_interrupts();
  TIMSK1 &= ~(1 << OCIE1A);  // stop timer
}

/* main scripts */
void setup() {
  /* pin setups */
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  /* initiate functions */
  init_timer();
  init_pin_interrupts();
  enable_pin_interrupts();
  Serial.begin(9600);
}

void loop() {
  /* constantly checks to see if a pin has been triggered and
   *  sends a message if it has.
   */
  if (send_message) {
    /* send information via serial */
    Serial.print("Interrupt on: ");
    Serial.println(int_pin);
    int_pin = 0;  // reset read pin variable
    send_message = 0; // reset send message command
  }
  //delay(100);
}
