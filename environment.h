#pragma once 

#define grass_height 8
#define grass_width 8 
#define bush_height 16
#define bush_width 16 
#define tree_height 44
#define tree_width 32 
#define projectile_height 8
#define projectile_width 8 


/* --------------------------- greenery -------------------------- */

// 'grass', 8x8px
extern const unsigned char sprite_grass [] PROGMEM;

// 'bush', 16x16px
extern const unsigned char sprite_bush [] PROGMEM;

// 'Tree', 32x44px
extern const unsigned char sprite_tree [] PROGMEM;


/* --------------------------- projectiles -------------------------- */

// 'projectile2_left', 4x4px
extern const unsigned char sprite_projectile2_left [] PROGMEM;

// 'projectile2_rigth', 4x4px
extern const unsigned char sprite_projectile2_right [] PROGMEM;

// 'projectile1_left', 8x8px
extern const unsigned char sprite_projectile1_left [] PROGMEM;

// 'projectile1_right', 8x8px
extern const unsigned char sprite_projectile1_right [] PROGMEM;


/* --------------------------- moon -------------------------- */

// 'full_moon', 32x32px
extern const unsigned char sprite_full_moon [] PROGMEM;

// 'half_moon', 32x32px
extern const unsigned char sprite_half_moon [] PROGMEM;

// 'small_half_moon', 16x16px
extern const unsigned char sprite_small_half_moon [] PROGMEM;

// 'very_small_half_moon', 8x8px
extern const unsigned char sprite_very_small_half_moon [] PROGMEM;

// 'small_moon', 16x16px
extern const unsigned char sprite_small_moon [] PROGMEM;
