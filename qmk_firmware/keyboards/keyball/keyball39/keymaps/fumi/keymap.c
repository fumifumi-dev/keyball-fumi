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

#define KC_MHEN KC_INT4
#define KC_HENK KC_INT5

#define JM_MINS KC_MINUS          // - us:-
#define JM_CIRC KC_EQUAL          // ^ us:=
#define JM_AT   KC_LBRC           // @ us:Shift+2
#define JM_LBRC KC_RBRC           // [ us:]
#define JM_SCLN KC_SCLN           // ; us:;
#define JM_COLN KC_QUOT           // : us:Shift+;
#define JM_RBRC KC_BSLS           // ] us:\;
#define JM_COMM KC_COMM           // , us:,
#define JM_DOT  KC_DOT            // . us:.
#define JM_SLSH KC_SLSH           // / us:/
#define JM_BSLS KC_INT1           // \ us:none (Ro-key)
#define JM_YEN  KC_INT3           // ¥ us:none (Yen-key)
#define JM_EXLM S(KC_1)           // ! us:Shift+1
#define JM_DQUO S(KC_2)           // " us:Shift+'
#define JM_HASH S(KC_3)           // # us:Shift+3
#define JM_DLR  S(KC_4)           // $ us:Shift+4
#define JM_PERC S(KC_5)           // % us:Shift+5
#define JM_AMPR S(KC_6)           // & us:Shift+7
#define JM_QUOT S(KC_7)           // ' us:'
#define JM_LPRN S(KC_8)           // ( us:Shift+9
#define JM_RPRN S(KC_9)           // ) us:Shift+0
#define JM_EQL  S(KC_MINUS)       // = us:Shift+-
#define JM_TILD S(KC_EQUAL)       // ~ us:Shift+`
#define JM_PIPE S(KC_INT3)        // | us:Shift+\;
#define JM_GRV  S(KC_LBRC)        // ` us:`
#define JM_LCBR S(KC_RBRC)        // { us:Shift+[
#define JM_RCBR S(KC_BSLS)        // } us:Shift+]
#define JM_PLUS S(KC_SCLN)        // + us:Shift+=
#define JM_ASTR S(KC_QUOT)        // * us:Shift+8
#define JM_LABK S(KC_COMM)        // < us:Shift+,
#define JM_RABK S(KC_DOT)         // > us:Shift+.
#define JM_QUES S(KC_SLSH)        // ? us:Shift+/
#define JM_UNDS S(KC_INT1)        // _ us:Shift+-

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , KC_S     ,LT(3,KC_D),LT(1,KC_F), KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , KC_MINUS  ,
   LT(4,KC_Z), KC_X     , KC_C     , KC_V     ,LT(2,KC_B),                           LT(2,KC_N), KC_M     , KC_COMM  , KC_DOT   ,LT(4,JM_SLSH),
    KC_CAPS  , KC_LGUI  , KC_LALT  ,LCTL_T(KC_MHEN),KC_SPC,LSFT_T(KC_HENK),KC_RSFT  , KC_ENT   , _______  , _______  , _______  , JM_EQL
  ),

  // !                     ¥                    ~                                     [          ]          (          )          +
  // &          #          $                    `                                     *                     "          '          -
  // @          %          ^         |          \                                     {          }          <          >          /
  [1] = LAYOUT_universal(
    JM_EXLM  , _______  , JM_YEN   , _______  , JM_TILD  ,                            JM_LBRC  , JM_RBRC  , JM_LPRN  , JM_RPRN  , JM_PLUS  ,
    JM_AMPR  , JM_HASH  , JM_DLR   , _______  , JM_GRV   ,                            JM_ASTR  , _______  , JM_DQUO  , JM_QUOT  , KC_MINUS  ,
    JM_AT    , JM_PERC  , JM_CIRC  , JM_PIPE  , JM_BSLS  ,                            JM_LCBR  , JM_RCBR  , JM_LABK  , JM_RABK  , JM_SLSH  ,
    _______  , KC_LGUI  , KC_LALT  , KC_LCTL  , KC_TAB   , KC_LSFT  ,      KC_DEL   , KC_BSPC  , _______  , _______  , _______  , KC_ESC
  ),

  [2] = LAYOUT_universal(
    KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                            KC_6     , KC_7     , KC_8     , KC_9     , JM_PLUS,
    _______  , _______  , _______  , _______  , _______  ,                            JM_ASTR  , KC_4     , KC_5     , KC_6     , KC_MINUS  ,
    _______  , JM_PERC  , _______  , _______  , _______  ,                            _______  , KC_1     , KC_2     , KC_3     , JM_SLSH  ,
    _______  , KC_LGUI  , KC_LALT  , KC_LCTL  , KC_0     , KC_LSFT  ,       JM_DOT  ,  KC_ENT  , _______  , _______  , _______  , JM_EQL
  ),

  [3] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , KC_UP    , KC_BSPC  , KC_DEL   ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , KC_LGUI  , KC_LALT  , KC_LCTL  , KC_SPC   , KC_LSFT  ,      KC_RSFT  , KC_ENT   , _______  , _______  , _______  , _______
  ),

  [4] = LAYOUT_universal(
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                            KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , KC_F10   , KC_F12   ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , KC_LGUI  , KC_LALT  , KC_LCTL  , KC_SPC   , KC_LSFT  ,      KC_RSFT  , KC_RCTL  , _______  , _______  , _______  , _______
  ),
/*
  [7] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),
*/
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
//    // Auto enable scroll mode when the highest layer is 3
//    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef COMBO_ENABLE
// combo setting
const uint16_t PROGMEM my_jk[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM my_kl[] = {KC_K, KC_L, COMBO_END};

combo_t key_combos[] = {
    COMBO(my_jk, KC_BTN1),
    COMBO(my_kl, KC_BTN2),
    NULL
};
#endif

#ifdef KEY_OVERRIDE_ENABLE
//key_override_on
const key_override_t coln_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_COMM, KC_QUOT, 1, MOD_MASK_SHIFT);
const key_override_t scln_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_DOT, KC_SCLN, 1, MOD_MASK_SHIFT);
const key_override_t unds_key_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_MINUS, KC_INT1, 1);

const key_override_t **key_overrides = (const key_override_t *[]) {
    &coln_key_override,
    &scln_key_override,
    &unds_key_override,
    NULL // 終端
};
#endif

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
