/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
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
#include "features/mouse_turbo_click.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
#define _BL 0 // Base
#define _FL 1 // Functional
#define _OL 2 // One Note functions
#define _OL_TEMP 3 // Switch for temp Key rebinding
#define _SL 10 // Switching 


// Each Layer (except temporary ones) gets a RGB Value to differentiate.
#define _BL_RGB 255, 0, 0
#define _FL_RGB 0, 255, 0
#define _OL_RGB 0, 0, 255

#define _LOCKED_COLOR 255,255,255

// For iteration (Hotkeys in the switch layer)
uint8_t SLButtons[]={18,19,20,80,81,13,50,35,53,32};
uint8_t SLcolors[][3]={{_BL_RGB},{_FL_RGB},{_OL_RGB},{0,255,0},{255,0,0},{255,0,0},{188,23,207},{255,0,0},{0,255,0},{0,0,0}};

//Boolean variables for switches
bool layerColor = true;
bool holdW = false;

// Macro Keycodes (if needed)
enum custom_keycodes{
  LSColor = SAFE_RANGE, //Switch between color modes and Layer color RGB lighting
  //Switch Layer
  HOLDW, //For Hold W switch
  CLICKER, //Autoclicker
  //OneNote Layer
  ROUND, // round brackets
  POINTY, // pointy brackets
  SQUARED, // squared brackets
  CFONT, // Change Font in 
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: Base Layer (Default Layer)
   */
[_BL] = LAYOUT(
  QK_GESC,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_DEL,   KC_INS,   KC_PGUP,  KC_PGDN,
  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_ENT,   KC_P7,    KC_P8,    KC_P9,    KC_PPLS,
  KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,            KC_P4,    KC_P5,    KC_P6,
  KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_P1,    KC_P2,    KC_P3,    KC_PENT,
  KC_LCTL,  KC_LGUI,  KC_LALT,                      KC_SPC,                                 KC_RALT,  MO(_SL),  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,    KC_PDOT),

  /* Keymap _FL: Functional Layer: For now same as Default Layer but can be adjusted if needed 
   */
[_FL] = LAYOUT(
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,                      _______,                                _______,  MO(_SL),  _______,  _______,   _______,  _______,  _______,  _______),

  /** Keymap _OL: Onenote layer: Used to input Math equations into Onenote and other stuff he.he.
   *  _OL_TEMP: Temporary switch for WASD to arrow keys
  */
[_OL] = LAYOUT(
  _______,  LALT(KC_RBRC),  RALT(KC_MINS),  LSFT(KC_6),  CFONT,  ROUND,  POINTY,  SQUARED,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,
  MO(_OL_TEMP),      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RALT(KC_MINS),   _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,                      _______,                                _______,  MO(_SL),  _______,  _______,   _______,  _______,  _______,  KC_DOT),

  [_OL_TEMP] = LAYOUT(
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,
  _______,  LSFT(KC_1),  LSFT(KC_2),  LSFT(KC_3),  LSFT(KC_4),  LSFT(KC_5),  LSFT(KC_6),  LSFT(KC_7),  LSFT(KC_8),  LSFT(KC_9),  LSFT(KC_0),  _______,  _______,   _______,  _______,  _______,  _______,  _______,
  _______,  _______,  KC_UP,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,
  _______,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,                      _______,                                _______,  MO(_SL),  _______,  _______,   _______,  _______,  _______,  _______),

  /* Keymap _SL: Switching Layer as well as functional additions
  */
[_SL] = LAYOUT(
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   KC_PWR,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  TO(_BL),  TO(_FL),  TO(_OL),  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,  RGB_TOG,  XXXXXXX,  XXXXXXX,  RGB_RMOD,
  XXXXXXX,  XXXXXXX,    HOLDW,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_MYCM,  XXXXXXX,  XXXXXXX,   XXXXXXX,  LSColor,  XXXXXXX,  XXXXXXX,  RGB_MOD,
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,             XXXXXXX,  XXXXXXX,  XXXXXXX,
  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_HOME,  KC_END,   XXXXXXX,   KC_VOLU,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  _______,  _______,  _______,                      XXXXXXX,                                CLICKER,  XXXXXXX,  XXXXXXX,  KC_MPRV,   KC_VOLD,  KC_MNXT,  XXXXXXX,  XXXXXXX)
  /* As Default for other Layers Transparent Default with switch to Switching Layer
  */
// [_TL] = LAYOUT(
//   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,
//   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,
//   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,
//   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,  _______,  _______,
//   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,
//   _______,  _______,  _______,                      _______,                                _______,  MO(_SL),  _______,  _______,   _______,  _______,  _______,  _______)
};

/**
 * Specific Coloring for the _SL Layer
*/
void switchColorCheck(void){
  rgb_matrix_set_color_all(_LOCKED_COLOR);
  for(uint8_t i=0; i<(sizeof(SLButtons)/sizeof(SLButtons[0]));++i){
    rgb_matrix_set_color(SLButtons[i],SLcolors[i][0],SLcolors[i][1],SLcolors[i][2]);
  }
}
/**
 * Change Color depending on active Layer.
*/
void colorCheck(void){
  if(layerColor){
    switch(get_highest_layer(layer_state)){
      case _BL: rgb_matrix_set_color_all(_BL_RGB);break;
      case _FL: rgb_matrix_set_color_all(_FL_RGB);break;
      case _OL: rgb_matrix_set_color_all(_OL_RGB);break;
      case _SL: switchColorCheck();break;
    }
  }else{
    if(IS_LAYER_ON(_SL)){
      switchColorCheck();
    }
  }
}

/**
 * Main Color changing method
*/
bool rgb_matrix_indicators_kb(void) {
  if(!rgb_matrix_indicators_user()){return false;}
  colorCheck();
  if (host_keyboard_led_state().caps_lock) {
    rgb_matrix_set_color(54, _LOCKED_COLOR);
    for(uint8_t i = 100; i<=109;i++){
      rgb_matrix_set_color(i, _LOCKED_COLOR);
    }
  }
  if (!host_keyboard_led_state().num_lock) {
    rgb_matrix_set_color(32, _LOCKED_COLOR);
    for(uint8_t i = 110; i<=119;i++){
      rgb_matrix_set_color(i, _LOCKED_COLOR);
    }
  }
  return true;
}


/**
 * Brackets
*/
void createBrackets(char *s){
  SEND_STRING(s);
  register_code(KC_LEFT);
  unregister_code(KC_LEFT);
}

/**
 * Macro functions on press and on release
*/
bool process_record_user(uint16_t keycode, keyrecord_t *record){
  switch(keycode){
    case LSColor:
      if(record->event.pressed){
        if(layerColor){
          layerColor = false;  
        }else{
          layerColor = true;
        }
      }
      break;
    case HOLDW:
      if(record->event.pressed){
        if(!holdW){
          register_code(KC_W);
          holdW = true;
        }else{
          unregister_code(KC_W);
          holdW =false;
        }
      }
    break;
    case CLICKER:
      if(!process_mouse_turbo_click(keycode, record, CLICKER)){return false;}
    break;
    case ROUND:
      if(record->event.pressed){
        createBrackets(SS_LSFT("89"));
      }
    break;
    case POINTY:
    if(record->event.pressed){
      createBrackets(SS_RALT("70"));
    }
    break;
    case SQUARED:
    if(record->event.pressed){
      createBrackets(SS_RALT("89"));
    }
    break;
    case CFONT:
    if(record->event.pressed){
      SEND_STRING(SS_TAP(X_LALT)"rsc");
    }
  }
  return true;
}

// void post_process_record_user(uint16_t keycode, keyrecord_t *record){
//   switch(keycode) {
//     case SAMPLE:
//       if(!record->event.pressed){
//       }
//       break;
//   }
// }
