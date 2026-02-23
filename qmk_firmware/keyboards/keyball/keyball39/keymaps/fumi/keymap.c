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

#define JM_LSH1 LSFT_T(KC_HENK)
#define JM_RSH1 RSFT_T(KC_BSPC)

static bool shift_left_pressed  = false;
static bool shift_right_pressed = false;
static uint16_t shift_osm_timer = 0;  // タイマー保持
static uint16_t layer5_timer    = 0;     // レイヤー5自動戻しタイマー

// カスタムキーコードの定義（既存の定義と被らない名前で）
enum custom_keycodes {
    MY_COMM = SAFE_RANGE, // Shiftなしで「,」、Shiftありで「:」
    MY_DOT,              // Shiftなしで「.」、Shiftありで「;」
    MY_MINS              // Shiftなしで「-」、Shiftありで「_」
};

//----------------------------------
// キー処理
//----------------------------------
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t layer = get_highest_layer(layer_state);

    bool is_layer_0 = (layer == 0);
    bool is_layer_0_or_1 = (layer <= 1); // 0か1か
    uint8_t mods = get_mods() | get_oneshot_mods();
    bool shift = mods & MOD_MASK_SHIFT;

    switch (keycode) {

        // カスタムキー処理 + One-Shot Shift 解除
        case MY_COMM:
            if (is_layer_0 && shift) tap_code16(S(KC_QUOT));
            else tap_code(KC_COMM);
            if (record->event.pressed && (get_oneshot_mods() & MOD_MASK_SHIFT))
                clear_oneshot_mods();
            goto check_shift_input;

        case MY_DOT:
            if (is_layer_0 && shift) tap_code16(S(KC_SCLN));
            else tap_code(KC_DOT);
            if (record->event.pressed && (get_oneshot_mods() & MOD_MASK_SHIFT))
                clear_oneshot_mods();
            goto check_shift_input;

        case MY_MINS:
            if (is_layer_0 && shift) tap_code16(S(KC_INT1));
            else tap_code(KC_MINUS);
            if (record->event.pressed && (get_oneshot_mods() & MOD_MASK_SHIFT))
                clear_oneshot_mods();
            goto check_shift_input;

        // Shift 押下状態更新
        case KC_LSFT: shift_left_pressed  = record->event.pressed; break;
        case KC_RSFT: shift_right_pressed = record->event.pressed; break;

        // One-Shot Shift 解除対象（MY_* は既に処理済み）
        case KC_ENT: case KC_SPC:
        case JM_SCLN: case JM_COLN: case JM_LPRN: case JM_RPRN:
        case JM_LABK: case JM_RABK: case JM_LCBR: case JM_RCBR:
            if (record->event.pressed && (get_oneshot_mods() & MOD_MASK_SHIFT))
                clear_oneshot_mods();
            break;
    }

check_shift_input:
    // 左右Shift同時押しで自前 One-Shot Shift
    if (shift_left_pressed && shift_right_pressed &&
        (keycode == KC_LSFT || keycode == KC_RSFT) &&
        record->event.pressed &&
        is_layer_0_or_1) {

        register_mods(MOD_MASK_SHIFT);
        unregister_mods(MOD_MASK_SHIFT);
        shift_osm_timer = timer_read();
    }

    // Shift以外でタイマーリセット
    if (record->event.pressed && keycode != KC_LSFT && keycode != KC_RSFT) {
        shift_osm_timer = timer_read();
    }

    // レイヤー5タイマーリセット
    if (record->event.pressed && get_highest_layer(layer_state) == 5) {
        layer5_timer = timer_read();
    }

    return true;
}


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     ,LT(2,KC_T),                           LT(2,KC_Y), KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , KC_S     , KC_D     , KC_F     ,LT(1,KC_G),                           LT(1,KC_H), KC_J     ,LT(3,KC_K), KC_L     , MY_MINS  ,
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , MY_COMM  , MY_DOT   , JM_SLSH  ,
    _______  , KC_LGUI  , KC_LALT  , KC_MHEN  , KC_SPC   , JM_LSH1  ,      JM_LSH1  , KC_ENT   , _______  , _______  , _______  , JM_EQL
  ),

  [1] = LAYOUT_universal(
    JM_EXLM  , _______  , JM_YEN   , _______  , JM_TILD  ,                            JM_ASTR  , KC_7     , KC_8     , KC_9     , JM_PLUS,
    JM_AMPR  , JM_HASH  , JM_DLR   , _______  , _______  ,                            _______  , KC_4     , KC_5     , KC_6     , MY_MINS  ,
    JM_AT    , JM_PERC  , JM_CIRC  , JM_PIPE  , JM_GRV   ,                            _______  , KC_1     , KC_2     , KC_3     , JM_SLSH  ,
    MO(5)    , _______  , _______  , _______  , _______  , _______  ,      KC_DEL   ,  KC_0    , _______  , _______  , _______  , JM_EQL
  ),

  [2] = LAYOUT_universal(
    _______  , _______  , JM_LABK  , JM_LBRC  , _______  ,                            _______  , JM_RBRC  , JM_RABK  , _______  , _______  ,
    _______  , _______  , JM_LCBR  , JM_LPRN  , _______  ,                            _______  , JM_RPRN  , JM_RCBR  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    S(KC_LEFT),S(KC_UP) ,S(KC_DOWN),S(KC_RGHT),  KC_DEL  ,                            _______  , _______  , _______  , _______  , _______  ,
    KC_LEFT  , KC_UP    , KC_DOWN  , KC_RGHT  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    KC_HOME  , KC_PGUP  , KC_PGDN  , KC_END   , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      KC_BSPC  , KC_ENT   , _______  , _______  , _______  , _______
  ),

  [4] = LAYOUT_universal(
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                            KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   ,
    KC_ESC   , _______  , _______  , _______  , _______  ,                            KC_PSCR  , KC_PAUS  , KC_INS   , KC_F10   , KC_F12   ,
    KC_HOME  , KC_PGUP  , KC_PGDN  , KC_END   , _______  ,                            KC_SYRQ  , _______  , KC_SCRL  , _______  , KC_DEL   ,
    MO(0)    , KC_LGUI  , KC_LALT  , KC_LCTL  , KC_SPC   , KC_LSFT  ,      KC_RSFT  , KC_RCTL  , _______  , _______  , _______  , KC_RALT
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


//----------------------------------
// スキャン処理
//----------------------------------
void matrix_scan_user(void) {
    // One-Shot Shift 自動解除（3秒）
    if (get_oneshot_mods() & MOD_MASK_SHIFT) {
        if (timer_elapsed(shift_osm_timer) > 3000) {
            clear_oneshot_mods();
        }
    }

    // レイヤー5 自動解除（10秒）
    if (get_highest_layer(layer_state) == 5) {
        if (timer_elapsed(layer5_timer) > 10000) {
            layer_move(0);
        }
    }
}

//----------------------------------
// レイヤー状態更新
//----------------------------------
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);

    // レイヤー0/1以外で One-Shot Shift 解除
    if (layer != 0 && layer != 1) {
        if (get_oneshot_mods() & MOD_MASK_SHIFT) {
            clear_oneshot_mods();
        }
    }

    // スクロールモード切替
    keyball_set_scroll_mode(layer == 4);

    return state;
}

#ifdef COMBO_ENABLE

// <
//const uint16_t PROGMEM my_tr[] = {KC_T, KC_R, COMBO_END};

//combo_t key_combos[] = {
//    COMBO(my_tr, JM_LABK),
//};
#endif

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
