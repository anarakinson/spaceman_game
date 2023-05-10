#pragma once

#define spaceman_width 32
#define spaceman_height 32

// 32x32 bit = array 1024 bit == array 128 byte = 16x8 byte with positional encoded bit

// 'spaceman_left', 32x32px
extern const unsigned char sprite_spaceman_left [] PROGMEM;

// 'spaceman_left_attack', 32x32px
extern const unsigned char sprite_spaceman_left_attack [] PROGMEM;

// 'spaceman_left_fly1', 32x32px
extern const unsigned char sprite_spaceman_left_fly1 [] PROGMEM;

// 'spaceman_left_fly2', 32x32px
extern const unsigned char sprite_spaceman_left_fly2 [] PROGMEM;

// 'spaceman_left_run1', 32x32px
extern const unsigned char sprite_spaceman_left_run1 [] PROGMEM;

// 'spaceman_left_run2', 32x32px
extern const unsigned char sprite_spaceman_left_run2 [] PROGMEM;

// 'spaceman_right', 32x32px
extern const unsigned char sprite_spaceman_right [] PROGMEM;

// 'spaceman_right_attack', 32x32px
extern const unsigned char sprite_spaceman_right_attack [] PROGMEM;

// 'spaceman_right_fly1', 32x32px
extern const unsigned char sprite_spaceman_right_fly1 [] PROGMEM;

// 'spaceman_right_fly2', 32x32px
extern const unsigned char sprite_spaceman_right_fly2 [] PROGMEM;

// 'spaceman_right_run1', 32x32px
extern const unsigned char sprite_spaceman_right_run1 [] PROGMEM;

// 'spaceman_right_run2', 32x32px
extern const unsigned char sprite_spaceman_right_run2 [] PROGMEM;

// 'spaceman_left_fly_attack1', 32x32px
extern const unsigned char sprite_spaceman_left_fly_attack1 [] PROGMEM;

// 'spaceman_left_fly_attack2', 32x32px
extern const unsigned char sprite_spaceman_left_fly_attack2 [] PROGMEM;

// 'spaceman_right_fly_attack1', 32x32px
extern const unsigned char sprite_spaceman_right_fly_attack1 [] PROGMEM;

// 'spaceman_right_fly_attack2', 32x32px
extern const unsigned char sprite_spaceman_right_fly_attack2 [] PROGMEM;


// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 1728)
extern const unsigned char* sprite_allArray[12];

// run animation array
extern const unsigned char* spaceman_left_run[2];
extern const unsigned char* spaceman_right_run[2];

// fly animation array
extern const unsigned char* spaceman_left_jump[2];
extern const unsigned char* spaceman_right_jump[2];

// fly attack animation array
extern const unsigned char* spaceman_left_jump_attack[2];
extern const unsigned char* spaceman_right_jump_attack[2];
