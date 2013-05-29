SOURCES=blink.c

MCU=attiny85
F_CPU=8000000
AVRDUDE_PROGRAMMER=usbtiny

CFLAGS=-I. -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -Wall -Wstrict-prototypes -std=gnu99 -DF_CPU=$(F_CPU) -mmcu=$(MCU) 

HEX=$(SOURCES:.c=.hex)

all: $(SOURCES) $(HEX)

install: $(HEX)
	avrdude -c $(AVRDUDE_PROGRAMMER) -p $(MCU) -U flash:w:$(HEX)

%.hex: %.elf
	avr-objcopy -O ihex -R .eeprom $(basename $@).elf $@

%.elf: %.o
	avr-gcc $(CFLAGS) -Wa,-adhlns=$(basename $@).o $(basename $@).o --output $@

%.o: %.c
	avr-gcc $(CFLAGS) -c $(basename $@).c -o $@

clean:
	rm -f *.elf *.o

.PHONY: all install clean
