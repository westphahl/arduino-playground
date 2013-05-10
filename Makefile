TARGET = blink
PORT = /dev/ttyACM0
MCU = atmega328p
F_CPU = 16000000UL
FORMAT = ihex
BAUDRATE = 115200
PROGRAMMER = arduino 

# Explanation of some GCC options:
# -Os (optimized for size)
# -c (compile but don't run the linker)
CC = avr-gcc
CFLAGS = -Os -Wall -DF_CPU=$(F_CPU) -mmcu=$(MCU) -c
LDFLAGS = -mmcu=$(MCU)

OBJCOPY = avr-objcopy -O $(FORMAT) -R .eeprom

AVRDUDE = avrdude
FFLAGS = -D -v -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUDRATE) -U flash:w:blink.hex:i

FUSEFLAGS = -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -n -v

SRCS = blink.c
OBJS = $(SRCS:.c=.o)

.PHONY: all flash info clean

all: $(TARGET).hex

.c.o:
	$(CC) $(CFLAGS) $< -o $@

$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) $< -o $@

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) $(TARGET).elf $(TARGET).hex

flash:
	$(AVRDUDE) $(FFLAGS)

info:
	$(AVRDUDE) $(FUSEFLAGS)

clean:
	rm -rf *.o *.elf *.hex
