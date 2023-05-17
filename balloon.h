#pragma once 

#include "enemies.h"

class Balloon: public Enemy {
  public:

    Balloon(int x, int y) {
      set_hitpoints(1);
      set_x(x);
      set_y(y);
    }

    void move() override;
    void explode();

    const unsigned char *get_bits() {
      return balloon_bits;
    }

  private:
    bool jitter_marker = false;
    unsigned long long move_timer = 0;
    unsigned long long jitter_timer = 0;
    unsigned long long explode_timer = 0;

    bool explosion = false;

    const unsigned char *balloon_bits = sprite_balloon;
};