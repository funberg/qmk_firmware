#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_swedish.h"


enum custom_keycodes {
    KC__SCLN= SAFE_RANGE,
    KC__QUOT,
    KC__COMM,
    KC__DOT,
    KC__SLSH
};

enum planck_layers {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
    _LAYER4,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT(
RESET     ,KC_Q      ,KC_W      ,KC_E      ,KC_R      ,KC_T                                       ,KC_Y      ,KC_U      ,KC_I      ,KC_O      ,KC_P      ,KC_BSPC,
KC_TAB    ,KC_A      ,KC_S      ,KC_D      ,KC_F      ,KC_G                                       ,KC_H      ,KC_J      ,KC_K      ,KC_L      ,KC__SCLN  ,KC__QUOT,
KC_LSFT   ,KC_Z      ,KC_X      ,KC_C      ,KC_V      ,KC_B                                       ,KC_N      ,KC_M      ,KC__COMM  ,KC__DOT   ,KC__SLSH  ,KC_ENT ,
           KC_LCTL   ,KC_LALT   ,KC_LGUI   ,RAISE     ,KC_SPC    ,KC_BSPC              ,KC_BSPC   ,KC_SPC    ,KC_LEFT   ,KC_RIGHT  ,KC_DOWN   ,KC_UP
),
[_LOWER] = LAYOUT(
SE_TILD   ,KC_EXLM   ,SE_AT     ,KC_HASH   ,SE_DLR    ,KC_PERC                                    ,SE_CIRC   ,SE_AMPR   ,SE_ASTR   ,SE_LPRN   ,SE_RPRN   ,SE_MINS,
_______   ,_______   ,_______   ,SE_LBRC   ,SE_RBRC   ,_______                                    ,_______   ,SE_LPRN   ,SE_RPRN   ,SE_PIPE_MAC,_______  ,SE_UNDS,
KC_LSHIFT ,_______   ,_______   ,SE_LCBR_MAC,SE_RCBR_MAC,_______                                  ,_______   ,SE_PLUS   ,SE_EQL    ,SE_BSLS_MAC,_______  ,_______,
           _______   ,_______   ,_______   ,_______   ,MO(2)     ,_______              ,KC_NO     ,_______   ,_______   ,_______   ,_______   ,_______
),
[_RAISE] = LAYOUT(
SE_ACUT   ,KC_1      ,KC_2      ,KC_3      ,KC_4      ,KC_5                                       ,KC_6      ,KC_7      ,KC_8      ,KC_9      ,KC_0      ,SE_AA,
_______   ,KC_F1     ,KC_F2     ,KC_F3     ,KC_F4     ,KC_F5                                      ,_______   ,KC_4      ,KC_5      ,KC_6      ,SE_OSLH   ,SE_ADIA,
KC_LSHIFT ,KC_F6     ,KC_F7     ,KC_F8     ,KC_F9     ,KC_F10                                     ,_______   ,KC_1      ,KC_2      ,KC_3      ,_______   ,_______,
           _______   ,_______   ,_______   ,_______   ,_______   ,_______              ,KC_NO     ,KC_0      ,KC_DOT    ,_______   ,_______   ,_______
),

[_ADJUST] = LAYOUT(
RESET     ,_______   ,_______   ,_______   ,_______   ,_______                                    ,_______   ,KC_NO     ,RGB_SPD   ,_______   ,_______   ,KC_SYSTEM_SLEEP,
KC_ASTG   ,KC_ASDN   ,KC_ASUP   ,KC_ASRP   ,_______   ,_______                                    ,_______   ,RGB_TOG   ,RGB_VAD   ,RGB_VAI   ,_______   ,_______   ,
_______   ,_______   ,_______   ,KC_AUDIO_MUTE,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP                  ,KC_NO     ,RGB_MOD   ,RGB_HUD   ,RGB_HUI   ,_______   ,_______,
           _______   ,_______   ,_______   ,_______   ,_______   ,_______              ,KC_NO     ,_______   ,_______   ,_______   ,_______   ,_______
),
[_LAYER4] = LAYOUT(
_______   ,_______   ,_______   ,_______   ,_______   ,_______                                    ,_______   ,LCTL(LGUI(KC_LEFT)),KC_UP,LCTL(LGUI(KC_RIGHT)),_______,KC_DELETE,
_______   ,KC_LGUI   ,KC_LALT   ,KC_LSHIFT ,_______   ,_______                                    ,_______   ,KC_LEFT   ,KC_DOWN   ,KC_RIGHT  ,_______   ,_______,
KC_LSHIFT ,_______   ,_______   ,_______   ,_______   ,_______                                    ,_______   ,LGUI(KC_0),LGUI(LSFT(KC_Y)),LALT(LGUI(KC_0)),_______,_______,
           _______   ,_______   ,_______   ,_______   ,_______   ,_______              ,KC_NO     ,_______   ,_______   ,_______   ,_______   ,_______
),

// [_BASE] = LAYOUT(
// XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX                                    ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX,
// XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX                                    ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX,
// XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX                                    ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX,
//            XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX              ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX
// )
};

// Make BASE layer special characters behave like the US-layout one instead of swedish ones
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool shift_held = false;
    const bool primary_down = record->event.pressed && !shift_held, primary_up = !record->event.pressed && !shift_held;
    const bool shifted_down = record->event.pressed && shift_held, shifted_up = !record->event.pressed && shift_held;
    switch (keycode) {
        case KC_LSFT:
        case KC_RSFT:
            shift_held = record->event.pressed;
            return true;
        case KC__SCLN: {
            if (primary_down) {
                register_code(KC_LSFT);
                register_code(SE_COMM);
            } else if (primary_up) {
                unregister_code(KC_LSFT);
                unregister_code(SE_COMM);
            } else if (shifted_down) {
                register_code(KC_LSFT);
                register_code(SE_DOT);
            } else if (shifted_up) {
                unregister_code(SE_DOT);
            }
            return false;
        }
        case KC__COMM: {
            if (primary_down) {
                register_code(SE_COMM);
            } else if (primary_up) {
                unregister_code(SE_COMM);
            } else if (shifted_down) {
                unregister_code(KC_LSFT);
                register_code(SE_SECT);
            } else if (shifted_up) {
                register_code(KC_LSFT);
                unregister_code(SE_SECT);
            }
            return false;
        }
        case KC__DOT: {
            if (primary_down) {
                register_code(SE_DOT);
            } else if (primary_up) {
                unregister_code(SE_DOT);
            } else if (shifted_down) {
                register_code(SE_SECT);
            } else if (shifted_up) {
                unregister_code(SE_SECT);
            }
            return false;
        }
        case KC__SLSH: {
            if (primary_down) {
                register_code(KC_LSFT);
                register_code(SE_7);
            } else if (primary_up) {
                unregister_code(KC_LSFT);
                unregister_code(SE_7);
            } else if (shifted_down) {
                register_code(SE_PLUS);
            } else if (shifted_up) {
                unregister_code(SE_PLUS);
            }
            return false;
        }
        case KC__QUOT: {
            if (primary_down) {
                register_code(SE_QUOT);
            } else if (primary_up) {
                unregister_code(SE_QUOT);
            } else if (shifted_down) {
                register_code(SE_2);
            } else if (shifted_up) {
                unregister_code(SE_2);
            }
            return false;
        }
    }
    return true;
};
