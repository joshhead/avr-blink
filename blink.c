// this is the header file that tells the compiler what pins and ports, etc.
// are available on this chip.
#include <avr/io.h>

#define NUM_LEDS 5
#define NUM_STATES 40

// Some macros that make the code more readable
#define output_low(port,pin) port &= ~(1<<pin)
#define output_high(port,pin) port |= (1<<pin)
#define set_input(portdir,pin) portdir &= ~(1<<pin)
#define set_output(portdir,pin) portdir |= (1<<pin)

int main(void) {
  uint8_t i;
  uint8_t which;
  uint8_t array_start;
  uint8_t divider;
  uint8_t leds[NUM_LEDS];
  uint8_t dividers[NUM_STATES];
  uint16_t counter;
  uint16_t counter_reset;

  leds[0] = PB3;
  leds[1] = PB4;
  leds[2] = PB2;
  leds[3] = PB1;
  leds[4] = PB0;

  for (i = 0; i < NUM_STATES; i++) {
    dividers[i] = 255;
  }

  dividers[0] = 1;
  dividers[1] = 2;
  dividers[2] = 4;
  dividers[3] = 8;
  dividers[4] = 16;
  dividers[5] = 32;
  dividers[6] = 64;
  dividers[7] = 128;

  // Set PORTB pins to output
  DDRB = 0xff;

  i = 0;
  counter = 0;
  array_start = 0;
  divider = 1;
  counter_reset = 300;

  while (1) {

    for (which = 0; which < NUM_LEDS; which++) {
      divider = dividers[(which + array_start) % NUM_STATES];
      if (divider < 255 && i % divider == 0) {
        output_high(PORTB, leds[which]);
      } else {
        output_low(PORTB, leds[which]);
      }
    }

    i++;
    counter++;
    if (counter == counter_reset) {
      counter = 0;

      array_start = (array_start + 1) % NUM_STATES;
    }
  }

}
