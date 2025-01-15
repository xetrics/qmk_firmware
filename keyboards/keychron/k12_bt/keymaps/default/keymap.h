/*
Copyright 2024 mintyleaf
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
#include QMK_KEYBOARD_H

/* Extended keycodes for controlling Bluetooth */
enum BT_keycodes {
    KC_BTPROF0 = SAFE_RANGE, // Set bluetooth profile 0
    KC_BTPROF1,              // Set bluetooth profile 1
    KC_BTPROF2,              // Set bluetooth profile 2
    KC_BTPAIR,               // Start pairing mode
    KC_BTTOGL,               // Toggle bluetooth mode
    KC_BTRST,                // Reset bluetooth module
    KC_BTBATT,               // Show battery level
    K2_SAFE_RANGE
};

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
    WIN_BASE = 0,
    WIN_FN1  = 1,
    MAC_BASE = 2,
    MAC_FN1  = 3,
    FN2      = 4,
};

#define KC_TASK LGUI(KC_TAB) // Task viewer
#define KC_FLXP LGUI(KC_E)   // Windows file explorer

#define KC_MSSN LGUI(KC_F3)        // Mission Control
#define KC_FIND LALT(LGUI(KC_SPC)) // Finder
#define KC_MSNP LSFT(LGUI(KC_4))   // Mac snip tool
