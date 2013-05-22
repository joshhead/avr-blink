// this is the header file that tells the compiler what pins and ports, etc.
// are available on this chip.
#include <avr/io.h>

// define what pins the LEDs are connected to.
#define LED PB0

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
  DDRB = 0xff;
  PORTB = 0xaa;

  while (1) {
    delay_ms(200);
    PORTB ^= 0xff;
  }
}
