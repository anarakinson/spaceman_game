#include "images.h"
#include "environment.h"
#include "projectile.h"
#include "spaceman.h"

#include <Wire.h>
#include <SSD1306Wire.h>

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

// #define DISPLAY_WIDTH 128
// #define DISPLAY_HEIGHT 64

const int DISPLAY_WIDTH = display.getWidth();
const int DISPLAY_HEIGHT = display.getHeight();

/*-------------------------------------------------------------------*/

// create spaceman
Spaceman spaceman;

unsigned short ground = 62;
unsigned long long counter = 0;
unsigned long long projectile_counter = 0;

/* ----- environment ----- */
int environment_coords = 0;
int environment_objects[256];

/* ----- projectiles ----- */
const unsigned char *projectile_bits = sprite_projectile1_right;
std::vector<Projectile> projectiles;


/* --- *** --- */
void setup() {
  // set inputs
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  pinMode(ATTACK_PIN, INPUT_PULLUP);
  pinMode(JUMP_PIN, INPUT_PULLUP);
  
  // set outputs
  Serial.begin(115200);
  display.init(); 
  display.flipScreenVertically(); 


  /* ----- set up spaceman ----- */
  spaceman.set_x(DISPLAY_WIDTH / 3);
  spaceman.set_y(20);

  spaceman.set_bits(sprite_spaceman_right);
  spaceman.set_ground(ground - spaceman_height + 1);

  /* --- set up environment objects --- */
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

/* --- *** --- */
void loop() {

  display.clear();
  
  /* ----- set up UI ----- */
  //               (x   y   w  h)
  display.drawRect(102, 2, 20, 8);
  unsigned short hitpoints = spaceman.get_hitpoints();
  for (short i = 0; i < hitpoints * 6 && hitpoints <= 3; i += 6) {
    display.fillRect(104 + i, 4, 4, 4);
  }

  display.setFont(ArialMT_Plain_10);
  display.drawString(2, 2, "fuel:");
  display.drawString(24, 2, String(spaceman.get_fuel()));
  display.drawString(40, 2, "ammo:");
  display.drawString(74, 2, String(spaceman.get_ammo()));

//  display.drawString(2, 44, String(environment_coords));
  
  display.drawHorizontalLine(0, 14, 128);
  
  /* ----- --- ----- */
  
  // draw moons
  display.drawXbm(0, 23, 16, 16, sprite_small_half_moon);
  display.drawXbm(15, 18, 8, 8, sprite_very_small_half_moon);

  // draw stars
  display.fillRect(116, 22, 1, 1);
  display.fillRect(126, 27, 1, 1);
  display.fillRect(93, 19, 1, 1);
  display.fillRect(88, 24, 1, 1);
  display.fillRect(102, 32, 1, 1);
//  display.fillRect(108, 45, 1, 1);
  display.fillRect(39, 19, 1, 1);
  display.fillRect(32, 32, 1, 1);

  // draw ground
  display.drawHorizontalLine(0, ground, 128);

  /* --------------------------------------------------------------- */


  /* ----- inputs ----- */
  spaceman.get_left_move( !digitalRead(LEFT_PIN) );
  spaceman.get_right_move( !digitalRead(RIGHT_PIN) );
  spaceman.get_attack_action( !digitalRead(ATTACK_PIN) );
  spaceman.get_jump_action( !digitalRead(JUMP_PIN) );
  
  /* ----------------------------------- ACT ------------------------------------- */
  spaceman.set_stand_state();
  spaceman.move();
  spaceman.check_hitpoints();
  spaceman.attack(projectiles);
  

  /*----------------- projectile ------------------*/
  // move projectiles
  if (millis() - projectile_counter >= 25) {
    for (int i = 0; i < projectiles.size(); ++i) {
      projectile_counter = millis();
      projectiles[i].flight();
    }
  }
  // draw projectiles
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

  /* ----------------------- animation ------------------------- */
  spaceman.set_animation();

  // draw spaceman
  display.drawXbm(spaceman.get_x(), spaceman.get_y(), spaceman_width, spaceman_height, spaceman.get_bits());
  
  /* ----------------------------------------------------------------------------- */

  // draw environment
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
  // cyrcle the world
  if (environment_coords < -4100) {
    environment_coords = 4100 + DISPLAY_WIDTH;
  } else if (environment_coords > 4100 + DISPLAY_WIDTH) {
    environment_coords = -4100;
  }

  /* ----- game over ----- */
  if (spaceman.is_dead() == true) {
    display.clear();
    display.setFont(ArialMT_Plain_16);
    display.drawString(18, 18, "GAME OVER");
  }

  // draw world  
  display.display();
}
