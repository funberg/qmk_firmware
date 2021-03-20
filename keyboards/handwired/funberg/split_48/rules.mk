# MCU name
MCU = atmega32u4

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = caterina

# Build Options
#   comment out to disable the options.
#
EXTRAKEY_ENABLE         = yes # Audio control and System control(+450)
CONSOLE_ENABLE          = yes  # Console for debug(+8000)
CUSTOM_MATRIX           = yes # Custom matrix file for the Dactyl
UNICODE_ENABLE          = yes # Unicode
TAP_DANCE_ENABLE        = yes

# project specific files
SRC = twimaster.c \
	  matrix.c
