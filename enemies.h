#pragma once


class Enemy {
  public:
    virtual ~Enemy() = default;

    // set coords
    void set_x(int x) { this->x = x; }
    void set_y(int y) { this->y = y; }
    // get coords
    int get_x() { return x; }
    int get_y() { return y; }

    // hitpoints and lifetime
    void set_hitpoints(int hp) { hitpoints = hp; }
    int get_hitpoints() { return hitpoints; }
    void hit() { --hitpoints; }
    void death() { dead = true; }
    bool is_dead() { return dead; }
  
    // interface
    virtual void move() = 0;

  private:
    int x;
    int y;
    int hitpoints;
    bool dead = false;
};



#define balloon_width 16
#define balloon_height 16
#define balloon_big_width 32
#define balloon_big_height 32

// 'ballon', 32x32px
const unsigned char sprite_balloon_big [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x0f, 0x00, 0x00, 0x1c, 0x30, 0x00, 
	0x00, 0x03, 0xc0, 0x00, 0x80, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x02, 0x20, 0x00, 0x00, 0x04, 
	0x10, 0x00, 0x50, 0x08, 0x10, 0x00, 0xa0, 0x08, 0x08, 0x00, 0x40, 0x11, 0x08, 0x00, 0x80, 0x10, 
	0x08, 0x00, 0x00, 0x10, 0x04, 0x00, 0x00, 0x20, 0x04, 0x00, 0x00, 0x20, 0x04, 0x00, 0x00, 0x20, 
	0x04, 0x00, 0x00, 0x20, 0x04, 0x00, 0x00, 0x20, 0x04, 0x00, 0x00, 0x20, 0x04, 0x00, 0x00, 0x10, 
	0x08, 0x01, 0x00, 0x10, 0x08, 0x02, 0x00, 0x10, 0x10, 0x05, 0x00, 0x08, 0x10, 0x02, 0x00, 0x08, 
	0x20, 0x00, 0x00, 0x04, 0x40, 0x00, 0x00, 0x02, 0x80, 0x00, 0x00, 0x01, 0x00, 0x03, 0xc0, 0x00, 
	0x00, 0x1c, 0x38, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'ballon_explode', 32x32px
const unsigned char sprite_balloon_big_explode [] PROGMEM = {
	0x00, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x20, 0x08, 0x02, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 
	0x10, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x04, 0x00, 0x00, 0x80, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x08, 
	0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x40, 0x20, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x08, 0x00
};
// 'ballon_small', 16x16px
const unsigned char sprite_balloon [] PROGMEM = {
	0xe0, 0x07, 0x10, 0x08, 0x0c, 0x30, 0x04, 0x24, 0x02, 0x48, 0x01, 0x54, 0x01, 0x88, 0x01, 0x80, 
	0x01, 0x80, 0x11, 0x80, 0x29, 0x40, 0x52, 0x40, 0x04, 0x20, 0x0c, 0x30, 0x30, 0x0c, 0xc0, 0x03
};
// 'ballon_small_explode', 16x16px
const unsigned char sprite_balloon_explode [] PROGMEM = {
	0x20, 0x04, 0x00, 0x00, 0x04, 0x20, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x20, 0x00, 0x00, 0x40, 0x04
};



#define acarus_width 32
#define acarus_height 32

// 'acarus_death_left1', 32x32px
const unsigned char sprite_acarus_death_left1 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xf0, 0x00, 
	0x20, 0x00, 0xff, 0x01, 0x00, 0x00, 0xc0, 0x07, 0x00, 0x3e, 0x00, 0x0d, 0x70, 0x7c, 0x02, 0x00, 
	0x3e, 0x60, 0x00, 0x00, 0x02, 0x70, 0x00, 0x00, 0x00, 0x00, 0xb0, 0x00, 0x00, 0x00, 0xe0, 0x00, 
	0x00, 0x07, 0x54, 0x12, 0x00, 0x43, 0x70, 0x00, 0xf0, 0x0b, 0x18, 0x00, 0x18, 0x8e, 0x5c, 0x03, 
	0xe8, 0x0c, 0x00, 0x06, 0x6c, 0x06, 0x00, 0x0d, 0x04, 0x4d, 0x90, 0x1a, 0xac, 0x86, 0x40, 0x15, 
	0xfc, 0x4b, 0x0a, 0x1a, 0x54, 0x85, 0x44, 0x1c, 0x00, 0x40, 0x0b, 0x2a, 0x00, 0x4a, 0x05, 0x44, 
	0x00, 0x00, 0x0a, 0x10, 0x00, 0x80, 0x00, 0x05, 0xa0, 0x40, 0x28, 0x00, 0xf0, 0xb0, 0x70, 0x00, 
	0x20, 0xe8, 0x38, 0x50, 0x1c, 0x30, 0xe0, 0xe0, 0x0c, 0x30, 0xc0, 0xc0, 0x04, 0x30, 0x80, 0x80
};
// 'acarus_death_left2', 32x32px
const unsigned char sprite_acarus_death_left2 [] PROGMEM = {
	0x00, 0x04, 0x00, 0x00, 0x20, 0x00, 0x00, 0x07, 0x00, 0x00, 0xd8, 0x09, 0x00, 0x36, 0x00, 0x2a, 
	0x70, 0x7c, 0x00, 0x68, 0x06, 0x60, 0x10, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 
	0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0xa0, 0x90, 0xc0, 0x01, 0x80, 0x03, 0x80, 0x00, 0xc0, 0x01, 
	0xdc, 0x02, 0x00, 0x00, 0x82, 0x42, 0x00, 0x00, 0x38, 0x01, 0x00, 0x00, 0x8b, 0x80, 0x4c, 0x0d, 
	0x41, 0x03, 0x00, 0x08, 0x82, 0x01, 0x00, 0x04, 0xaa, 0x42, 0x40, 0x6a, 0x55, 0x81, 0x05, 0x10, 
	0x00, 0xc0, 0x0a, 0x68, 0x80, 0x82, 0x04, 0x55, 0x00, 0x40, 0x0a, 0xa8, 0x00, 0x40, 0x05, 0xbc, 
	0x00, 0x00, 0x0a, 0xc0, 0x00, 0x80, 0x00, 0x14, 0x20, 0x40, 0x88, 0x00, 0x01, 0xa0, 0x50, 0x00, 
	0x2a, 0x88, 0x18, 0x00, 0x10, 0x20, 0x00, 0xc0, 0x0c, 0x30, 0xc0, 0xc0, 0x04, 0x30, 0xc0, 0xc0
};
// 'acarus_death_right1', 32x32px
const unsigned char sprite_acarus_death_right1 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x20, 0x00, 
	0x80, 0xff, 0x00, 0x04, 0xe0, 0x03, 0x00, 0x00, 0xb0, 0x00, 0x7c, 0x00, 0x00, 0x40, 0x3e, 0x0e, 
	0x00, 0x00, 0x06, 0x7c, 0x00, 0x00, 0x0e, 0x40, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 
	0x48, 0x2a, 0xe0, 0x00, 0x00, 0x0e, 0xc2, 0x00, 0x00, 0x18, 0xd0, 0x0f, 0xc0, 0x3a, 0x71, 0x18, 
	0x60, 0x00, 0x30, 0x17, 0xb0, 0x00, 0x60, 0x36, 0x58, 0x09, 0xb2, 0x20, 0xa8, 0x02, 0x61, 0x35, 
	0x58, 0x50, 0xd2, 0x3f, 0x38, 0x22, 0xa1, 0x2a, 0x54, 0xd0, 0x02, 0x00, 0x22, 0xa0, 0x52, 0x00, 
	0x08, 0x50, 0x00, 0x00, 0xa0, 0x00, 0x01, 0x00, 0x00, 0x14, 0x02, 0x05, 0x00, 0x0e, 0x0d, 0x0f, 
	0x0a, 0x1c, 0x17, 0x04, 0x07, 0x07, 0x0c, 0x38, 0x03, 0x03, 0x0c, 0x30, 0x01, 0x01, 0x0c, 0x20
};
// 'acarus_death_right2', 32x32px
const unsigned char sprite_acarus_death_right2 [] PROGMEM = {
	0x00, 0x00, 0x20, 0x00, 0xe0, 0x00, 0x00, 0x04, 0x90, 0x1b, 0x00, 0x00, 0x54, 0x00, 0x6c, 0x00, 
	0x16, 0x00, 0x3e, 0x0e, 0x00, 0x08, 0x06, 0x60, 0x00, 0x00, 0x0e, 0x00, 0xe0, 0x01, 0x00, 0x00, 
	0x60, 0x00, 0x00, 0x00, 0x09, 0x05, 0x00, 0x00, 0xc0, 0x01, 0x80, 0x03, 0x80, 0x03, 0x00, 0x01, 
	0x00, 0x00, 0x40, 0x3b, 0x00, 0x00, 0x42, 0x41, 0x00, 0x00, 0x80, 0x1c, 0xb0, 0x32, 0x01, 0xd1, 
	0x10, 0x00, 0xc0, 0x82, 0x20, 0x00, 0x80, 0x41, 0x56, 0x02, 0x42, 0x55, 0x08, 0xa0, 0x81, 0xaa, 
	0x16, 0x50, 0x03, 0x00, 0xaa, 0x20, 0x41, 0x01, 0x15, 0x50, 0x02, 0x00, 0x3d, 0xa0, 0x02, 0x00, 
	0x03, 0x50, 0x00, 0x00, 0x28, 0x00, 0x01, 0x00, 0x00, 0x11, 0x02, 0x04, 0x00, 0x0a, 0x05, 0x80, 
	0x00, 0x18, 0x11, 0x54, 0x03, 0x00, 0x04, 0x08, 0x03, 0x03, 0x0c, 0x30, 0x03, 0x03, 0x0c, 0x20
};
// 'acarus_run_left1', 32x32px
const unsigned char sprite_acarus_run_left1 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 
	0x00, 0xff, 0x01, 0x00, 0x00, 0xc0, 0x07, 0x00, 0x00, 0x00, 0x0f, 0x00, 0xc0, 0x3f, 0x1e, 0x00, 
	0xf8, 0x7f, 0x1c, 0x00, 0x08, 0xe0, 0x0c, 0x00, 0x00, 0x70, 0x0e, 0x00, 0x00, 0x38, 0x07, 0x00, 
	0x00, 0x98, 0x03, 0x00, 0x80, 0xdf, 0x01, 0x00, 0xc0, 0xf0, 0x7f, 0x00, 0x40, 0xe7, 0xd5, 0x00, 
	0x60, 0xb3, 0xab, 0x01, 0x20, 0xe8, 0x57, 0x03, 0x60, 0xb5, 0xaa, 0x02, 0xe0, 0x5f, 0x55, 0x03, 
	0xa0, 0xaa, 0xaa, 0x03, 0x00, 0x7e, 0x5d, 0x07, 0x00, 0xff, 0xff, 0x0f, 0x80, 0x63, 0x38, 0x1c, 
	0xc0, 0x61, 0x30, 0x38, 0xc0, 0x60, 0x30, 0x30, 0x40, 0x20, 0x20, 0x30, 0x40, 0x20, 0x20, 0x20
};
// 'acarus_run_left2', 32x32px
const unsigned char sprite_acarus_run_left2 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x01, 0x00, 0x00, 0xc0, 0x07, 0x00, 
	0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x1e, 0x00, 0xe0, 0x7f, 0x38, 0x00, 0x30, 0xfe, 0x70, 0x00, 
	0x10, 0xc0, 0xf0, 0x00, 0x00, 0xc0, 0xe0, 0x00, 0x00, 0xe0, 0x70, 0x00, 0x00, 0x70, 0x3e, 0x00, 
	0x00, 0x38, 0x1f, 0x00, 0x80, 0x9f, 0x07, 0x00, 0xc0, 0xf0, 0x7f, 0x00, 0x40, 0xe7, 0xd5, 0x00, 
	0x60, 0xb3, 0xab, 0x01, 0x20, 0xe8, 0x57, 0x03, 0x60, 0xb5, 0xaa, 0x02, 0xe0, 0x5f, 0x75, 0x03, 
	0xa0, 0xaa, 0xfa, 0x03, 0xc0, 0xff, 0x7d, 0x3f, 0xe0, 0xff, 0xff, 0x7f, 0x70, 0xc0, 0x61, 0xe0, 
	0x10, 0xe0, 0x40, 0xc0, 0x00, 0x60, 0x00, 0x80, 0x00, 0x60, 0x00, 0x80, 0x00, 0x40, 0x00, 0x00
};
// 'acarus_run_left3', 32x32px
const unsigned char sprite_acarus_run_left3 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 0x00, 
	0x00, 0xf8, 0x0f, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x38, 0x00, 0xc0, 0x03, 0x70, 0x00, 
	0xf8, 0x0f, 0x60, 0x00, 0xfc, 0x1f, 0x70, 0x00, 0x04, 0x38, 0x3c, 0x00, 0x00, 0x30, 0x0f, 0x00, 
	0x00, 0xb8, 0x03, 0x00, 0x80, 0xdf, 0x01, 0x00, 0xc0, 0xf0, 0x7f, 0x00, 0x40, 0xe7, 0xd5, 0x00, 
	0x60, 0xb3, 0xab, 0x01, 0x20, 0xe8, 0x57, 0x03, 0x60, 0xb5, 0xaa, 0x02, 0xe0, 0xdf, 0x55, 0x03, 
	0xa0, 0xea, 0xab, 0x1f, 0x00, 0xfe, 0xdd, 0x3f, 0x00, 0xfe, 0xff, 0x33, 0x00, 0xce, 0x38, 0x10, 
	0x00, 0x86, 0x30, 0x10, 0x00, 0x06, 0x30, 0x00, 0x00, 0x04, 0x20, 0x00, 0x00, 0x04, 0x20, 0x00
};
// 'acarus_run_right1', 32x32px
const unsigned char sprite_acarus_run_right1 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 
	0x00, 0x80, 0xff, 0x00, 0x00, 0xe0, 0x03, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x78, 0xfc, 0x03, 
	0x00, 0x38, 0xfe, 0x1f, 0x00, 0x30, 0x07, 0x10, 0x00, 0x70, 0x0e, 0x00, 0x00, 0xe0, 0x1c, 0x00, 
	0x00, 0xc0, 0x19, 0x00, 0x00, 0x80, 0xfb, 0x01, 0x00, 0xfe, 0x0f, 0x03, 0x00, 0xab, 0xe7, 0x02, 
	0x80, 0xd5, 0xcd, 0x06, 0xc0, 0xea, 0x17, 0x04, 0x40, 0x55, 0xad, 0x06, 0xc0, 0xaa, 0xfa, 0x07, 
	0xc0, 0x55, 0x55, 0x05, 0xe0, 0xba, 0x7e, 0x00, 0xf0, 0xff, 0xff, 0x00, 0x38, 0x1c, 0xc6, 0x01, 
	0x1c, 0x0c, 0x86, 0x03, 0x0c, 0x0c, 0x06, 0x03, 0x0c, 0x04, 0x04, 0x02, 0x04, 0x04, 0x04, 0x02
};
// 'acarus_run_right2', 32x32px
const unsigned char sprite_acarus_run_right2 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0f, 0x00, 0x00, 0xe0, 0x03, 0x00, 
	0x00, 0xf8, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x1c, 0xfe, 0x07, 0x00, 0x0e, 0x7f, 0x0c, 
	0x00, 0x0f, 0x03, 0x08, 0x00, 0x07, 0x03, 0x00, 0x00, 0x0e, 0x07, 0x00, 0x00, 0x7c, 0x0e, 0x00, 
	0x00, 0xf8, 0x1c, 0x00, 0x00, 0xe0, 0xf9, 0x01, 0x00, 0xfe, 0x0f, 0x03, 0x00, 0xab, 0xe7, 0x02, 
	0x80, 0xd5, 0xcd, 0x06, 0xc0, 0xea, 0x17, 0x04, 0x40, 0x55, 0xad, 0x06, 0xc0, 0xae, 0xfa, 0x07, 
	0xc0, 0x5f, 0x55, 0x05, 0xfc, 0xbe, 0xff, 0x03, 0xfe, 0xff, 0xff, 0x07, 0x07, 0x86, 0x03, 0x0e, 
	0x03, 0x02, 0x07, 0x08, 0x01, 0x00, 0x06, 0x00, 0x01, 0x00, 0x06, 0x00, 0x00, 0x00, 0x02, 0x00
};
// 'acarus_run_right3', 32x32px
const unsigned char sprite_acarus_run_right3 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x01, 0x00, 
	0x00, 0xf0, 0x1f, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x0e, 0xc0, 0x03, 
	0x00, 0x06, 0xf0, 0x1f, 0x00, 0x0e, 0xf8, 0x3f, 0x00, 0x3c, 0x1c, 0x20, 0x00, 0xf0, 0x0c, 0x00, 
	0x00, 0xc0, 0x1d, 0x00, 0x00, 0x80, 0xfb, 0x01, 0x00, 0xfe, 0x0f, 0x03, 0x00, 0xab, 0xe7, 0x02, 
	0x80, 0xd5, 0xcd, 0x06, 0xc0, 0xea, 0x17, 0x04, 0x40, 0x55, 0xad, 0x06, 0xc0, 0xaa, 0xfb, 0x07, 
	0xf8, 0xd5, 0x57, 0x05, 0xfc, 0xbb, 0x7f, 0x00, 0xcc, 0xff, 0x7f, 0x00, 0x08, 0x1c, 0x73, 0x00, 
	0x08, 0x0c, 0x61, 0x00, 0x00, 0x0c, 0x60, 0x00, 0x00, 0x04, 0x20, 0x00, 0x00, 0x04, 0x20, 0x00
};

const unsigned char* acarus_left_run[3] = {
  sprite_acarus_run_left1,
  sprite_acarus_run_left2,
  sprite_acarus_run_left3
};

const unsigned char* acarus_right_run[3] = {
  sprite_acarus_run_right1,
  sprite_acarus_run_right2,
  sprite_acarus_run_right3
};


const unsigned char* acarus_left_death[2] = {
  sprite_acarus_death_left1,
  sprite_acarus_death_left2
};

const unsigned char* acarus_right_death[2] = {
  sprite_acarus_death_right1,
  sprite_acarus_death_right2
};

