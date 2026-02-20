/*
Copyright 2022 @Yowkees
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

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , KC_S     , KC_D     ,LT(1,KC_F), KC_G     ,                            KC_H     ,LT(1,KC_J),LT(3,KC_K), KC_L     , KC_MINS  ,
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  ,
    _______  , KC_LGUI  , KC_LALT  ,LCTL_T(KC_INT4),KC_SPC,LSFT_T(KC_INT5),KC_RSFT  , KC_ENT   , _______  , _______  , _______  , LT(2,KC_ESC)
  ),

  // !          @          =+        *          ~                                     [{         ]}         '"
  // &          #          $                    `~                                                                                ;:
  //            %          ^         |          \|                                    (          )          <          >
  [1] = LAYOUT_universal(
    S(KC_1)  , _______  , KC_EQUAL , S(KC_8)  ,S(KC_GRV) ,                            KC_LBRC  , KC_RBRC  , KC_QUOT  , _______  , _______  ,
    S(KC_7)  , S(KC_3)  , S(KC_4)  , _______  , KC_GRV   ,                            _______  , _______  , _______  , _______  , KC_SCLN  ,
    _______  , S(KC_5)  , S(KC_6)  ,S(KC_BSLS), KC_BSLS  ,                            S(KC_9)  , S(KC_0)  ,S(KC_COMM),S(KC_DOT) , _______ ,
    _______  , KC_LGUI  , KC_LALT  , KC_LCTL  , KC_TAB   , KC_LSFT  ,      KC_RSFT  , KC_BSPC  , _______  , _______  , _______  , KC_ESC
  ),

  [2] = LAYOUT_universal(
  S(KC_EQUAL), KC_7     , KC_8     , KC_9     , KC_EQUAL ,                            _______  , _______  , _______  , _______  , _______  ,
    KC_MINS  , KC_4     , KC_5     , KC_6     , S(KC_3)  ,                            _______  , _______  , _______  , _______  , _______  ,
    S(KC_8)  , KC_1     , KC_2     , KC_3     , KC_COMM  ,                            _______  , _______  , _______  , _______  , _______  ,
    KC_SLSH  , KC_0     , KC_DOT   , KC_DEL   , KC_SPC    , KC_TAB  ,      KC_BSPC  , KC_ENT   , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    _______  , KC_UP    , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , C(KC_X)  , C(KC_C)  , C(KC_V)  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , KC_SPC   , _______  ,      KC_RSFT  , KC_ENT   , _______  , _______  , _______  , _______
  ),

  [4] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [5] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [6] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [7] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                            MS_WHLU  , MS_WHLL  , MS_WHLR  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            MS_WHLD  , MS_BTN1  , MS_BTN2  , KC_PGUP  , _______  ,
    _______  , C(KC_X)  , C(KC_C)  , C(KC_V)  , _______  ,                            _______  , MS_BTN3  , MS_BTN4  , KC_PGDN  , _______  ,
    _______  , _______  , _______  ,LCTL_T(KC_INT4),KC_SPC,LSFT_T(KC_INT5),_______  , _______  , _______  , _______  , _______  , _______
  ),
};
// clang-format on

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);
}
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    int h_layer = get_highest_layer(state);
    // Auto enable scroll mode when the highest layer is 3 or 6
    keyball_set_scroll_mode(h_layer == 3 || h_layer == 6);

    #ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    switch(get_highest_layer(remove_auto_mouse_layer(state, true))) {
        case 1:
        case 2:
            state = remove_auto_mouse_layer(state, false);
            set_auto_mouse_enable(false);
            break;
        default:
            set_auto_mouse_enable(true);
            break;
    }
    #endif

    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
