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
    bool is_dead() { if (hitpoints > 0) return false; else return true; }
  
    // interface
    virtual void move() = 0;

  private:
    int x;
    int y;
    int hitpoints;
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
