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
  uint8_t r_divider;
  uint8_t g_divider;
  uint8_t b_divider;

  r_divider = 130;
  g_divider = 140;
  b_divider = 150;

  // initialize the direction of the B port to be outputs
  // on the 3 pins that have LEDs connected
  set_output(DDRB, RED);
  set_output(DDRB, GREEN);
  set_output(DDRB, BLUE);

  while (1) {

    for (i = 0; i < 255; i++) {

      if (i % r_divider == 0) {
        output_high(PORTB, RED);
      } else {
        output_low(PORTB, RED);
      }

      if (i % g_divider == 0) {
        output_high(PORTB, GREEN);
      } else {
        output_low(PORTB, GREEN);
      }

      if (i % b_divider == 0) {
        output_high(PORTB, BLUE);
      } else {
        output_low(PORTB, BLUE);
      }
    }

    r_divider++;
    g_divider++;
    b_divider++;

    if (r_divider > 150) {
      r_divider = 0;
    }
    if (g_divider > 150) {
      g_divider = 0;
    }
    if (b_divider > 150) {
      b_divider = 0;
    }
  }
}
