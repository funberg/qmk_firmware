#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_swedish.h"

#define RETRO_TAPPING

enum tap_dance_codes {
    C_CPY,
    V_PST,
    X_CUUT,
    Z_UNDO,
    S_SAV,
    SPC_NAV
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
KC_TAB       ,KC_A         ,TD(S_SAV)    ,KC_D         ,KC_F         ,KC_G                       ,KC_H         ,KC_J         ,KC_K         ,KC_L         ,KC__SCLN     ,KC__QUOT     ,
KC_LSFT      ,TD(Z_UNDO)   ,TD(X_CUUT)   ,TD(C_CPY)    ,TD(V_PST)    ,KC_B                       ,KC_N         ,KC_M         ,KC__COMM     ,KC__DOT      ,KC__SLSH     ,KC_ENT       ,
                                          NAV          ,FNUM         ,SPC_CMD                    ,TD(SPC_NAV)  ,CODE         ,KC_LCTL
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


// Helper tap dance function
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

uint8_t my_tap_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}

// Tap dance macro for tap = KC, hold = CMD+KC
typedef struct {
uint16_t keycode;
uint8_t step;
} my_tap_hold_t;

#    define MY_TAP_HOLD(kc) \
        { .fn = {my_tap_hold_on_each_tap, my_tap_hold_finished, my_tap_hold_reset}, \
        .user_data = (void *)&((my_tap_hold_t){kc, 0}) }

void my_tap_hold_on_each_tap(qk_tap_dance_state_t *state, void *user_data) {
    my_tap_hold_t *user = (my_tap_hold_t *)user_data;
    if(state->count == 3) {
        tap_code16(user->keycode);
        tap_code16(user->keycode);
        tap_code16(user->keycode);
    }
    if(state->count > 3) {
        tap_code16(user->keycode);
    }
}

void my_tap_hold_finished(qk_tap_dance_state_t *state, void *user_data) {
    my_tap_hold_t *user = (my_tap_hold_t *)user_data;
    user->step = my_tap_step(state);
    switch (user->step) {
        case SINGLE_TAP: register_code16(user->keycode); break;
        case SINGLE_HOLD: tap_code16(G(user->keycode)); break;
        case DOUBLE_TAP:
        case DOUBLE_SINGLE_TAP: tap_code16(user->keycode); register_code16(user->keycode);
    }
}

void my_tap_hold_reset(qk_tap_dance_state_t *state, void *user_data) {
    my_tap_hold_t *user = (my_tap_hold_t *)user_data;
    switch (user->step) {
        case SINGLE_TAP: unregister_code16(user->keycode); break;
        case DOUBLE_TAP:
        case DOUBLE_SINGLE_TAP: unregister_code16(user->keycode);
    }
    user->step = 0;
}

// Tap dance macro for tap = KC, hold = momentary layer switch, double hold = toggle layer
typedef struct {
uint16_t keycode;
uint8_t layer;
int8_t step;
} my_tap_layer_toggle_t;

#    define MY_TAP_LAYER_TOGGLE(kc, layer) \
        { .fn = {my_tap_layer_toggle_on_each_tap, my_tap_layer_toggle_finished, my_tap_layer_toggle_reset}, \
        .user_data = (void *)&((my_tap_layer_toggle_t){kc, layer, 0}) }

void my_tap_layer_toggle_on_each_tap(qk_tap_dance_state_t *state, void *user_data) {
    my_tap_layer_toggle_t *user = (my_tap_layer_toggle_t *)user_data;
    if(state->count == 3) {
        tap_code16(user->keycode);
        tap_code16(user->keycode);
        tap_code16(user->keycode);
    }
    if(state->count > 3) {
        tap_code16(user->keycode);
    }
}

void my_tap_layer_toggle_finished(qk_tap_dance_state_t *state, void *user_data) {
    my_tap_layer_toggle_t *user = (my_tap_layer_toggle_t *)user_data;
    user->step = my_tap_step(state);

    switch (user->step) {
        case SINGLE_TAP: register_code16(user->keycode); break;
        case SINGLE_HOLD:
        case DOUBLE_HOLD: layer_invert(user->layer); break;
        case DOUBLE_SINGLE_TAP: tap_code16(user->keycode); register_code16(user->keycode);
    }
}

void my_tap_layer_toggle_reset(qk_tap_dance_state_t *state, void *user_data) {
    my_tap_layer_toggle_t *user = (my_tap_layer_toggle_t *)user_data;
    switch (user->step) {
        case SINGLE_TAP: unregister_code16(user->keycode); break;
        case SINGLE_HOLD: layer_invert(user->layer); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(user->keycode); break;
    }
    user->step = 0;
}


qk_tap_dance_action_t tap_dance_actions[] = {
    [C_CPY] = MY_TAP_HOLD(KC_C),
    [V_PST] = MY_TAP_HOLD(KC_V),
    [X_CUUT] = MY_TAP_HOLD(KC_X),
    [Z_UNDO] = MY_TAP_HOLD(KC_Z),
    [S_SAV] = MY_TAP_HOLD(KC_S),
    [SPC_NAV] = MY_TAP_LAYER_TOGGLE(KC_SPC, _NAV)
};

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
