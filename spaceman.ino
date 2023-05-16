#include "spaceman.h"
#include "projectile.h"
#include "images.h"

#include <vector>

void Spaceman::set_stand_state() {
  // set stand state for moving both directions or if attacking on ground
  if (left_move && right_move) {
    left_move = 0;
    right_move = 0;
  }

  if (!is_attacking) {
    if (left_move == 0 && right_move == 0) {
      stand_animation = true;
      run_animation = false;
    }
    if (jump_action == 0) {
      stand_animation = true;
      jump_animation = false;
    }
  }
}

// moving, jumping, falling
void Spaceman::move(int &environment_coords, std::vector<Projectile> &projectiles) {
  /* ----- move ----- */
  if (left_move && (millis() - left_counter >= 50)) {
    left_counter = millis();
    right_direction = false; 
    if (spaceman_x > (DISPLAY_WIDTH / 16) * 5) {
      spaceman_x--;
    } else {
      environment_coords++;
      for (int i = 0; i < projectiles.size(); ++i) {
        if (projectiles[i].right_direction) {
          projectiles[i].x_coord += 2;
        } else if (!projectiles[i].right_direction) {
          projectiles[i].x_coord += 0;
        }
      }  
    }
    stand_animation = false;
    run_animation = true;
  }
  
  if (right_move && (millis() - right_counter >= 50)) {
    right_counter = millis();
    right_direction = true;
    if (spaceman_x < (DISPLAY_WIDTH / 16) * 11 - spaceman_width) {
      spaceman_x++;
    } else {
      environment_coords--;
      for (int i = 0; i < projectiles.size(); ++i) {
        if (projectiles[i].right_direction) {
          projectiles[i].x_coord -= 0;
        } else if (!projectiles[i].right_direction) {
          projectiles[i].x_coord -= 2;
        }
      }  
    }
    stand_animation = false;
    run_animation = true;
  }  
  
  /* ----- jump ----- */
  if (jump_action && spaceman_fuel > 0 && (millis() - jump_counter >= 50)) {
    jump_counter = millis();
    spaceman_y -= 3;
    spaceman_fuel -= 2;
    stand_animation = false;
    jump_animation = true;
  }  

  /* ----- fuel ----- */ 
  if (spaceman_fuel < 0) spaceman_fuel = 0;
  if (spaceman_y >= spaceman_ground && spaceman_fuel < FUEL_LIMIT && jump_action == 0 && millis() - fuel_counter >= 75) {
    fuel_counter = millis();
    spaceman_fuel++;
  }
  
  // fall down every moment
  if (spaceman_y < spaceman_ground && millis() - fall_counter >= 50) {
    fall_counter = millis();
    spaceman_y += 2;
  }
  // push up if underground
  if (spaceman_y > spaceman_ground) {
    spaceman_y--;
  } else if (spaceman_y < 14) {
    spaceman_y++;
  }

}

// hitpoints
void Spaceman::check_hitpoints() {
  if (hitpoints <= 0) {
    game_over = true;
  } else if (hitpoints > 3) {
    hitpoints = 3;
  }
}
void Spaceman::update_hitpoints(int how) {
  switch(how) {
    case 1:
      ++hitpoints;
    case 0:
      --hitpoints;
  }
}

// attacking
void Spaceman::attack(std::vector<Projectile> &projectiles) {
  if (attack_action && can_attacking && !is_attacking && (millis() - attack_counter >= 50)) {
    attack_counter = millis();
    stand_animation = false;
    attack_animation = true;
    can_attacking = false;
    is_attacking = true;
    
    /*----------------- projectile ------------------*/
    Projectile projectile;
    projectile.right_direction = right_direction;
    projectile.x_coord = spaceman_x;
    if (right_direction) {
      projectile.x_coord += spaceman_width - projectile_width;
    }
    projectile.y_coord = spaceman_y + 16;
    projectiles.push_back(projectile);
    /*----------------- ----------- ------------------*/
  }

  // attack once and wait cooldown
  if (is_attacking && millis() - attack_counter >= 200) {
    is_attacking = false;
    attack_animation = false;
    stand_animation = true;
    spaceman_ammo--;
  }
  /* ----- cooldown ----- */
  if (!can_attacking && !is_attacking && spaceman_ammo && millis() - attack_counter >= 700){
    can_attacking = true;  
  }
  /* ----- ammo ----- */ 
  if (spaceman_ammo < 0) spaceman_ammo = 0;
  if (spaceman_ammo < AMMO_LIMIT && millis() - attack_counter >= 1750 && millis() - ammo_counter >= 100) {
    ammo_counter = millis();
    spaceman_ammo++;
  }

}

// animation
void Spaceman::set_animation() {
  if (millis() - animation_counter >= 50) {

    animation_counter = millis();

    if (jump_animation || attack_animation) {
      run_animation = false;    
      stand_animation = false;
    }

    // stand animation
    if (stand_animation) {
        if (right_direction) {
          spaceman_bits = sprite_spaceman_right;
        } else if (!right_direction) {
          spaceman_bits = sprite_spaceman_left;
        }
    }
    
    // run animation
    if (run_animation) {
      if (!right_direction) {
      spaceman_bits = spaceman_left_run[sprite_run_counter / 2];
      } else if (right_direction) {
        spaceman_bits = spaceman_right_run[sprite_run_counter / 2];
      }
      sprite_run_counter++;
      if (sprite_run_counter > 3) sprite_run_counter = 0;
    }
    
    // jump animation 
    else if (jump_animation) {
      if (right_direction) {
        spaceman_bits = spaceman_right_jump[sprite_jump_counter];
        if (attack_animation) {
          spaceman_bits = spaceman_right_jump_attack[sprite_jump_counter];
        }
      } else if (!right_direction) {
        spaceman_bits = spaceman_left_jump[sprite_jump_counter];
        if (attack_animation) {
          spaceman_bits = spaceman_left_jump_attack[sprite_jump_counter];
        }
      }
      sprite_jump_counter++;
      if (sprite_jump_counter > 1) sprite_jump_counter = 0;
    }
    
    // attack animation 
    else if (!jump_animation && attack_animation) {
      if (right_direction) {
        spaceman_bits = sprite_spaceman_right_attack;
      } else if (!right_direction) {
        spaceman_bits = sprite_spaceman_left_attack;
      }
    }

  }
}