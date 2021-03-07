#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_swedish.h"

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _LAYER4,
  _LAYER5,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
KC_ESC ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,               KC_Y   ,KC_U   ,KC_I    ,KC_O    ,KC_P   ,KC_BSPC,
KC_TAB ,KC_A   ,KC_S   ,KC_D   ,LT(4,KC_F),KC_G,               KC_H   ,KC_J   ,KC_K    ,KC_L    ,SE_SCLN,SE_APOS,
KC_LSFT,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,               KC_N   ,KC_M   ,KC_COMMA,KC_DOT  ,SE_SLSH,KC_ENT ,
KC_LCTL,KC_LALT,KC_LGUI,RAISE  ,KC_SPC ,KC_BSPC,               KC_BSPC,KC_SPC ,KC_LEFT ,KC_RIGHT,KC_DOWN,KC_UP  )
};
