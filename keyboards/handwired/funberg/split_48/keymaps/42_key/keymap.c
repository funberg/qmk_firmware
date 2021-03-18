#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_swedish.h"

#define RETRO_TAPPING

// Tap Dance keycodes
enum td_keycodes {
    ALT_LP // Our example key: `LALT` when held, `(` when tapped. Add additional keycodes for each tapdance.
};

// Define a type containing as many tapdance states as you need
typedef enum {
    INACTIVE = 0,
    SINGLE_TAP,
    SINGLE_HOLD,
    DOUBLE_TAP
} td_state_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Declare your tapdance functions:

// Function associated with all tap dances
uint8_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
    [ALT_LP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset)
};

enum custom_keycodes {
    KC__SCLN= SAFE_RANGE,
    KC__QUOT,
    KC__COMM,
    KC__DOT,
    KC__SLSH,
    KC__DEBUG
};

enum planck_layers {
    _BASE,
    _CODE,
    _FNUM,
    _ADJUST,
    _NAV,
};

#define CODE MO(_CODE)
#define FNUM MO(_FNUM)
#define ADJUST MO(_ADJUST)
#define ADJUST0 LT(_ADJUST, KC_0)
#define NAV MO(_NAV)
#define SPC_CMD MT(MOD_LGUI, KC_SPC)
#define NAV_SPC LT(_NAV, KC_SPC)

#define CTL_TAB C(KC_F9)
#define MUTE KC_AUDIO_MUTE
#define VOL_UP KC_AUDIO_VOL_UP
#define VOL_DOWN KC_AUDIO_VOL_DOWN

#define BASE_ON DF(_BASE)
#define NAV_ON  DF(_NAV)
#define CODE_ON DF(_CODE)
#define FNUM_ON DF(_FNUM)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_42(
KC_ESC       ,KC_Q         ,KC_W         ,KC_E         ,KC_R         ,KC_T                       ,KC_Y         ,KC_U         ,KC_I         ,KC_O         ,KC_P         ,KC_BSPC      ,
KC_TAB       ,KC_A         ,KC_S         ,KC_D         ,KC_F         ,KC_G                       ,KC_H         ,KC_J         ,KC_K         ,KC_L         ,KC__SCLN     ,KC__QUOT     ,
KC_LSFT      ,KC_Z         ,KC_X         ,KC_C         ,KC_V         ,KC_B                       ,KC_N         ,KC_M         ,KC__COMM     ,KC__DOT      ,KC__SLSH     ,KC_ENT       ,
                                          NAV          ,FNUM         ,SPC_CMD                    ,TD(ALT_LP)   ,CODE         ,KC_LCTL
),
[_FNUM] = LAYOUT_42(
SE_GRV       ,KC_1         ,KC_2         ,KC_3         ,KC_4         ,KC_5                       ,KC_6         ,KC_7         ,KC_8         ,KC_9         ,KC_0         ,SE_AA        ,
_______      ,KC_F1        ,KC_F2        ,KC_F3        ,KC_F4        ,KC_F5                      ,XXXXXXX      ,KC_4         ,KC_5         ,KC_6         ,SE_OSLH      ,SE_ADIA      ,
_______      ,KC_F6        ,KC_F7        ,KC_F8        ,KC_F9        ,KC_F10                     ,XXXXXXX      ,KC_1         ,KC_2         ,KC_3         ,XXXXXXX      ,_______      ,
                                          _______      ,_______      ,_______                    ,_______      ,ADJUST0      ,KC_DOT
),
[_CODE] = LAYOUT_42(
SE_TILD      ,KC_EXLM      ,SE_AT        ,KC_HASH      ,SE_DLR       ,KC_PERC                    ,SE_CIRC      ,SE_AMPR      ,SE_ASTR      ,SE_LPRN      ,SE_RPRN      ,SE_MINS      ,
_______      ,XXXXXXX      ,XXXXXXX      ,SE_LCBR_MAC  ,SE_RCBR_MAC  ,XXXXXXX                    ,XXXXXXX      ,SE_LPRN      ,SE_RPRN      ,SE_PIPE_MAC  ,_______      ,SE_UNDS      ,
_______      ,XXXXXXX      ,XXXXXXX      ,SE_LBRC      ,SE_RBRC      ,XXXXXXX                    ,XXXXXXX      ,SE_PLUS      ,SE_EQL       ,SE_BSLS_MAC  ,_______      ,_______      ,
                                          _______      ,ADJUST       ,_______                    ,_______      ,_______      ,_______
),
[_ADJUST] = LAYOUT_42(
RESET        ,XXXXXXX      ,XXXXXXX      ,XXXXXXX      ,XXXXXXX      ,XXXXXXX                    ,XXXXXXX      ,XXXXXXX      ,XXXXXXX      ,XXXXXXX      ,XXXXXXX      ,_______      ,
KC__DEBUG    ,XXXXXXX      ,XXXXXXX      ,XXXXXXX      ,XXXXXXX      ,XXXXXXX                    ,XXXXXXX      ,XXXXXXX      ,XXXXXXX      ,XXXXXXX      ,XXXXXXX      ,_______      ,
_______      ,XXXXXXX      ,XXXXXXX      ,MUTE         ,VOL_DOWN     ,VOL_UP                     ,XXXXXXX      ,XXXXXXX      ,XXXXXXX      ,XXXXXXX      ,XXXXXXX      ,_______      ,
                                          _______      ,_______      ,_______                    ,_______      ,_______      ,_______
),
[_NAV] = LAYOUT_42(
BASE_ON      ,NAV_ON       ,XXXXXXX      ,XXXXXXX      ,XXXXXXX      ,XXXXXXX                    ,XXXXXXX      ,C(G(KC_LEFT)),KC_UP        ,C(G(KC_RGHT)),XXXXXXX      ,KC_DELETE    ,
_______      ,KC_LSFT      ,KC_LCTL      ,KC_LALT      ,KC_LGUI      ,XXXXXXX                    ,XXXXXXX      ,KC_LEFT      ,KC_DOWN      ,KC_RIGHT     ,XXXXXXX      ,_______      ,
_______      ,XXXXXXX      ,XXXXXXX      ,XXXXXXX      ,XXXXXXX      ,CTL_TAB                    ,XXXXXXX      ,G(KC_0)      ,G(S(KC_Y))   ,A(G(KC_0))   ,XXXXXXX      ,_______      ,
                                          _______      ,_______      ,_______                    ,_______      ,_______      ,_______
),
};

// Determine the current tap dance state
uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) return DOUBLE_TAP;
    else return INACTIVE;
}

// Functions that control what our tap dance key does
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            tap_code(KC_QUOT);
            break;
        case SINGLE_HOLD:
            layer_on(_NAV);
            break;
        case DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(_NAV)) {
                // If already set, then switch it off
                layer_off(_NAV);
            } else {
                // If not already set, then switch the layer on
                layer_on(_NAV);
            }
            break;
        default:
            break;
    }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (td_state == SINGLE_HOLD) {
        layer_off(_NAV);
    }
    td_state = INACTIVE;
}

// Make BASE layer special characters behave like the US-layout one instead of swedish ones
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool shift_held = false, _debugging = false;
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
        case KC__DEBUG: {
            if(record->event.pressed) {
                _debugging = !_debugging;
                debug_enable = _debugging;
                debug_matrix = _debugging;
            }
            return false;
        }
    }
    return true;
};

layer_state_t layer_state_set_user(layer_state_t state) {
    int layer = get_highest_layer(state);
    uprintf("layer:%d\n", layer);
    return state;
}