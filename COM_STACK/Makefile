# === CONFIGURATION ===
MCU = atmega32
F_CPU = 8000000UL
PROGRAMMER = usbasp
BAUD = 19200

# === TOOLS ===
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# === FLAGS ===
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os \
         -I./MCAL/SPI \
         -I./MCAL/UART \
         -I./MCAL/PORT \
         -I./MCAL/TIMER \
         -I./Comm \
         -I./App

OBJ2HEX_FLAGS = -O ihex -R .eeprom

# Allow overriding -B value via CLI (defaults to safe -B 20)
AVRDUDE_FLAGS ?= -c $(PROGRAMMER) -p $(MCU) -B 20

# === FILES ===
SRC = $(wildcard App/*.c) \
      $(wildcard Comm/*.c) \
      $(wildcard MCAL/SPI/*.c) \
      $(wildcard MCAL/UART/*.c) \
      $(wildcard MCAL/PORT/*.c) \
      $(wildcard MCAL/TIMER/*.c)
      
OBJ = $(SRC:.c=.o)
ELF = app.elf
HEX = app.hex

# === RULES ===
all: $(HEX)

$(ELF): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(ELF)

$(HEX): $(ELF)
	$(OBJCOPY) $(OBJ2HEX_FLAGS) $(ELF) $(HEX)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

flash: $(HEX)
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U flash:w:$(HEX)

flash-verbose: $(HEX)
	$(AVRDUDE) -v -v -v $(AVRDUDE_FLAGS) -U flash:w:$(HEX)

clean:
	rm -f $(OBJ) $(ELF) $(HEX)
