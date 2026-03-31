# Optimize for speed, 16Mhz, target microcontroller
CFLAGS ?= -Os -DF_APU=16000000UL -mmcu=atmega328p
# Target microcontroller
LDFLAGS ?= -mmcu=atmega328p
# Path to port of microcontroller, using USB. On Linux run dmesg -w and plug in USB to find port
ARDUINO_USB ?= /dev/ttyACM0

# Build source code for board
all: main.hex

main.hex: main
	# Compiling to intel hex, removing .eeprom section, compile main to main.hex
	avr-objcopy -O ihex -R .eeprom main main.hex

main: main.o
	avr-gcc $(LDFLAGS) -o $@ $^

main.o: main.c
	avr-gcc $(CFLAGS) -c -o $@ $<

# Flash device from source
deploy: main.hex
	# Flash device using arduino programming process to our board at a designated port
	# using the standard seriel baud rate from our data source.
	avrdude -F -V -c arduino -p ATMEGA328p -P $(ARDUINO_USB) -b 115200 -U flash:w:main.hex

# Clean build artificats for recompilation
clean: FRC
	rm -f main.elf main.hex main.o main

FRC:
