#pragma once 

#include "images.h"

class Projectile {
  public:
    int number;
    int x_coord;
    int y_coord;

    bool right_direction = true;

    void flight() {
      if (right_direction) {
        x_coord += 1;
      } else if (!right_direction) {
        x_coord -= 1;
      }
    }
};
