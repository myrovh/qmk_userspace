/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LY_NAV,
    LY_NUM,
    LY_SYM,
    LY_FUN,
    LY_MOUSE
};

/** \brief Automatically enable sniping-mode on the pointer layer. */
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LY_MOUSE

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define PT_Z LT(LY_MOUSE, KC_Z)
#define PT_SLSH LT(LY_MOUSE, KC_SLSH)
#define NAV LT(LY_NAV, KC_SPC)
#define NUM LT(LY_NUM, KC_BSPC)
#define SYM LT(LY_SYM, KC_ENT)
#define FUN LT(LY_FUN, KC_DEL)
#define XXX KC_NO

#define U_RDO C(KC_Y)
#define U_PST C(KC_V)
#define U_CPY C(KC_C)
#define U_CUT C(KC_X)
#define U_UND C(KC_Z)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
XXX, XXX         , XXX         , XXX         , XXX         , XXX   , XXX    , XXX         , XXX         , XXX           , XXX            , XXX
XXX, KC_Q        , KC_W        , KC_E        , KC_R        , KC_T  , KC_Y   , KC_U        , KC_I        , KC_O          , KC_P           , XXX
XXX, LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), KC_G  , KC_H   , LSFT_T(KC_J), LCTL_T(KC_K), LALT_T(KC_L)  , LGUI_T(KC_QUOT), XXX
XXX, PT_Z        , ALGR_T(KC_X), KC_C        , KC_V        , KC_B  , KC_N   , KC_M        , KC_COMM     , ALGR_T(KC_DOT), PT_SLSH        , XXX
                                 XXX         , KC_ESC      , NAV   , NUM    , FUN         ,
                                               XXX         , KC_TAB, SYM
  ),

  [LY_NAV] = LAYOUT(
XXX, XXX         , XXX         , XXX         , XXX         , XXX   , XXX    , XXX         , XXX         , XXX           , XXX            , XXX
XXX, XXX         , XXX         , XXX         , XXX         , XXX   , U_RDO  , U_PST       , U_CPY       , U_CUT         , U_UND          , XXX
XXX, KC_LGUI     , KC_LALT     , KC_LCTL     , KC_LSFT     , XXX   , KC_LEFT, KC_DOWN     , KC_UP       , KC_RGHT       , CW_TOGG        , XXX
XXX, XXX         , KC_ALGR     , XXX         , XXX         , XXX   , KC_HOME, KC_PGDN     , KC_PGUP     , KC_END        , KC_INS         , XXX
                                 XXX         , XXX         , XXX   , KC_BSPC, KC_DEL      ,
                                               XXX         , XXX   , KC_ENT
  ),

  [LY_NUM] = LAYOUT(
XXX, XXX         , XXX         , XXX         , XXX         , XXX   , XXX    , XXX         , XXX         , XXX           , XXX            , XXX
XXX, KC_LBRC     , KC_7        , KC_8        , KC_9        ,KC_RBRC, XXX    , XXX         , XXX         , XXX           , XXX            , XXX
XXX, KC_SCLN     , KC_4        , KC_5        , KC_6        , KC_EQL, XXX    , KC_LSFT     , KC_LCTL     , KC_LALT       , KC_LGUI        , XXX
XXX, KC_GRV      , KC_1        , KC_2        , KC_3        ,KC_BSLS, XXX    , XXX         , XXX         , KC_ALGR       , XXX            , XXX
                                 XXX         , KC_DOT      , KC_0  , XXX    , XXX         ,
                                               XXX         ,KC_MINS, XXX
  ),

  [LY_SYM] = LAYOUT(
XXX, XXX         , XXX         , XXX         , XXX         , XXX   , XXX    , XXX         , XXX         , XXX           , XXX            , XXX
XXX, KC_LCBR     , KC_AMPR     , KC_ASTR     , KC_LPRN     ,KC_RCBR, XXX    , XXX         , XXX         , XXX           , XXX            , XXX
XXX, KC_COLN     , KC_DLR      , KC_PERC     , KC_CIRC     ,KC_PLUS, XXX    , KC_LSFT     , KC_LCTL     , KC_LALT       , KC_LGUI        , XXX
XXX, KC_TILD     , KC_EXLM     , KC_AT       , KC_HASH     ,KC_PIPE, XXX    , XXX         , XXX         , KC_ALGR       , XXX            , XXX
                                 XXX         , KC_LPRN     ,KC_RPRN, XXX    , XXX         ,
                                               XXX         ,KC_UNDS, XXX
  ),

  [LY_FUN] = LAYOUT(
XXX, XXX         , XXX         , XXX         , XXX         , XXX   , XXX    , XXX         , XXX         , XXX           , XXX            , XXX
XXX, KC_F12      , KC_F7       , KC_F8       , KC_F9       ,KC_PSCR, XXX    , XXX         , XXX         , XXX           , XXX            , XXX
XXX, KC_F11      , KC_F4       , KC_F5       , KC_F6       ,KC_SCRL, XXX    , KC_LSFT     , KC_LCTL     , KC_LALT       , KC_LGUI        , XXX
XXX, KC_F10      , KC_F1       , KC_F2       , KC_F3       ,KC_PAUS, XXX    , XXX         , XXX         , KC_ALGR       , XXX            , XXX
                                 XXX         , KC_APP      , KC_SPC, XXX    , XXX         ,
                                               XXX         ,KC_TAB , XXX
  ),

  [LY_MOUSE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       QK_BOOT,  EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,  EE_CLR,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD,    S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, DRGSCRL, SNIPING, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, SNIPING, DRGSCRL, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_BTN2, KC_BTN1, KC_BTN3,    KC_BTN3, KC_BTN1,
                                           DRGSCRL, KC_BTN2,    KC_BTN2
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LY_MOUSE);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LY_MOUSE);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif
