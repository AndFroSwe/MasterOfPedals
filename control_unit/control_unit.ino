#define PED1 8
#define PED2 9
#define PED3 10

int all_pedals[3] = {PED1, PED2, PED3};
int mode_1 = 0b111;
int mode_2 = 0b101;
int mode_3 = 0b100;
int all_modes[] = {mode_1, mode_2, mode_3};

int received;

void setup()
{
  // setup all pedal pins
  for (int i = 0; i < sizeof(all_pedals)/sizeof(int); i++)
  {
    pinMode(all_pedals[i], OUTPUT);
  }

  Serial.begin(9600);  // start serial
  Serial.println(sizeof(all_pedals)/sizeof(int));
  Serial.println(sizeof(all_modes)/sizeof(int));
  

}

void loop()
{
  // check serial for messages
  if (Serial.available() > 0)
  {
    received = Serial.read();
    int received_as_int = received - '0'; // convert ascii to corresponding int
    if ((received_as_int >= 0) && (received_as_int < sizeof(all_pedals)/sizeof(int))) { // protect against non-valid inputs
      Serial.println(received_as_int);
      enable_pedals(received_as_int);
    }
  }
}

void kill_all() {
  for (int i = 0; i < sizeof(all_pedals)/sizeof(int); i++)
  {
    digitalWrite(all_pedals[i], LOW);
  }
}

void enable_pedals(int command) {
  /* starts all pedals according to mode */
  kill_all(); // start with killing all pedals
  // loop through mode variable and see which pedals to start
  int mode = all_modes[command];
  for (int i = 0; i < sizeof(all_pedals)/sizeof(int); i++)
  {
    if ((mode >> i) & 0x01) {
      digitalWrite(all_pedals[i], HIGH);
    }
  }
}

