#pragma once 

#include "images.h"

class Projectile {
  public:
    int number;
    int x_coord;
    int y_coord;

    bool right_direction = true;

    void flight();
    const unsigned char *projectile_bits;
};
