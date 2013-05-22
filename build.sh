#!/bin/sh
avr-gcc -c -I. -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -Wall -Wstrict-prototypes -DF_CPU=16000000 -Wa,-adhlns=blink.lst -mmcu=attiny85 -std=gnu99 blink.c -o blink.o

avr-gcc -I. -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -Wall -Wstrict-prototypes -DF_CPU=16000000 -Wa,-adhlns=blink.o -mmcu=attiny85 -std=gnu99 blink.o --output blink.elf -Wl,-Map=%.map,--cref

avr-objcopy -O ihex -R .eeprom blink.elf blink.hex
