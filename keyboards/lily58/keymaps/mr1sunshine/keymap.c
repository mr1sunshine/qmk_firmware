#include QMK_KEYBOARD_H

#include "keymap_russian.h"

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif

#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

#define KC_PREVTAB LCTL(LSFT(KC_TAB))
#define KC_NEXTTAB LCTL(KC_TAB)

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  FLSCRN,
  MXSCRN,
  NTSCRN,
  SEARCH,
  LTSCRN,
  RTSCRN,
  DLTROW,
  RPLACE,
  VSBACK,
  ALTC,
  SPOTIFY
};

enum { ESC_CAPS = 0, DELS };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------| MUTE  |    |SPOTIFY|------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |DLTROW|RPLACE|
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT( \
  TD(ESC_CAPS), KC_1, KC_2, KC_3,    KC_4,    KC_5,                                  KC_6,   KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS, \
  KC_TAB,       KC_Q, KC_W, KC_E,    KC_R,    KC_T,                                  KC_Y,   KC_U,    KC_I,    KC_O,   KC_P,    KC_BSPACE, \
  KC_LCTRL,     KC_A, KC_S, KC_D,    KC_F,    KC_G,                                  KC_H,   KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT, \
  KC_LSFT,      KC_Z, KC_X, KC_C,    KC_V,    KC_B,  KC_MUTE, SPOTIFY,        KC_N,  KC_M,   KC_COMM, KC_DOT, KC_SLSH, TD(DELS), \
                            KC_LALT, KC_LGUI, LOWER, KC_SPC,  RSFT_T(KC_ENT), RAISE, DLTROW, RPLACE \
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  ~   |      |      | HOME | END  |SEARCH|                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |FLSCRN|VSBACK|-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |KC_MPRV|------+------+------+------+------+------|
 * |      |      |NTSCRN|MXSCRN|      | ALTC |-------|    |-------|      |      |      |      |      |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT( \
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,\
  KC_TILD, _______, _______, KC_HOME, KC_END,  SEARCH,                    _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, FLSCRN,  VSBACK,                    _______, _______, _______, _______, _______, _______, \
  _______, _______, NTSCRN,  MXSCRN,  _______, ALTC,    _______, KC_MPRV, _______, _______, _______, _______, _______, KC_PIPE, \
                             _______, _______, _______, _______, _______, _______, _______, _______\
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |   [  |   ]  |                    | PGUP |LTSCRN|  Up  |RTSCRN|      |KC_DEL|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |   {  |   }  |-------.    ,-------|PGDOWN| Left | Down |Right |      |      |
 * |------+------+------+------+------+------|       |    |KC_MNXT|------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|   +  |   =  |      |      |      |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                   _______,   _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, KC_LBRC, KC_RBRC,                   KC_PGUP,   LTSCRN,  KC_UP,   RTSCRN,  _______, KC_DEL, \
  _______, _______, _______, _______, KC_LCBR, KC_RCBR,                   KC_PGDOWN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_PLUS,   KC_EQL,  _______, _______, _______, KC_BSLS, \
                             _______, _______, _______, _______, _______, _______,   _______, _______ \
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |RGBTST|XMAS  |SNAKE |RAINBW|PLAIN |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |GRADE |KNIGHT|SWIRL |BREATH|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, RGB_M_T, RGB_M_X, RGB_M_SN, RGB_M_R,  RGB_M_P, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, RGB_M_G, RGB_M_K,  RGB_M_SW, RGB_M_B, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI,  RGB_SAI,  RGB_VAI, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_HUD,  RGB_SAD,  RGB_VAD,\
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
  )
};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk

void render_keyboard(void) {
    static const char PROGMEM font_keyboard[11] = {0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0};
    oled_write_P(font_keyboard, false);
};

void render_kb_split(void) {
    static const char PROGMEM font_kb_split[11] = {0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0};
    oled_write_P(font_kb_split, false);
};

// 5x1 Layer indicator

void render_layer(void) {
    static const char PROGMEM font_layer[4][6] = {
        {0x85, 0x86, 0x87, 0x88, 0x89, 0},
        {0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0},
        {0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0},
        {0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0},
    };
    uint8_t layer = 0;
    if (layer_state_is(_ADJUST)) {
        layer = 3;
    } else if (layer_state_is(_RAISE)) {
        layer = 2;
    } else if (layer_state_is(_LOWER)) {
        layer = 1;
    }
    oled_write_P(font_layer[layer], false);
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return OLED_ROTATION_270;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keyjlogs(void);

const char *read_mode_icon(bool swap);
const char *read_host_led_state(void);
void set_timelog(void);
const char *read_timelog(void);

void render_mod_ctrl(void) {
    static const char PROGMEM font_ctrl[3] = {0x93, 0x94, 0};
    oled_write_P(font_ctrl, false);
};

void render_mod_alt(void) {
    static const char PROGMEM font_alt[3] = {0xb3, 0xb4, 0};
    oled_write_P(font_alt, false);
};

void render_mod_shift(void) {
    static const char PROGMEM font_shift[3] = {0xd3, 0xd4, 0};
    oled_write_P(font_shift, false);
};

void render_mod_gui(void) {
    static const char PROGMEM font_gui[3] = {0x95, 0x96, 0};
    oled_write_P(font_gui, false);
};

void render_mod_status(void) {
#ifdef NO_ACTION_ONESHOT
    uint8_t modifiers = get_mods();
#else
    uint8_t modifiers = get_mods() | get_oneshot_mods();
#endif

    (modifiers & MOD_MASK_CTRL) ? render_mod_ctrl() : oled_write_P(PSTR("  "), false);
    oled_write_P(PSTR(" "), false);
    (modifiers & MOD_MASK_SHIFT) ? render_mod_shift() : oled_write_P(PSTR("  "), false);

    (modifiers & MOD_MASK_ALT) ? render_mod_alt() : oled_write_P(PSTR("  "), false);
    oled_write_P(PSTR(" "), false);
    (modifiers & MOD_MASK_GUI) ? render_mod_gui() : oled_write_P(PSTR("  "), false);
}

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    // oled_write_ln(read_layer_state(), false);
    render_kb_split();
    oled_write_ln("", false);
    oled_write_ln("", false);
    oled_write_ln("", false);
    render_layer();
    oled_write_ln("", false);
    oled_write_ln("", false);
    oled_write_ln("", false);
    render_mod_status();
    oled_write_ln("", false);
    oled_write_ln("", false);
    oled_write_ln("", false);
    oled_write_ln(read_keylog(), false);
  } else {
    oled_write(read_logo(), false);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

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
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
    case FLSCRN: {
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LALT)SS_DOWN(X_LGUI)SS_DOWN(X_LCTRL)SS_TAP(X_F)SS_UP(X_LCTRL)SS_UP(X_LGUI)SS_UP(X_LALT));
        }
        break;
    }
    case MXSCRN: {
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LALT)SS_DOWN(X_LGUI)SS_DOWN(X_LCTRL)SS_TAP(X_M)SS_UP(X_LCTRL)SS_UP(X_LGUI)SS_UP(X_LALT));
        }
        break;
    }
    case NTSCRN: {
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LALT)SS_DOWN(X_LGUI)SS_DOWN(X_LCTRL)SS_TAP(X_N)SS_UP(X_LCTRL)SS_UP(X_LGUI)SS_UP(X_LALT));
        }
        break;
    }
    case SEARCH: {
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LGUI)SS_DOWN(X_LSHIFT)SS_TAP(X_UP)SS_UP(X_LSHIFT)SS_UP(X_LGUI));
        }
        break;
    }
    case LTSCRN: {
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LCTRL)SS_TAP(X_LEFT)SS_UP(X_LCTRL));
        }
        break;
    }
    case RTSCRN: {
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LCTRL)SS_TAP(X_RIGHT)SS_UP(X_LCTRL));
        }
        break;
    }
    case RPLACE: {
      if (record->event.pressed) {
          SEND_STRING(SS_DOWN(X_LGUI) SS_DOWN(X_F2) SS_UP(X_F2) SS_UP(X_LGUI));
      }
      break;
    }
    case DLTROW: {
      if (record->event.pressed) {
          SEND_STRING(SS_DOWN(X_LALT) SS_DOWN(X_LSHIFT) SS_DOWN(X_BSPACE) SS_UP(X_BSPACE) SS_UP(X_LSHIFT) SS_UP(X_LALT));
      }
      break;
    }
    case VSBACK: {
      if (record->event.pressed) {
          SEND_STRING(SS_DOWN(X_LCTRL) SS_DOWN(X_MINS) SS_UP(X_MINS) SS_UP(X_LCTRL));
      }
      break;
    }
    case ALTC: {
      if (record->event.pressed) {
          SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_C) SS_UP(X_LALT));
      }
      break;
    }
    case SPOTIFY: {
      if (record->event.pressed) {
          SEND_STRING(SS_DOWN(X_LCTRL) SS_DOWN(X_LGUI) SS_TAP(X_S) SS_UP(X_LGUI) SS_UP(X_LCTRL));
      }
    }
  }
  return true;
}

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}
#endif

void send_backspaces(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    SEND_STRING(SS_TAP(X_RSHIFT));
    reset_tap_dance (state);
  } else if (state->count >= 2) {
    SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_BSPACE) SS_UP(X_LALT));
    reset_tap_dance (state);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
[ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
[DELS] = ACTION_TAP_DANCE_FN(send_backspaces)
};
