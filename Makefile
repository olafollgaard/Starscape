#----------------------------------------------------
# Based on http://github.com/turicas/arduinoMakefile

#----------------------------------------------------------------------------
# Sketch, board and path configuration (in general change only this section)

# Sketch filename (should be in the same directory of Makefile)
SKETCH_NAME = Stjernehimmel.ino

# MCU, frequency, Arduino hardware core folder, include path, and which .c and .cpp files to compile
MCU = atmega328p
F_CPU = 16000000
ARDUINO_CORE = /home/olaf/arduino-1.8.1/hardware/arduino/avr/cores/arduino
INCLUDE = -I. -I$(ARDUINO_CORE)
CORE_C_FILES = WInterrupts wiring_analog wiring wiring_digital wiring_pulse wiring_shift
CORE_CPP_FILES = abi CDC HardwareSerial HardwareSerial0 HardwareSerial1 HardwareSerial2 HardwareSerial3 \
		IPAddress main new PluggableUSB Print Stream Tone USBCore WMath WString
#MCU = attiny85
#F_CPU = 8000000
#ARDUINO_CORE = /home/olaf/Arduino/tiny/avr/cores/tiny
#INCLUDE = -I. -I$(ARDUINO_CORE)
#CORE_C_FILES = pins_arduino WInterrupts wiring_analog wiring wiring_digital wiring_pulse wiring_shift
#CORE_CPP_FILES = HardwareSerial main Print Tone WMath WString

# Reset and upload configuration
PORT = /dev/ttyACM0
BOARD_TYPE = arduino
BAUD_RATE = 115200

#---------------------------------
# Compiler and tool configuration

CC = /usr/bin/avr-gcc
CXX = /usr/bin/avr-g++
AVR_OBJCOPY = /usr/bin/avr-objcopy 
AVRDUDE = /usr/bin/avrdude

CPPFLAGS = $(INCLUDE)
C_COMMON_FLAGS =-g -Os -w -Wall -ffunction-sections -fdata-sections -fno-exceptions \
	-mmcu=$(MCU) -DF_CPU=$(F_CPU)
CFLAGS = $(C_COMMON_FLAGS) -std=gnu99
CXXFLAGS = $(C_COMMON_FLAGS)
AVRDUDE_CONF = /etc/avrdude.conf

#-----------------------------
# Core and intermediate files

tmp_dir = /tmp/build_arduino
sketch_cpp = $(tmp_dir)/$(SKETCH_NAME).cpp
sketch_elf = $(tmp_dir)/$(SKETCH_NAME).elf
sketch_hex = $(tmp_dir)/$(SKETCH_NAME).hex
sketch_o = $(tmp_dir)/$(SKETCH_NAME).o
core_o = $(CORE_C_FILES:%=$(tmp_dir)/%.o) $(CORE_CPP_FILES:%=$(tmp_dir)/%.o)

#-------------------
# Targets and rules

.PHONY: all build clean before_compile compile reset upload sketch_o core_o

all: clean compile upload

build: clean compile

clean:
		@echo '# *** Cleaning...'
		rm -rf "$(tmp_dir)"

before_compile:
		@echo '# *** Compiling...'

compile: before_compile $(tmp_dir) $(sketch_hex)
		@echo '# *** Compiled successfully! \o/'

reset:
		@echo '# *** Resetting...'
		stty --file $(PORT) hupcl
		sleep 0.1
		stty --file $(PORT) -hupcl

upload:
		@echo '# *** Uploading...'
		$(AVRDUDE) -q -V -p $(MCU) -C $(AVRDUDE_CONF) -c $(BOARD_TYPE) -b $(BAUD_RATE) -P $(PORT) \
			   -U flash:w:$(sketch_hex):i
		@echo '# *** Done - enjoy your sketch!'

$(tmp_dir):
		mkdir $@

# Convert elf to hex
$(sketch_hex): $(sketch_elf)
		$(AVR_OBJCOPY) -O ihex -R .eeprom $< $@

# Compile to elf
$(sketch_elf): $(sketch_o) $(core_o)
		$(CC) -mmcu=$(MCU) -lm -Wl,--gc-sections -Os -o $@ $^

# Generate sketch .cpp from .ino
$(sketch_cpp): $(SKETCH_NAME)
		@echo '# *** Generating .cpp from .ino...
		@echo '#include "WProgram.h"' > $@
		@cat $< >> $@

# Compile sketch .cpp file
$(tmp_dir)/%.o:: $(tmp_dir)/%.cpp
		$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

# Compile core .c files
$(tmp_dir)/%.o:: $(ARDUINO_CORE)/%.c
		$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

# Compile core .cpp files
$(tmp_dir)/%.o:: $(ARDUINO_CORE)/%.cpp
		$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@
