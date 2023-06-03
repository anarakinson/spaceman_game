#pragma once 

#include "enemies.h"


class Acarus: public Enemy {
  public:

    Acarus(int x, int y) {
      set_hitpoints(3);
      set_x(x);
      set_y(y);
    }

    void move() override;
    void explode();

    void set_right_direction(bool dir) { right_direction = dir; }
    bool get_right_direction() { return right_direction; }

    const unsigned char *get_bits() {
      return acarus_bits;
    }

  private:
    bool right_direction = true;
    short sprite_run_counter = 0;
    short sprite_death_counter = 0;
    unsigned long long move_timer = 0;
    unsigned long long explode_timer = 0;

    bool explosion = false;

    const unsigned char *acarus_bits = sprite_acarus_run_right1;
};

