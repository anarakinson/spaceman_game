#include "projectile.h"

void Projectile::flight(int modifier = 0) {
  if (right_direction) {
    this->x_coord += (1 + modifier) * 1;
  } else if (!right_direction) {
    this->x_coord -= (1 - modifier) * 1;
  }
}