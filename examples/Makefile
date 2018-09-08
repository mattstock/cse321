CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-mmcu=attiny85 -Os
PROGFLAGS=-B100 -p t85 -c $(ISP) -e
#ISP=avrisp2
#ISP=jtag3isp
ISP=usbtiny

all: registers registers.hex

clean:
	rm -f *.o *.hex registers

%.hex: %
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

fuse:
	avrdude -B100 -p t88 -c $(ISP) -U lfuse:w:0xEE:m

install: registers.hex
	avrdude $(PROGFLAGS) -U flash:w:registers.hex
