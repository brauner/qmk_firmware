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
  _UMLAUT,
  _MOUSE1,
  _MANAGE,
  _UNUSED
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  UMLAUT,
  MOUSE1,
  MANAGE,
  UNUSED,
  BACKLIT
};

#define MOD_TAP_LSFT_ESC  LSFT_T(KC_ESC)
#define MOD_TAP_LSFT_ENT  LSFT_T(KC_ENT)

#define LT_HOLD_COPY      LT(_QWERTY, KC_C)
#define LT_HOLD_CUT       LT(_QWERTY, KC_X)
#define LT_HOLD_PASTE     LT(_QWERTY, KC_V)
#define LT_LOWER_SPC      LT(_LOWER,  KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,---------------------------------------------------------------------------------------------------------.
 * | Caps Lock|   1  |   2  |   3  |   4        |   5  |   6  |   7        |   8  |   9  |   0  |            |
 * |----------+------+------+------+------------+------+------+------------+------+------+------+------------|
 * | Ctrl     |   Q  |   W  |   E  |   R        |   T  |   Y  |   U        |   I  |   O  |   P  | Ctrl       |
 * |----------+------+------+------+------------+-------------+------------+------+------+------+------------|
 * | Shift/Esc|   A  |   S  |   D  |   F        |   G  |   H  |   J        |   K  |   L  |   '  |Shift/Enter |
 * |----------+------+------+------+------------+------|------+------------+------+------+------+------------|
 * |          |   Z  |   X  |   C  |   V        |   B  |   N  |   M        |   ,  |   .  |   /  |            |
 * |----------+------+------+------+------------+------+------+------------+------+------+------+------------|
 * |          |      |Layer2|Raise |Lower/Space | Alt  |Mouse1|Lower/Space |Raise |Layer2|      |            |
 * `---------------------------------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid(
  KC_CAPS,          KC_1,    KC_2,        KC_3,         KC_4,          KC_5,    KC_6,        KC_7,         KC_8,    KC_9,   KC_0,    _______,
  KC_LCTL,          KC_Q,    KC_W,        KC_E,         KC_R,          KC_T,    KC_Y,        KC_U,         KC_I,    KC_O,   KC_P,    KC_RCTL,
  MOD_TAP_LSFT_ESC, KC_A,    KC_S,        KC_D,         KC_F,          KC_G,    KC_H,        KC_J,         KC_K,    KC_L,   KC_QUOT, MOD_TAP_LSFT_ENT,
  KC_LEAD,          KC_Z,    LT_HOLD_CUT, LT_HOLD_COPY, LT_HOLD_PASTE, KC_B,    KC_N,        KC_M,         KC_COMM, KC_DOT, KC_SLSH, KC_LEAD,
  _______,          _______, UMLAUT,      RAISE,        LOWER,         KC_LALT, TG(_MOUSE1), LT_LOWER_SPC, RAISE,   UMLAUT, _______, MANAGE
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

/* Umlaut
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  Ü   |      |  Ö   |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  Ä   |  ß   |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_UMLAUT] = LAYOUT_preonic_grid(
  XXXXXXX, XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RALT(KC_Y), XXXXXXX, RALT(KC_P), XXXXXXX, XXXXXXX,
  KC_LSFT, RALT(KC_Q), RALT(KC_S), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,    XXXXXXX, KC_LSFT,
  XXXXXXX, XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX
),

/* Mouse1
 * ,------------------------------------------------------------------------------------------------------------------------------.
 * |      |      |              |              |              |      |           |           |         |            |      |      |
 * |------+------+--------------+--------------+--------------+------+-----------+-----------+---------+------------+------+------|
 * |      |      |              |              |              |      |Wheel Left |Wheel Down |Wheel Up |Wheel Right |      |      |
 * |------+------+--------------+--------------+--------------+------------------+-----------+---------+------------+------+------|
 * |      |      |   Button 3   |   Button 2   |   Button 1   |      |Cursor Left|Cursor Down|Cursor Up|Cursor Right|      |      |
 * |------+------+--------------+--------------+--------------+------|-----------+-----------+---------+------------+------+------|
 * |      |      |              |              |              |      |           |           |         |            |      |      |
 * |------+------+--------------+--------------+--------------+------+-----------+-----------+---------+------------+------+------|
 * |      |      |Accelaration 2|Accelaration 1|Accelaration 0|      |           |           |         |            |      |      |
 * `------------------------------------------------------------------------------------------------------------------------------'
 */
[_MOUSE1] = LAYOUT_preonic_grid(
  XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,     XXXXXXX,        XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX, KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_MS_BTN3,   KC_MS_BTN2,   KC_MS_BTN1,   XXXXXXX, KC_MS_LEFT,    KC_MS_DOWN,    KC_MS_UP,    KC_MS_RIGHT,    XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,     XXXXXXX,        XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_MS_ACCEL2, KC_MS_ACCEL1, KC_MS_ACCEL0, XXXXXXX, _______,       XXXXXXX,       XXXXXXX,     XXXXXXX,        XXXXXXX, XXXXXXX),

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

/* Unused
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_UNUSED] = LAYOUT_preonic_grid(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
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
        case UMLAUT:
          if (record->event.pressed) {
            layer_on(_UMLAUT);
          } else {
            layer_off(_UMLAUT);
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
        case UNUSED:
          if (record->event.pressed) {
            layer_on(_UNUSED);
          } else {
            layer_off(_UNUSED);
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
        case LT_HOLD_CUT:
          if (!record->tap.count && record->event.pressed) {
              tap_code16(C(KC_X)); /* cut on hold */
              return false;
          }
          return true;
        case LT_HOLD_COPY:
          if (!record->tap.count && record->event.pressed) {
              tap_code16(C(KC_C)); /* copy on hold */
              return false;
          }
          return true;
        case LT_HOLD_PASTE:
          if (!record->tap.count && record->event.pressed) {
              tap_code16(C(KC_V)); /* paste on hold */
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
