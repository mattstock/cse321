CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-mmcu=attiny85 -Os -I/usr/local/include -std=gnu99
PROGFLAGS=-B100 -p t85 -c $(ISP) -e
#ISP=avrisp2
ISP=jtag3isp
#ISP=usbtiny

programs = registers direct direct2 direct3 direct4 sw-led simple timers timers2 sw-led2 polling pinchg pwm pwm2 debounce power simulator myrtos

all: ${programs}

clean:
	rm -f *.hex *~ *.o ${programs} *.S

%.S: %.c
	$(CC) $(CFLAGS) -o $@ -S $<
%.hex: %
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

install-%: %.hex
	avrdude $(PROGFLAGS) -U flash:w:$<
