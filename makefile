ARDUINO_PATH = /opt/arduino-1.8.7
BOARD = teensy:avr:teensyLC
USB_PREF = custom_usb=teensyLC_xinput
OPTIONS = --board $(BOARD) --pref $(USB_PREF)

all:
	$(ARDUINO_PATH)/arduino --verify $(OPTIONS) .

install:
	$(ARDUINO_PATH)/arduino --upload $(OPTIONS) .
