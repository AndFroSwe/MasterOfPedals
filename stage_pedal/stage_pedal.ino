#define DEBOUNCE_TIME_MS 100

ISR(PCINT0_vect) {
  delay(DEBOUNCE_TIME_MS);
  digitalWrite(13, HIGH);
  start_timer();
}

ISR(TIMER1_COMPA_vect) {
  digitalWrite(13, LOW);
  TIMSK1 &= ~(1 << OCIE1A);  // stop timer
}


void init_pin_interrupts() {
  cli();  // disable interrupts
  PCICR |= (1 << PCIE0);  // enable interrupts on PC0
  PCMSK0 |= (1 << PCINT1); // enable interrupt on PCINT1 (pin 9)
  sei();  // enable interrupts
}

void init_timer() {
  /* setup 16 bit counter timer */
  cli();  // disable interrupts
  TCCR1A = 0x00;  // reset register
  TCCR1B = 0x00;  // reset register
  //TCNT1 = 0;    // reset counter
  OCR1A = 15624; // set counter top value
  TCCR1B |= (1 << WGM12); // set ctc mode
  TCCR1B |= (1 << CS12) | (1 << CS10); // set clock source
  //TIMSK1 |= (1 << OCIE1A);  // enable compare match on OCRA
  sei();  // enable interrupts
}

void start_timer() {
  TCNT1 = 0;  // reset counter
  TIMSK1 |= (1 << OCIE1A);  // start timer in CTC mode
}


void setup() {
  /* pin setups */
  pinMode(9, INPUT);
  pinMode(13, OUTPUT);
  init_timer();
  init_pin_interrupts();
}

void loop() {
}
