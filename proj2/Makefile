CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-mmcu=attiny85 -Os
PROGFLAGS=-B100 -p t85 -c $(ISP) -e
ISP=usbtiny

all: safe safe.hex testhw.hex

clean:
	rm -f *.o safe safe.hex

%.hex: %
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

fuse:
	avrdude -B100 -p t85 -c $(ISP) -U lfuse:w:0x62:m

install-%: %.hex
	avrdude $(PROGFLAGS) -U flash:w:$<
