#include "images.h"
#include "environment.h"
#include "projectile.h"
#include "spaceman.h"
#include "balloon.h"
#include "acarus.h"
#include "logo.h"

#include <Wire.h>
#include <SSD1306Wire.h>

#include <vector>

/* ----------------------------------------------------------------- */
#define balloon_debug_mode 0
#define acarus_debug_mode 0
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
const int UI_EDGE = 15;
/*-------------------------------------------------------------------*/

// create spaceman
Spaceman spaceman;

unsigned short ground = 62;
unsigned long long counter = 0;
unsigned long long hit_counter = 0;
unsigned long long projectile_counter = 0;

/* ----- enemies ----- */
unsigned long long balloon_counter = 0;
std::vector<Balloon> balloons;
unsigned long long acarus_counter = 0;
std::vector<Acarus> acaruses;

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

  /* --- display logo --- */
  display.drawXbm(0, 0, 128, 65, bitmap_LOGO);
  display.display();
  delay(3000);

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
  display.drawString(44, 2, "ammo:");
  display.drawString(78, 2, String(spaceman.get_ammo()));

  // debug
  // display.drawString(2, 44, String(millis() / 1000));
#if balloon_debug_mode
  display.drawString(2, 44, String(balloons.size()));
#endif
#if acarus_debug_mode
  display.drawString(2, 44, String(acaruses.size()));
#endif

  display.drawHorizontalLine(0, UI_EDGE, 128);
  
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
  bool left_move = !digitalRead(LEFT_PIN);
  bool right_move = !digitalRead(RIGHT_PIN);
  bool attack_action = !digitalRead(ATTACK_PIN);
  bool jump_action = !digitalRead(JUMP_PIN);
  spaceman.set_left_move(left_move);
  spaceman.set_right_move(right_move);
  spaceman.set_attack_action(attack_action);
  spaceman.set_jump_action(jump_action);
  
  /* ----------------------------------- ACT ------------------------------------- */
  spaceman.set_stand_state();
  spaceman.move(environment_coords, projectiles);
  spaceman.check_hitpoints();
  spaceman.attack(projectiles);


  /* ----------------------------- balloons ----------------------------- */
  if (
    millis() - balloon_counter >= 3000 + random(0, 5000)
    // && (environment_coords < -100 || environment_coords > 100)
    ) {
    balloon_counter = millis();
    
    /* ----- balloon random placement ----- */
    int spawn_place = random(-(balloon_width + DISPLAY_WIDTH / 2), (DISPLAY_WIDTH * 1.5));
    Balloon balloon(spawn_place - environment_coords, DISPLAY_HEIGHT);
    balloons.push_back(balloon);
  }
  for (int j = 0; j < balloons.size(); ++j) {
    balloons[j].move();
    int b_x = balloons[j].get_x() + environment_coords;
    int b_y = balloons[j].get_y();
    display.drawXbm(
      b_x, 
      b_y, 
      balloon_width, 
      balloon_height, 
      balloons[j].get_bits()
    );
    if (b_y < 0 - balloon_height || balloons[j].is_dead()) {
      balloons.erase(balloons.begin() + j);
    }
    
    /* ----- debug ----- */
#if balloon_debug_mode
    // display.drawString(5 * j, 54, String(balloons[j].is_dead()));
    display.drawString(5 * j, 54, String(balloons[j].get_hitpoints()));
#endif
    /* ----- *** ----- */

    for (int i = 0; i < projectiles.size(); ++i) {
      if (
        (projectiles[i].x_coord + projectile_width > b_x + 4 &&
        projectiles[i].x_coord < b_x + balloon_width - 4)
          &&
        (projectiles[i].y_coord + projectile_height > b_y + 2 &&
        projectiles[i].y_coord < b_y + balloon_height - 2)
      ) {
        balloons[j].explode();
        projectiles.erase(projectiles.begin() + i);
      }
    }
  }
  /* ---------------------------------------------------------- */

  /* ----------------------- acaruses -------------------------- */
  if (
    millis() - acarus_counter >= 10000 + random(0, 5000)
    && 
    ((environment_coords < -600 && environment_coords > -2400) 
    || 
    (environment_coords >= 400 && environment_coords < 2000))  // acaruses inhabited regions
    && 
    acaruses.size() < 3 // maximum number of acaruses
    ) {
    acarus_counter = millis();
    
    /* ----- acarus random placement ----- */
    int spawn_place = random(0, 2);
    if (spawn_place == 0) {
      Acarus acarus(DISPLAY_WIDTH + random(DISPLAY_WIDTH) - environment_coords, ground - acarus_height);
      acarus.set_right_direction(false);
      acaruses.push_back(acarus);
    } else if (spawn_place == 1) {
      Acarus acarus(-(acarus_width + random(DISPLAY_WIDTH)) - environment_coords, ground - acarus_height);
      acarus.set_right_direction(true);
      acaruses.push_back(acarus);
    }
  }
  for (int j = 0; j < acaruses.size(); ++j) {
    acaruses[j].move();
    int b_x = acaruses[j].get_x() + environment_coords;
    int b_y = acaruses[j].get_y();
    display.drawXbm(
      b_x, 
      b_y, 
      acarus_width, 
      acarus_height, 
      acaruses[j].get_bits()
    );
    if (
      (b_x < -DISPLAY_WIDTH * 2 - acarus_width)
      || (b_x > DISPLAY_WIDTH * 2)
      || (acaruses[j].is_dead())) {
      acaruses.erase(acaruses.begin() + j);
    }
    if (
      (millis() - hit_counter > 2000) 
      &&
      ((b_x + 10 <= spaceman.get_x() + spaceman_width)
      && (b_x + acarus_width - 10  >= spaceman.get_x()))
      && 
      ((b_y + (acarus_height / 2)) + 6 <= spaceman.get_y() + spaceman_height)
      &&
      !acaruses[j].is_dead()
    ) {
      hit_counter = millis();
      spaceman.hit();
    }
    /* --- hit visual effect --- */
    if (millis() - hit_counter < 50) {
      display.fillRect(0, UI_EDGE, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    } else if (millis() - hit_counter < 150) {
      display.drawHorizontalLine(0, DISPLAY_HEIGHT / 2 + UI_EDGE, DISPLAY_WIDTH);
    }
    /* --- *** --- */
  
    /* --- debug --- */
#if acarus_debug_mode
    display.drawString(5 * j, 54, String(acaruses[j].get_hitpoints()));
    // display.drawString(5 * j, 54, String(acaruses[j].is_dead()));
#endif
    /* --- *** --- */

    for (int i = 0; i < projectiles.size(); ++i) {
      if (
        (projectiles[i].x_coord + projectile_width > b_x + 4 &&
        projectiles[i].x_coord < b_x + acarus_width - 4)
          &&
        (projectiles[i].y_coord + projectile_height > b_y + 2 &&
        projectiles[i].y_coord < b_y + acarus_height - 2)
      ) {
        acaruses[j].hit();
        if (acaruses[j].get_hitpoints() <= 0) { acaruses[j].explode(); }
        projectiles.erase(projectiles.begin() + i);
      }
    }
  }


  /* ---------------------------------------------------------- */

  /*----------------- projectile ------------------*/  
  // move projectiles
  if (millis() - projectile_counter >= 25) {
    for (int i = 0; i < projectiles.size(); ++i) {
      projectile_counter = millis();
      projectiles[i].flight(0);
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
