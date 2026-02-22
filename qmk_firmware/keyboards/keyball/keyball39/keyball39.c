/*
Copyright 2021 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
*/

#include QMK_KEYBOARD_H

#include "lib/keyball/keyball.h"

//////////////////////////////////////////////////////////////////////////////

// clang-format off
matrix_row_t matrix_mask[MATRIX_ROWS] = {
    0b00011111,
    0b00011111,
    0b00011111,
    0b00111111,
    0b00011111,
    0b00011111,
    0b00011111,
    0b00111111,
};
// clang-format on

// combo setting
#ifdef COMBO_ENABLE

const uint16_t PROGMEM my_jk[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM my_kl[] = {KC_K, KC_L, COMBO_END};

combo_t key_combos[] = {
    COMBO(my_jk, KC_BTN1),
    COMBO(my_kl, KC_BTN2),
};
#endif

#ifdef KEY_OVERRIDE_ENABLE
const key_override_t coln_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM , JM_COLN);
const key_override_t scln_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT  , JM_SCLN);
const key_override_t unds_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_MINUS, JM_UNDS);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
	&coln_key_override,
	&scln_key_override,
	&unds_key_override,
};

#endif

void keyball_on_adjust_layout(keyball_adjust_t v) {
#ifdef RGBLIGHT_ENABLE
    // adjust RGBLIGHT's clipping and effect ranges
    uint8_t lednum_this = keyball.this_have_ball ? 22 : 24;
    uint8_t lednum_that = !keyball.that_enable ? 0 : keyball.that_have_ball ? 22 : 24;
    rgblight_set_clipping_range(is_keyboard_left() ? 0 : lednum_that, lednum_this);
    rgblight_set_effect_range(0, lednum_this + lednum_that);
#endif
}
