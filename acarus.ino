#include "enemies.h"
#include "acarus.h"


void Acarus::move() {
  if (millis() - move_timer >= 50) {
    move_timer = millis();
    if (!explosion) {

      int x = get_x();
      int y = get_y();

      if (!right_direction) {
        acarus_bits = acarus_left_run[sprite_run_counter / 2];
        --x;
      } else if (right_direction) {
        acarus_bits = acarus_right_run[sprite_run_counter / 2];
        ++x;
      }
      sprite_run_counter++;
      if (sprite_run_counter > 5) sprite_run_counter = 0;

      set_x(x);
      set_y(y);
    }

    /* ----- explosion ----- */
    else if (explosion) {
      if (!right_direction) {
        acarus_bits = acarus_left_death[sprite_death_counter / 2];
      } else if (right_direction) {
        acarus_bits = acarus_right_death[sprite_death_counter / 2];
      }
      sprite_death_counter++;
      if (sprite_death_counter > 3) sprite_death_counter = 0;
    }
    /* ----- *** ----- */
  
    if (explosion && millis() - explode_timer >= 150) {
      death(); 
    }
  }
}

void Acarus::explode() {
  explode_timer = millis();
  explosion = true;
}