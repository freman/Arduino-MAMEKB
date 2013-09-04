/*
 Keyboard Encoder for MAME

*/

#define xDEBUG
#define xNOKB

void p(char *fmt, ... ){
        char tmp[128]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(tmp, 128, fmt, args);
        va_end (args);
        Serial.print(tmp);
}

#ifdef DEBUG
  #define DPRINT(x)  Serial.println (x)
  #define DPRINTBIN(x) Serial.println (x, BIN);
  #define DPRINTF(fmt, ...) p(fmt, __VA_ARGS__);
  #define DSLEEP(x) delay(x);
#else
  #define DPRINT(x)
  #define DPRINTBIN(x)
  #define DPRINTF(fmt, ...)
  #define DSLEEP(x)
#endif

#define BUTTONS     20
#define THRESHOLD   100

// Build a keymap and statemap
char keymap[BUTTONS] = {
  '/',                    // D0 - Player 2 Start Button
  '.',                    // D1 - Player 2 Orange Button
  'm',                    // D2 - Player 2 Blue Button
  KEY_ESC,                // D3 - Player 2 Coin Button
  ',',                    // D4 - Player 2 Yellow Button
  'n',                    // D5 - Player 2 Red Button
  'j',                    // D6 - Player 2 Left
  'c',                    // D7 - Player 1 Start Button
  KEY_LEFT_ALT,           // D8 - Player 1 Blue Button
  'x',                    // D9 - Player 1 Orange Button
  'i',                    // D10 - Player 2 Up
  'k',                    // D11 - Player 2 Down
  'v',                    // D12 - Player 1 Coin Button
  'l',                    // D13 - Player 2 Right
  'd',                    // A0 - Player 1 Right
  'z',                    // A1 - Player 1 Yellow Button
  'w',                    // A2 - Player 1 Up
  KEY_LEFT_CTRL,          // A3 - Player 1 Red Button
  'a',                    // A4 - Player 1 Left
  's'                     // A5 - Player 1 Down
};

int keystate[BUTTONS] = {
  LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW
};

// Debounce the buttons
char debounce[BUTTONS];

// Only used for working out where you plugged what wires.
char *iomap[BUTTONS] = {
  "D0", "D1", "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "D10", "D11", "D12", "D13", "A0", "A1", "A2", "A3", "A4", "A5"
};


void setup() {
  // All the pins are input
  DDRD = 0x00;
  DDRC = 0x00;
  DDRE = 0x00;
  DDRF = 0x00;
  DDRB = 0x00;
  PORTD = 0x00;
  PORTF = 0x00;
  PORTE = 0x00;
  PORTC = 0x00;
  PORTB = 0x00;

  // Initialize the debounce array
  for (byte i = 0; i < BUTTONS; i++) {
    debounce[i] == 0;
  }

#ifndef NOKB
  // initialize control over the keyboard:
  Keyboard.begin();
#endif
}

void set_key(int key, int state) {
  state = state > 0;
  if (state == HIGH && keystate[key] == LOW) {
    if (debounce[key] < THRESHOLD) {
      debounce[key] += 1;
    }
    else if (debounce[key] >= THRESHOLD) {
      DPRINTF("KEY %d (%s) GOT PRESSED\r\n", key, iomap[key]);
#ifndef NOKB
      Keyboard.press(keymap[key]);
#endif
      keystate[key] = state;
    }
  }
  else if (state == LOW && keystate[key] == HIGH) {
    if (debounce[key] > 0) {
      debounce[key] -= 1;
    }
    else if (debounce[key] == 0) {
      DPRINTF("KEY %d (%s) GOT RELEASED\r\n", key, iomap[key]);
#ifndef NOKB
      Keyboard.release(keymap[key]);
#endif
      keystate[key] = state;
    }
  }
  else if (state == keystate[key]) {
    debounce[key] = state ? THRESHOLD : 0;
  }
}

void loop() {
  uint8_t b = PINB;
  uint8_t c = PINC;
  uint8_t d = PIND;
  uint8_t e = PINE;
  uint8_t f = PINF;

  set_key(0, d & 0x04);
  set_key(1, d & 0x08);
  set_key(2, d & 0x02);
  set_key(3, d & 0x01);
  set_key(4, d & 0x10);
  set_key(5, c & 0x40);
  set_key(6, d & 0x80);
  set_key(7, e & 0x40);

  set_key(8, b & 0x10);
  set_key(9, b & 0x20);
  set_key(10, b & 0x40);
  set_key(11, b & 0x80);
  set_key(12, d & 0x40);
  set_key(13, c & 0x80);

  set_key(14, f & 0x80);
  set_key(15, f & 0x40);
  set_key(16, f & 0x20);
  set_key(17, f & 0x10);
  set_key(18, f & 0x02);
  set_key(19, f & 0x01);

#ifdef DEBUG
  if (e != e_prev) {
    DPRINTBIN(e);
  }
#endif
}


