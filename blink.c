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
  DDRB = 0xff; // All PORTB pins to output

  while (1) {
    // start with all the LEDs off
    output_low(PORTB, RED);
    output_low(PORTB, GREEN);
    output_low(PORTB, BLUE);

    // turn on the red light for 200ms
    output_high(PORTB, RED);
    delay_ms(100);

    // turn on red & green -> yellow for 100ms
    output_high(PORTB, GREEN);
    delay_ms(100);

    // now turn off red to make just green
    output_low(PORTB, RED);
    delay_ms(100);

    // now turn on green & blue to make greenish-blue
    output_high(PORTB, BLUE);
    delay_ms(100);

    // turn off green -> blue
    output_low(PORTB, GREEN);
    delay_ms(100);

    // turn on red again to make purple
    output_high(PORTB, RED);
    delay_ms(100);
  }
}
