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

void do_pwm(uint8_t r_duty, uint8_t g_duty, uint8_t b_duty, uint8_t rate) {
  uint8_t i;

  while (rate != 0) {
    output_high(PORTB, RED);
    output_high(PORTB, GREEN);
    output_high(PORTB, BLUE);

    for (i=0; i < 255; i++) {
      if (i == r_duty)
        output_low(PORTB, RED);
      if (i == g_duty)
        output_low(PORTB, GREEN);
      if (i == b_duty)
        output_low(PORTB, BLUE);
    }
    rate--;
  }
}

int main(void) {
  uint8_t i;

  // initialize the direction of the B port to be outputs
  // on the 3 pins that have LEDs connected
  set_output(DDRB, RED);
  set_output(DDRB, GREEN);
  set_output(DDRB, BLUE);

  // slowly turn red on
  for (i=0; i<255; i++)
    do_pwm(i, 0, 0, 5);

  while (1) {
    // slowly turn green on too
    for (i=0; i<255; i++)
      do_pwm(255, i, 0, 15);

    // now turn red off
    for (i=255; i>0; i--)
      do_pwm(i, 255, 0, 15);

    // slowly turn on blue
    for (i=0; i<255; i++)
      do_pwm(0, 255, i, 15);

    // turn off green
    for (i=255; i>0; i--)
      do_pwm(0, i, 255, 15);

    // turn on red
    for (i=0; i<255; i++)
      do_pwm(i, 0, 255, 15);

    // turn off blue
    for (i=255; i>0; i--)
      do_pwm(255, 0, i, 15);
  }
}
