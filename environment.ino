#include "environment.h"

#define grass_height 8
#define grass_width 8 
#define bush_height 16
#define bush_width 16 
#define tree_height 44
#define tree_width 32 
#define projectile_height 8
#define projectile_width 8 

// 'grass', 8x8px
const unsigned char sprite_grass [] PROGMEM = {
  0x00, 0x00, 0x28, 0x92, 0x54, 0x38, 0x92, 0x7c
};
// 'bush', 16x16px
const unsigned char sprite_bush [] PROGMEM = {
  0x00, 0x00, 0x00, 0x01, 0x40, 0x05, 0x80, 0x03, 0x30, 0x19, 0x48, 0x25, 0x80, 0x02, 0xd8, 0x37, 
  0xa4, 0x4a, 0x42, 0x85, 0x82, 0x82, 0x32, 0x99, 0x48, 0x25, 0x80, 0x03, 0x20, 0x09, 0xc0, 0x07
};
// 'projectile2_left', 4x4px
const unsigned char sprite_projectile2_left [] PROGMEM = {
  0x00, 0x02, 0x0d, 0x02
};
// 'projectile2_rigth', 4x4px
const unsigned char sprite_projectile2_right [] PROGMEM = {
  0x00, 0x04, 0x0b, 0x04
};
// 'projectile1_left', 8x8px
const unsigned char sprite_projectile1_left [] PROGMEM = {
  0x00, 0x00, 0x0c, 0x36, 0xfb, 0x36, 0x0c, 0x00
};
// 'projectile1_right', 8x8px
const unsigned char sprite_projectile1_right [] PROGMEM = {
  0x00, 0x00, 0x30, 0x6c, 0xdf, 0x6c, 0x30, 0x00
};

// 'full_moon', 32x32px
const unsigned char sprite_full_moon [] PROGMEM = {
  0x00, 0xe0, 0x07, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x80, 0x03, 0xc0, 0x01, 
  0xc0, 0x80, 0x00, 0x03, 0x60, 0x00, 0x00, 0x06, 0x30, 0x00, 0x00, 0x0c, 0x18, 0x00, 0x08, 0x18, 
  0x08, 0x78, 0x00, 0x10, 0x0c, 0x08, 0x00, 0x30, 0x04, 0x08, 0x00, 0x20, 0x64, 0x38, 0x40, 0x20, 
  0x36, 0x18, 0x3c, 0x44, 0x12, 0x00, 0x04, 0x40, 0x33, 0x00, 0x2c, 0xc0, 0x03, 0x00, 0x38, 0xc0, 
  0x03, 0x00, 0x10, 0xc0, 0x03, 0x00, 0x00, 0xcc, 0x82, 0x41, 0x00, 0x44, 0x86, 0x00, 0x00, 0x5c, 
  0x84, 0x04, 0x00, 0x20, 0x84, 0x06, 0x30, 0x20, 0x8c, 0x03, 0x30, 0x30, 0x08, 0x00, 0x20, 0x10, 
  0x18, 0x40, 0x28, 0x18, 0x30, 0x80, 0x38, 0x0c, 0x60, 0x02, 0x00, 0x06, 0xc0, 0x00, 0x00, 0x07, 
  0x80, 0x03, 0xc0, 0x01, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xf0, 0x0f, 0x00
};
// 'half_moon', 32x32px
const unsigned char sprite_half_moon [] PROGMEM = {
  0x00, 0xe0, 0x07, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x80, 0x03, 0xc0, 0x01, 
  0xc0, 0x80, 0x00, 0x03, 0x60, 0x00, 0x00, 0x06, 0x30, 0x00, 0x00, 0x0c, 0x18, 0x00, 0x08, 0x18, 
  0x08, 0x78, 0x00, 0x10, 0x0c, 0x08, 0x00, 0x30, 0x04, 0x08, 0x00, 0x20, 0x64, 0x38, 0x40, 0x20, 
  0x36, 0x18, 0x3c, 0x44, 0x12, 0x00, 0x04, 0x40, 0x33, 0x00, 0xec, 0xdf, 0x03, 0x00, 0x38, 0xf0, 
  0x03, 0x00, 0x0c, 0x00, 0x03, 0x00, 0x06, 0x00, 0x82, 0x41, 0x03, 0x00, 0x86, 0x80, 0x01, 0x00, 
  0x84, 0xc4, 0x00, 0x00, 0x84, 0x46, 0x00, 0x00, 0x8c, 0x63, 0x00, 0x00, 0x08, 0x20, 0x00, 0x00, 
  0x18, 0x20, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x60, 0x32, 0x00, 0x00, 0xc0, 0x10, 0x00, 0x00, 
  0x80, 0x13, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'small_half_moon', 16x16px
const unsigned char sprite_small_half_moon [] PROGMEM = {
  0xe0, 0x07, 0x18, 0x08, 0x04, 0x10, 0x82, 0x26, 0x2b, 0x44, 0x65, 0x40, 0x01, 0x78, 0x01, 0x0e, 
  0x21, 0x01, 0x89, 0x00, 0x9b, 0x00, 0x42, 0x00, 0x64, 0x00, 0x48, 0x00, 0x70, 0x00, 0x00, 0x00
};
// 'very_small_half_moon', 8x8px
const unsigned char sprite_very_small_half_moon [] PROGMEM = {
  0x3c, 0x5a, 0x95, 0xe1, 0x3b, 0x19, 0x0a, 0x0c
};
// 'small_moon', 16x16px
const unsigned char sprite_small_moon [] PROGMEM = {
  0xe0, 0x07, 0x18, 0x08, 0x84, 0x30, 0x02, 0x22, 0x22, 0x40, 0x67, 0x40, 0x01, 0xc0, 0x01, 0x86, 
  0x41, 0xa0, 0x09, 0xe0, 0x1a, 0xc4, 0x02, 0x44, 0xa4, 0x26, 0x08, 0x10, 0x30, 0x0c, 0xc0, 0x03
};

// 'Tree', 32x44px
const unsigned char sprite_tree [] PROGMEM = {
  0x00, 0x20, 0x50, 0x00, 0x00, 0x28, 0x50, 0x00, 0x80, 0x38, 0x70, 0x60, 0x80, 0x60, 0x1c, 0x20, 
  0x80, 0xc1, 0x07, 0x31, 0x07, 0xfd, 0x02, 0x11, 0x0c, 0xe1, 0x02, 0x89, 0x18, 0xc1, 0x02, 0xc9, 
  0xf0, 0x81, 0x03, 0x7a, 0x30, 0x83, 0x03, 0x0e, 0x1e, 0x82, 0x01, 0x06, 0x00, 0x86, 0x81, 0x03, 
  0x00, 0xbc, 0xc1, 0x00, 0x00, 0xf8, 0x61, 0x40, 0x02, 0xe0, 0x31, 0x40, 0x03, 0xc0, 0x11, 0x60, 
  0x3e, 0x80, 0x19, 0x30, 0x60, 0x80, 0x0f, 0x10, 0xc0, 0x80, 0x07, 0x38, 0x81, 0x80, 0x01, 0x6c, 
  0x89, 0x81, 0x01, 0x47, 0x1f, 0x81, 0x81, 0x0f, 0xf8, 0x8f, 0xc1, 0x18, 0x0c, 0xf8, 0x71, 0x60, 
  0x07, 0xf0, 0x7f, 0x40, 0x00, 0xc0, 0x1f, 0x00, 0x00, 0xc0, 0x07, 0x00, 0x00, 0xc0, 0x03, 0x00, 
  0x00, 0xc4, 0x03, 0x00, 0x00, 0x48, 0x03, 0x00, 0x00, 0x4e, 0x03, 0x00, 0x00, 0x50, 0x03, 0x00, 
  0x00, 0xd0, 0x03, 0x00, 0x00, 0xe0, 0x83, 0x00, 0x00, 0xc0, 0xe3, 0x01, 0x00, 0xc0, 0x3b, 0x00, 
  0x00, 0xe0, 0x0f, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xa0, 0x07, 0x00, 
  0x00, 0xa0, 0x07, 0x00, 0x00, 0xa0, 0x07, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xf8, 0x1f, 0x00
};
