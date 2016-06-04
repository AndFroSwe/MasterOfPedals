#define DEBOUNCE_TIME_MS 100
volatile int int_pin = 0;

ISR(PCINT0_vect) {
  /* interrupt fired on digital pin 8-13 */
  PCMSK0 = 0x00;  // disable pin interrupts
  if (PINB & (1 << PB1)) {
    int_pin = 9;
  } else if (PINB & (1 << PB2)) {
    int_pin = 10;
  } else {
    int_pin = 100;
  }
  Serial.print("Interrupt on: ");
  Serial.println(int_pin);
  int_pin = 0;  // pin sense reset
  start_timer();  // timer to protect from too frequent switches
}

ISR(TIMER1_COMPA_vect) {
  /* timer interrupt */
  enable_pin_interrupts();
  TIMSK1 &= ~(1 << OCIE1A);  // stop timer
}

void init_pin_interrupts() {
  cli();  // disable interrupts
  PCICR |= (1 << PCIE0);  // enable interrupts on PC0
  sei();  // enable interrupts
}

void enable_pin_interrupts() {
  PCMSK0 |= (1 << PCINT1) | (1 << PCINT2); // enable interrupts
}

void init_timer() {
  /* setup 16 bit counter timer */
  cli();  // disable interrupts
  TCCR1A = 0x00;  // reset register
  TCCR1B = 0x00;  // reset register
  //TCNT1 = 0;    // reset counter
  OCR1A = 15624 * 3; // set counter top value
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
  pinMode(10, INPUT);
  init_timer();
  init_pin_interrupts();
  enable_pin_interrupts();
  Serial.begin(9600);
}

void loop() {
}
