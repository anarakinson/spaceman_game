#include "projectile.h"

void Projectile::flight() {
  if (this->right_direction) {
    this->x_coord += 1;
  } else if (!right_direction) {
    this->x_coord -= 1;
  }
}