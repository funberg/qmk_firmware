/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
Copyright 2017 Erin Call <hello@erincall.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Steady Hands
#define PRODUCT         Split48
#define DESCRIPTION     An ortholinear, split planck keyboard with a bendy thumb row.

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

// Expander needs to be first in the setup, no support for bit swizzling yet
// Since MCU is in left half, use the LAYOUT_ macro to flip back the keys to the correct side
#define COL_EXPANDED { true, true, true, true, true, true, false, false, false, false, false, false }
#define MATRIX_ONBOARD_COL_PINS { 0, 0, 0, 0, 0, 0 , F4, F5, F6, F7, B1, B3}
#define MATRIX_ONBOARD_ROW_PINS { D4, C6, D7, E6 }


#define EXPANDER_COL_REGISTER GPIOB
#define EXPANDER_ROW_REGISTER GPIOA
#define MATRIX_EXPANDER_COL_PINS {0, 1, 2, 3, 4, 5}
#define MATRIX_EXPANDER_ROW_PINS {0, 1, 2, 3}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */
#define BACKLIGHT_LEVELS 0

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define RETRO_TAPPING

// IO expander config
#define I2C_ADDR        0x20
#define I2C_ADDR_WRITE  ( (I2C_ADDR<<1) | I2C_WRITE )
#define I2C_ADDR_READ   ( (I2C_ADDR<<1) | I2C_READ  )
#define IODIRA          0x00            // i/o direction register
#define IODIRB          0x01
#define GPPUA           0x0C            // GPIO pull-up resistor register
#define GPPUB           0x0D
#define GPIOA           0x12            // general purpose i/o port register (write modifies OLAT)
#define GPIOB           0x13
