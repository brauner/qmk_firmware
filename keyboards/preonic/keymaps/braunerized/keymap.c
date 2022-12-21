/* Copyright 2015-2021 Jack Humbert
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
#include "muse.h"

enum preonic_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _MOUSE,
  _MANAGE,
  _COMPOSITOR
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  MOUSE,
  MANAGE,
  COMPOSITOR,
  BACKLIT
};

#define MOD_TAP_LSFT_ESC LSFT_T(KC_ESC)
#define MOD_TAP_LSFT_ENT LSFT_T(KC_ENT)

#define LT_COPY_Y    LT(_QWERTY, KC_Y)
#define LT_CUT_X     LT(_QWERTY, KC_X)
#define LT_PASTE_P   LT(_QWERTY, KC_P)
#define LT_AE_A      LT(_QWERTY, KC_A)
#define LT_OE_O      LT(_QWERTY, KC_O)
#define LT_UE_U      LT(_QWERTY, KC_U)
#define LT_SZ_S      LT(_QWERTY, KC_S)
#define LT_E_ACGRV   LT(_QWERTY, KC_E)
#define LT_LOWER_SPC LT(_LOWER,  KC_SPC)

#define LM_COMP_LALT      LM(_COMPOSITOR, MOD_LALT)
#define LM_COMP_LALT_LSFT LM(_COMPOSITOR, MOD_LALT | MOD_LSFT)

#define KO_LAYER_MASK_EXCEPT(layer) ((~0) & ~(1 << layer))

enum combos {
  COMBO_LPRN_RPRN, /* (|) */
  COMBO_LBRC_RBRC, /* [|] */
  COMBO_LCBR_RCBR, /* {|} */
  COMBO_MAX,
};

uint16_t COMBO_LEN = COMBO_MAX;

const uint16_t PROGMEM combo_lprn_rprn[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM combo_lbrc_rbrc[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM combo_lcbr_rcbr[] = {KC_C, KC_V, COMBO_END};

combo_t key_combos[COMBO_MAX] = {
  [COMBO_LPRN_RPRN] = COMBO_ACTION(combo_lprn_rprn),
  [COMBO_LBRC_RBRC] = COMBO_ACTION(combo_lbrc_rbrc),
  [COMBO_LCBR_RCBR] = COMBO_ACTION(combo_lcbr_rcbr),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case COMBO_LPRN_RPRN:
      if (pressed) {
        tap_code16(KC_LPRN);
        tap_code16(KC_RPRN);
        tap_code16(KC_LEFT);
      }
      break;
    case COMBO_LBRC_RBRC:
      if (pressed) {
        tap_code16(KC_LBRC);
        tap_code16(KC_RBRC);
        tap_code16(KC_LEFT);
      }
      break;
    case COMBO_LCBR_RCBR:
      if (pressed) {
        tap_code16(KC_LCBR);
        tap_code16(KC_RCBR);
        tap_code16(KC_LEFT);
      }
      break;
  }
}

const key_override_t nop_shift_quote = ko_make_with_layers(MOD_MASK_SHIFT, KC_QUOT, KC_NO, KO_LAYER_MASK_EXCEPT(_COMPOSITOR)); /* " */
const key_override_t nop_shift_dot   = ko_make_with_layers(MOD_MASK_SHIFT, KC_DOT, KC_NO, KO_LAYER_MASK_EXCEPT(_COMPOSITOR));  /* < */
const key_override_t nop_shift_comma = ko_make_with_layers(MOD_MASK_SHIFT, KC_COMM, KC_NO, KO_LAYER_MASK_EXCEPT(_COMPOSITOR)); /* > */
const key_override_t nop_shift_slash = ko_make_with_layers(MOD_MASK_SHIFT, KC_SLSH, KC_NO, KO_LAYER_MASK_EXCEPT(_COMPOSITOR)); /* ? */
const key_override_t nop_shift_one   = ko_make_with_layers(MOD_MASK_SHIFT, KC_1, KC_NO, KO_LAYER_MASK_EXCEPT(_COMPOSITOR));    /* ! */
const key_override_t nop_shift_two   = ko_make_with_layers(MOD_MASK_SHIFT, KC_2, KC_NO, KO_LAYER_MASK_EXCEPT(_COMPOSITOR));    /* override @ */
const key_override_t nop_shift_three = ko_make_with_layers(MOD_MASK_SHIFT, KC_3, KC_NO, KO_LAYER_MASK_EXCEPT(_COMPOSITOR));    /* override # */
const key_override_t nop_shift_four  = ko_make_with_layers(MOD_MASK_SHIFT, KC_4, KC_NO, KO_LAYER_MASK_EXCEPT(_COMPOSITOR));    /* override $ */
const key_override_t nop_shift_five  = ko_make_with_layers(MOD_MASK_SHIFT, KC_5, KC_NO, KO_LAYER_MASK_EXCEPT(_COMPOSITOR));    /* override % */
const key_override_t nop_shift_six   = ko_make_with_layers(MOD_MASK_SHIFT, KC_6, KC_NO, KO_LAYER_MASK_EXCEPT(_COMPOSITOR));    /* override ^ */
const key_override_t nop_shift_seven = ko_make_with_layers(MOD_MASK_SHIFT, KC_7, KC_NO, KO_LAYER_MASK_EXCEPT(_COMPOSITOR));    /* override & */
const key_override_t nop_shift_eight = ko_make_with_layers(MOD_MASK_SHIFT, KC_8, KC_NO, KO_LAYER_MASK_EXCEPT(_COMPOSITOR));    /* override * */
const key_override_t nop_shift_nine  = ko_make_with_layers(MOD_MASK_SHIFT, KC_9, KC_NO, KO_LAYER_MASK_EXCEPT(_COMPOSITOR));    /* override ( */
const key_override_t nop_shift_zero  = ko_make_with_layers(MOD_MASK_SHIFT, KC_0, KC_NO, KO_LAYER_MASK_EXCEPT(_COMPOSITOR));    /* override ) */

const key_override_t **key_overrides = (const key_override_t *[]){
  &nop_shift_quote,
  &nop_shift_dot,
  &nop_shift_comma,
  &nop_shift_slash,
  &nop_shift_one,
  &nop_shift_two,
  &nop_shift_three,
  &nop_shift_four,
  &nop_shift_five,
  &nop_shift_six,
  &nop_shift_seven,
  &nop_shift_eight,
  &nop_shift_nine,
  &nop_shift_zero,
  NULL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,------------------------------------------------------------------------------------------------------------------------------------.
 * | Caps Lock|   1  |         2          |     3     |     4      |       5       |   6  |     7      |   8  |   9  |   0  |            |
 * |----------+------+--------------------+-----------+------------+---------------+------+------------+------+------+------+------------|
 * | Ctrl     |   Q  |         W          |    E/É    |     R      |       T       |   Y  |    Ü/U     |   I  | Ö/O  |   P  | Ctrl       |
 * |----------+------+--------------------+-----------+------------+----------------------+------------+------+------+------+------------|
 * | Shift/Esc| Ä/A  |        ß/S         |     D     |     F      |       G       |   H  |     J      |   K  |   L  |   '  | Shift/Enter|
 * |----------+------+--------------------+-----------+------------+---------------|------+------------+------+------+------+------------|
 * | Leader   |   Z  |       Cut/X        |  Copy/C   |   Paste/V  |       B       |   N  |     M      |   ,  |   .  |   /  | Leader     |
 * |----------+------+--------------------+-----------+------------+---------------+------+------------+------+------+------+------------|
 * |          |      |Compositor+Alt+Shift|   Raise   |Lower/Space | Compositor+Alt|Mouse |Lower/Space |Raise |      |      | Manage     |
 * `-------------------------------------------------------------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid(
  KC_CAPS,          KC_1,    KC_2,              KC_3,       KC_4,   KC_5,         KC_6,       KC_7,         KC_8,    KC_9,    KC_0,       _______,
  KC_LCTL,          KC_Q,    KC_W,              LT_E_ACGRV, KC_R,   KC_T,         LT_COPY_Y,  KC_U,         KC_I,    KC_O,    LT_PASTE_P, KC_RCTL,
  MOD_TAP_LSFT_ESC, LT_AE_A, LT_SZ_S,           KC_D,       KC_F,   KC_G,         KC_H,       KC_J,         KC_K,    KC_L,    KC_QUOT,    MOD_TAP_LSFT_ENT,
  KC_LEAD,          KC_Z,    LT_CUT_X,          KC_C,       KC_V,   KC_B,         KC_N,       KC_M,         KC_COMM, KC_DOT,  KC_SLSH,    KC_LEAD,
  _______,          _______, LM_COMP_LALT_LSFT, RAISE,      LOWER,  LM_COMP_LALT, TG(_MOUSE), LT_LOWER_SPC, RAISE,   _______, _______,    MANAGE
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  @   |  %   |  (   |   )  |      |      |  +   |  _   |  <   |  &   |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  ~   |      |  [   |   ]  |      | Left | Down |  Up  |Right |  "   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |  {   |   }  |      |      |      |  :   |   !  |  \   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_AT,   KC_PERC, KC_LPRN, KC_RPRN, XXXXXXX, XXXXXXX, KC_PLUS, KC_UNDS, KC_LT,   KC_AMPR, XXXXXXX,
  XXXXXXX, KC_TILD, XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DQUO, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, XXXXXXX, XXXXXXX, XXXXXXX, KC_COLN, KC_EXLM, KC_BSLS, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  #   |      |      |      |      |      |   *  |  -   |  >   |  =   |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  `   |      |      |      |      | Bspk |Pg Dn |Pg Up | Tab  |  $   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  ;   |  ?   |  |   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_HASH, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ASTR, KC_MINS, KC_GT,   KC_EQL,  XXXXXXX,
  XXXXXXX, KC_GRV,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC, KC_PGDN, KC_PGUP, KC_TAB,  KC_DLR,  XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SCLN, KC_QUES, KC_PIPE, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Mouse
 * ,---------------------------------------------------------------------------------------------------------------------------------------.
 * |      |      |              |              |              |               |           |           |         |            |      |      |
 * |------+------+--------------+--------------+--------------+---------------+-----------+-----------+---------+------------+------+------|
 * |      |      |              |              |              |               |Wheel Left |Wheel Down |Wheel Up |Wheel Right |      |Ctrl  |
 * |------+------+--------------+--------------+--------------+---------------------------+-----------+---------+------------+------+------|
 * |      |      |   Button 3   |   Button 2   |   Button 1   |               |Cursor Left|Cursor Down|Cursor Up|Cursor Right|      |      |
 * |------+------+--------------+--------------+--------------+---------------|-----------+-----------+---------+------------+------+------|
 * |      |      |              |              |              |               |           |           |         |            |      |      |
 * |------+------+--------------+--------------+--------------+---------------+-----------+-----------+---------+------------+------+------|
 * |      |      |Accelaration 2|Accelaration 1|Accelaration 0| Compositor+Alt|           |           |         |            |      |      |
 * `---------------------------------------------------------------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT_preonic_grid(
  XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,     XXXXXXX,        XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX, KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT, XXXXXXX, _______,
  XXXXXXX, XXXXXXX, KC_MS_BTN3,   KC_MS_BTN2,   KC_MS_BTN1,   XXXXXXX, KC_MS_LEFT,    KC_MS_DOWN,    KC_MS_UP,    KC_MS_RIGHT,    XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,     XXXXXXX,        XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_MS_ACCEL2, KC_MS_ACCEL1, KC_MS_ACCEL0, _______, _______,       XXXXXXX,       XXXXXXX,     XXXXXXX,        XXXXXXX, XXXXXXX),

/* Manage
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |Aud cy|Aud on|AudOff|      |      |Qwerty|      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Reset |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MANAGE] = LAYOUT_preonic_grid(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, MU_MOD,  AU_ON,   AU_OFF,  XXXXXXX, XXXXXXX, QWERTY,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Compositor
 * ,-----------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   '  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   Z  |   X  |   C  |  V   |   B  |   N  |   M  |   ,  |   .  |   /  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |Space |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_COMPOSITOR] = LAYOUT_preonic_grid(
  XXXXXXX, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    XXXXXXX,
  XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    XXXXXXX,
  XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,   KC_K,    KC_L,    KC_QUOT, KC_ENT,
  XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
          } else {
            layer_off(_LOWER);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
          } else {
            layer_off(_RAISE);
          }
          return false;
          break;
        case MANAGE:
          if (record->event.pressed) {
            layer_on(_MANAGE);
          } else {
            layer_off(_MANAGE);
          }
          return false;
          break;
        case COMPOSITOR:
          if (record->event.pressed) {
            layer_on(_COMPOSITOR);
          } else {
            layer_off(_COMPOSITOR);
          }
          return false;
          break;
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
            #ifdef RGBLIGHT_ENABLE
              rgblight_step();
            #endif
            #ifdef __AVR__
            writePinLow(E6);
            #endif
          } else {
            unregister_code(KC_RSFT);
            #ifdef __AVR__
            writePinHigh(E6);
            #endif
          }
          return false;
          break;
        case LT_CUT_X:
          if (!record->tap.count && record->event.pressed) {
              tap_code16(C(KC_X)); /* cut on hold */
              return false;
          }
          return true;
        case LT_COPY_Y:
          if (!record->tap.count && record->event.pressed) {
              tap_code16(C(KC_C)); /* copy on hold */
              return false;
          }
          return true;
        case LT_PASTE_P:
          if (!record->tap.count && record->event.pressed) {
              tap_code16(C(KC_V)); /* paste on hold */
              return false;
          }
          return true;
        case LT_AE_A:
          if (!record->tap.count && record->event.pressed) {
              tap_code16(RALT(KC_Q));
              return false;
          }
          return true;
        case LT_OE_O:
          if (!record->tap.count && record->event.pressed) {
              tap_code16(RALT(KC_P));
              return false;
          }
          return true;
        case LT_UE_U:
          if (!record->tap.count && record->event.pressed) {
              tap_code16(RALT(KC_Y));
              return false;
          }
          return true;
        case LT_SZ_S:
          if (!record->tap.count && record->event.pressed) {
              tap_code16(RALT(KC_S));
              return false;
          }
          return true;
        case LT_E_ACGRV:
          if (!record->tap.count && record->event.pressed) {
              tap_code16(RALT(KC_E));
              return false;
          }
          return true;
      }
    return true;
};

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                layer_on(_MANAGE);
            } else {
                layer_off(_MANAGE);
            }
            break;
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
    return true;
}

LEADER_EXTERNS();

static inline void register_ctrl_sequence(uint16_t keycode)
{
    register_code(KC_RCTL);
    register_code(keycode);
    unregister_code(keycode);
    unregister_code(KC_RCTL);
}

static inline void leader_bindings(void)
{
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_THREE_KEYS(KC_A, KC_C, KC_K) {
            SEND_STRING("Acked-by: Christian Brauner <brauner@kernel.org>");
        }

        SEQ_THREE_KEYS(KC_R, KC_V, KC_B) {
            SEND_STRING("Reviewed-by: Christian Brauner <brauner@kernel.org>");
        }

        SEQ_THREE_KEYS(KC_S, KC_O, KC_B) {
            SEND_STRING("Signed-off-by: Christian Brauner <brauner@kernel.org>");
        }

        /* Support vim-style copy. */
        SEQ_ONE_KEY(KC_Y) {
            register_code(KC_RCTL);
            register_code(KC_LSFT);
            register_code(KC_C);
            unregister_code(KC_C);
            unregister_code(KC_RCTL);
            unregister_code(KC_LSFT);
        }

        /* Support vim-style paste. */
        SEQ_ONE_KEY(KC_P) {
            register_code(KC_RCTL);
            register_code(KC_LSFT);
            register_code(KC_V);
            unregister_code(KC_V);
            unregister_code(KC_RCTL);
            unregister_code(KC_LSFT);
        }
    }
}

void matrix_scan_user(void) {
    leader_bindings();

#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
