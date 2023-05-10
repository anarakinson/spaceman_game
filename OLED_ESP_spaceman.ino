#include <Wire.h>
#include <SSD1306Wire.h>

#include "images.h"
#include "environment.h"
#include "projectile.h"

#include <vector>

/*-------------------------------------------------------------------*/

#define SCL_PIN D4
#define SDA_PIN D3
#define LEFT_PIN D1
#define RIGHT_PIN D2
#define JUMP_PIN D6
#define ATTACK_PIN D7


/*-------------------------------------------------------------------*/

SSD1306Wire display(0x3c, SDA_PIN, SCL_PIN); // SDA , SCL 

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

// const int display_width = display.getWidth();
// const int display_width = display.getHeight();

/*-------------------------------------------------------------------*/

#define FUEL_LIMIT 75
#define AMMO_LIMIT 25
unsigned short ground = 62;

unsigned long long counter = 0;
unsigned long long left_counter = 0;
unsigned long long right_counter = 0;
unsigned long long jump_counter = 0;
unsigned long long fuel_counter = 0;
unsigned long long ammo_counter = 0;
unsigned long long attack_counter = 0;
unsigned long long fall_counter = 0;
unsigned long long projectile_counter = 0;


unsigned long long animation_counter = 0;
bool stand_animation = true;
bool run_animation = false;
bool attack_animation = false;
bool jump_animation = false;
bool is_attacking = false;
bool can_attacking = true;

int str_x1;
bool edge_reached = true;

int spaceman_x = DISPLAY_WIDTH / 3, spaceman_y = 20;
const unsigned char *spaceman_bits = sprite_spaceman_right;
const unsigned char *projectile_bits = sprite_projectile1_right;

bool right_direction = true;

short sprite_run_counter = 0;
short sprite_jump_counter = 0;

short spaceman_fuel = 0;
short spaceman_ammo = AMMO_LIMIT;
unsigned short MAX_HITPOINTS = 3;
unsigned short hitpoints = MAX_HITPOINTS;
//unsigned short hitpoints = 1;

unsigned short spaceman_ground = ground - spaceman_height + 1;

int environment_coords = 0;
int environment_objects[256];

std::vector<Projectile> projectiles;

void setup() {
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  pinMode(ATTACK_PIN, INPUT_PULLUP);
  pinMode(JUMP_PIN, INPUT_PULLUP);
  
  Serial.begin(115200);
  display.init(); 
  display.flipScreenVertically(); 

  for (int i = 0; i < 256; i += 8) {
    environment_objects[i] = DISPLAY_WIDTH * (i / 8) + 24;
    environment_objects[i+1] = DISPLAY_WIDTH * (i / 8) + 55;
    environment_objects[i+2] = DISPLAY_WIDTH * (i / 8) + 79;
    environment_objects[i+3] = DISPLAY_WIDTH * (i / 8) + 120;
    
    environment_objects[i+4] = -DISPLAY_WIDTH * (i / 8) - 24;
    environment_objects[i+5] = -DISPLAY_WIDTH * (i / 8) - 55;
    environment_objects[i+6] = -DISPLAY_WIDTH * (i / 8) - 79;
    environment_objects[i+7] = -DISPLAY_WIDTH * (i / 8) - 120;
  }
}

void loop() {
  display.clear();
  
  //               (x   y   w  h)
  display.drawRect(102, 2, 20, 8);
  for (short i = 0; i < hitpoints * 6 && hitpoints <= 3; i += 6) {
    display.fillRect(104 + i, 4, 4, 4);
  }
//  display.fillRect(110, 4, 4, 4);
//  display.fillRect(116, 4, 4, 4);
//  
//  display.fillRect(116, 16, 16, 16); 
  display.drawXbm(0, 23, 16, 16, sprite_small_half_moon);
  display.drawXbm(15, 18, 8, 8, sprite_very_small_half_moon);

  display.fillRect(116, 22, 1, 1);
  display.fillRect(126, 27, 1, 1);
  display.fillRect(93, 19, 1, 1);
  display.fillRect(88, 24, 1, 1);
  display.fillRect(102, 32, 1, 1);
//  display.fillRect(108, 45, 1, 1);
  display.fillRect(39, 19, 1, 1);
  display.fillRect(32, 32, 1, 1);

  
  display.drawHorizontalLine(0, 14, 128);
  display.drawHorizontalLine(0, ground, 128);
  
  display.setFont(ArialMT_Plain_10);
  display.drawString(2, 2, "fuel:");
  display.drawString(24, 2, String(spaceman_fuel));
  display.drawString(40, 2, "ammo:");
  display.drawString(74, 2, String(spaceman_ammo));

//  display.drawString(2, 44, String(environment_coords));
  
  
  display.setFont(ArialMT_Plain_10); // Шрифт кегль: 10, 16, 24
//  display.drawString(DISPLAY_WIDTH / 5, 52, "conquere the world!");

  

//  if (millis() - counter > time_delay) {
//    counter = millis();
//    if (edge_reached) {
//      str_x1 -= 4;
//    } else {
//      str_x1 += 4;
//    }
//  }

  if (str_x1  <= 0) edge_reached = false;
  if (str_x1  >= DISPLAY_WIDTH / 2) edge_reached = true;

  bool left_move = !digitalRead(LEFT_PIN);
  bool right_move = !digitalRead(RIGHT_PIN);
  bool attack_action = !digitalRead(ATTACK_PIN);
  bool jump_action = !digitalRead(JUMP_PIN);
  

  // set stand state for moving both directions or if attacking on ground
  if (left_move && right_move) {
//  if (left_move && right_move || (!jump_action && is_attacking)) {
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
  
  // moving
  if (left_move && (millis() - left_counter >= 50)) {
    left_counter = millis();
    right_direction = false; 
    if (spaceman_x > (DISPLAY_WIDTH / 16) * 5) {
      spaceman_x--;
    } else {
      environment_coords++;
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
    }
    stand_animation = false;
    run_animation = true;
  }  

  // jump
  if (jump_action && spaceman_fuel > 0 && (millis() - jump_counter >= 50)) {
    jump_counter = millis();
    spaceman_y -= 3;
    spaceman_fuel -= 2;
    stand_animation = false;
    jump_animation = true;
  }  
  // fuel 
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
  if (spaceman_y > spaceman_ground) {
    spaceman_y--;
  } else if (spaceman_y < 14) {
    spaceman_y++;
  }
  
  // hitpoints
  if (hitpoints <= 0) {
    display.clear();
    display.setFont(ArialMT_Plain_16);
    display.drawString(18, 18, "GAME OVER");
    display.display();
    delay(5000);
  } else if (hitpoints > 3) {
    hitpoints = 3;
  }

  // attacking
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
  // cooldown
  if (!can_attacking && !is_attacking && spaceman_ammo && millis() - attack_counter >= 700){
    can_attacking = true;  
  }
  // ammo 
  if (spaceman_ammo < 0) spaceman_ammo = 0;
  if (spaceman_ammo < AMMO_LIMIT && millis() - attack_counter >= 1750 && millis() - ammo_counter >= 100) {
    ammo_counter = millis();
    spaceman_ammo++;
  }
  /*----------------- projectile ------------------*/
  if (millis() - projectile_counter >= 25) {
    for (int i = 0; i < projectiles.size(); ++i) {
      projectile_counter = millis();
      projectiles[i].flight();
    }
  }
  for (int i = 0; i < projectiles.size(); ++i) {
    if (projectiles[i].right_direction) {
      projectile_bits = sprite_projectile1_right;
    } else {
      projectile_bits = sprite_projectile1_left;
    }
    display.drawXbm(
      projectiles[i].x_coord, 
      projectiles[i].y_coord, 
      projectile_width, 
      projectile_height, 
      projectile_bits
    );  
    if (projectiles[i].x_coord >= DISPLAY_WIDTH || projectiles[i].x_coord <= 0 - projectile_width) {
      projectiles.erase(projectiles.begin() + i);
    }
  }
  /*----------------- ----------- ------------------*/  


  /* ----------------------- animation ------------------------- */
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

  
  // draw spaceman
  display.drawXbm(spaceman_x, spaceman_y, spaceman_width, spaceman_height, spaceman_bits);

//  display.drawXbm(environment_coords + 16, ground - grass_height, grass_width, grass_height, sprite_grass);
//  display.drawXbm(environment_coords + 116, ground - grass_height, grass_width, grass_height, sprite_grass);
//  display.drawXbm(environment_coords + 43, ground - grass_height, grass_width, grass_height, sprite_grass);
//  display.drawXbm(environment_coords + 76, ground - bush_height, bush_width, bush_height, sprite_bush);

  for (int coord : environment_objects) {
    if (coord - 32 <= environment_coords && coord + 32 >= environment_coords - DISPLAY_WIDTH) {
      if (coord % 6 == 0) {
        display.drawXbm(environment_coords - coord, ground - bush_height, bush_width, bush_height, sprite_bush);
      } else if (coord % 5 == 0) {
        display.drawXbm(environment_coords - coord, ground - tree_height, tree_width, tree_height, sprite_tree);
      } else {
        display.drawXbm(environment_coords - coord, ground - grass_height, grass_width, grass_height, sprite_grass);
      }
    }
  }  
  if (environment_coords < -4100) {
    environment_coords = 4100 + DISPLAY_WIDTH;
  } else if (environment_coords > 4100 + DISPLAY_WIDTH) {
    environment_coords = -4100;
  }

  
  display.display();
}
