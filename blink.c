// this is the header file that tells the compiler what pins and ports, etc.
// are available on this chip.
#include <avr/io.h>

// define what pins the LEDs are connected to.
#define RED PB2
#define GREEN PB1
#define BLUE PB0

// Some macros that make the code more readable
#define output_low(port,pin) port &= ~(1<<pin)
#define output_high(port,pin) port |= (1<<pin)
#define set_input(portdir,pin) portdir &= ~(1<<pin)
#define set_output(portdir,pin) portdir |= (1<<pin)

// this is just a program that 'kills time' in a calibrated method
void delay_ms(uint8_t ms) {
  uint16_t delay_count = F_CPU / 17500;
  volatile uint16_t i;

  while (ms != 0) {
    for (i=0; i != delay_count; i++);
    ms--;
  }
}

int main(void) {
  uint8_t i;
  uint8_t which;
  uint8_t leds[3];
  uint8_t dividers[3];

  leds[0] = RED;
  leds[1] = GREEN;
  leds[2] = BLUE;

  dividers[0] = 130;
  dividers[1] = 140;
  dividers[2] = 150;

  // initialize the direction of the B port to be outputs
  // on the 3 pins that have LEDs connected
  for (which = 0; which < 3; which++) {
    set_output(DDRB, leds[which]);
  }

  while (1) {

    for (i = 0; i < 255; i++) {

      for (which = 0; which < 3; which++) {
        if (i % dividers[which] == 0 && dividers[which] < 80) {
          output_high(PORTB, leds[which]);
        } else {
          output_low(PORTB, leds[which]);
        }
      }

    }

    for (which = 0; which < 3; which++) {
      dividers[which]++;

      if (dividers[which] > 150) {
        dividers[which] = 0;
      }
    }
  }
}
