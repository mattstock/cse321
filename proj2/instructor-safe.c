#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/eeprom.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define LED_0 (1 << PB0)
#define LED_1 (1 << PB1)
#define LED_2 (1 << PB2)
#define KEY_0 (1 << PB3)
#define KEY_1 (1 << PB4)

typedef enum { S_START, S_CHECK, S_LOCKED, S_UNLOCKED } state_t;

typedef enum { BLUE=0, RED, YELLOW, GREEN } led_t;

typedef enum { PRESSED, UNPRESSED } key_t;

typedef struct {
  uint8_t port;
  uint8_t dir;
} pin_t;

// Index maps to led_t values
const pin_t ledmap[] = {
  { LED_1, LED_1|LED_2 },
  { LED_2, LED_1|LED_2 },
  { LED_1, LED_1|LED_0 },
  { LED_0, LED_1|LED_0 }
};

#define CODE_LEN 6

// Valid 1-6.  0 is stupid and 7 doesn't give
// a blanking interval.
#define HIGH_BRIGHTNESS 6
#define LOW_BRIGHTNESS 1

uint8_t leds = 0;

volatile uint32_t tick = 0;
volatile uint8_t brightness = HIGH_BRIGHTNESS;
volatile key_t sw0state = UNPRESSED;
volatile key_t sw1state = UNPRESSED;

void led(uint8_t pos, uint8_t val) {
  if (val)
    leds |= (1 << pos);
  else
    leds &= ~(1 << pos);
}

ISR(TIMER0_COMPA_vect) {
  static uint8_t sw0 = 0;
  static uint8_t sw1 = 0;
  
  tick = tick + 1;

  sw0 = (sw0 << 1) | !(PINB & KEY_0);
  if (sw0 == 0xff)
    sw0state = PRESSED;
  if (sw0 == 0x00)
    sw0state = UNPRESSED;

  sw1 = (sw1 << 1) | !(PINB & KEY_1);
  if (sw1 == 0xff)
    sw1state = PRESSED;
  if (sw1 == 0x00)
    sw1state = UNPRESSED;
  
  // Rotate through 0-3, but leave 8 ticks to work with for
  // brightness.
  uint8_t strobe = (tick & (0b11 << 3)) >> 3;
  
  if (((1 << strobe) & leds) &&
      ((tick & 0x7) < brightness)) {
    DDRB = ledmap[strobe].dir;
    PORTB = ledmap[strobe].port;
  } else {
    DDRB = 0;
    PORTB = 0;
  }
}

void sad_blink() {
  uint8_t blinks = 0;

  while (blinks < 3) {
    led(YELLOW, 1);
    _delay_ms(50);
    led(YELLOW, 0);
    _delay_ms(50);
    blinks++;
  }
}

uint8_t check_keys() {
  if (sw0state == PRESSED)
    return 1;
  if (sw1state == PRESSED)
    return 2;
  return 0;
}

uint8_t get_input() {
  uint8_t result = 0;
  uint8_t keystate = 0;

  // wait for the first button push
  while (keystate != CODE_LEN) {
    if (keystate == 0) {
      // wait forever for first button
      cli();
      tick = 0;
      sei();
      while (!check_keys()) {
	if (tick > 20000)
	  brightness = LOW_BRIGHTNESS;
      }
      brightness = HIGH_BRIGHTNESS;
    } else {
      cli();
      tick = 0;
      sei();
      while (!check_keys() && tick < 5000); // timeout supported
      if (tick >= 5000)
	return 0x80; // timeout fail
    }
    result = (result << 1) | (check_keys() == 2);
    led(BLUE, 1);
    _delay_ms(10);
    led(BLUE, 0);
    while (check_keys()); // wait for button to be released
    keystate++;
  }
  return result;
}

int main(void) {
  uint8_t val;
  uint8_t code;
  state_t state = S_START;

  // Initialization
  DDRB = 0x0;  // All inputs to start
  PORTB = 0x0; // No pullups
  TCCR0B = 0b001; // No prescale for timer
  TIMSK = (1 << OCIE0A); // Enable timer interrupts

  sei();

  // Main loop
  while (1) {
    switch (state) {
    case S_START:
      if (tick > 16)
	state = S_CHECK;
      break;
    case S_CHECK:
      if (check_keys()) {
	state = S_UNLOCKED;
	eeprom_update_word((uint16_t *)0, 0x0000);
      } else {
	// Pull code and lock state from eeprom
	uint16_t eval = eeprom_read_word((uint16_t *)0);
	if ((eval & 0xff) == 0x2e) {
	  code = (eval >> 8);
	  state = S_LOCKED;
	} else
	  state = S_UNLOCKED;
      }
      break;
    case S_LOCKED:
      led(GREEN, 0);
      led(YELLOW, 0);
      led(RED, 1);
      val = get_input();
      if (val == code) {
	state = S_UNLOCKED;
	eeprom_update_word((uint16_t *)0, 0x0000);
      } else
	sad_blink();
      break;
    case S_UNLOCKED:
      led(RED, 0);
      led(GREEN, 1);
      led(YELLOW, 1);
      val = get_input();
      if ((val & 0x80) == 0) {
	state = S_LOCKED;
	code = val;
	eeprom_update_word((uint16_t *)0, (code << 8) | 0x2e);
      } else
	sad_blink();
      break;
    }
  }
}
