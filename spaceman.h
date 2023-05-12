#pragma once

#include "projectile.h"
#include "images.h"

#include <vector>


#define FUEL_LIMIT 75
#define AMMO_LIMIT 25


class Spaceman {
  public:

    // get inputs
    void get_left_move(bool action) { left_move = action; }
    void get_right_move(bool action) { right_move = action; }
    void get_attack_action(bool action) { attack_action = action; }
    void get_jump_action(bool action) { jump_action = action; }

    // set coordinates
    void set_x(int x) { spaceman_x = x; }
    void set_y(int y) { spaceman_y = y; }
    // get coordinates
    int get_x() { return spaceman_x; }
    int get_y() { return spaceman_y; }

    // attributes
    int get_fuel() { return spaceman_fuel; }
    int get_ammo() { return spaceman_ammo; }

    // direction 
    bool is_right_direction() { return right_direction; }
    void set_right_direction(bool dir) { right_direction = dir; }
    // ground
    void set_ground(unsigned short ground) { spaceman_ground = ground; }

    // set bitmap
    void set_bits(const unsigned char *bits) { spaceman_bits = bits; }
    // get bitmap
    const unsigned char* get_bits() { return spaceman_bits; }

    // hitpoints
    void set_hitpoints(unsigned short hp) { hitpoints = hp; }
    unsigned short get_max_hitpoints() { return MAX_HITPOINTS; }
    unsigned short get_hitpoints() { return hitpoints; }
    void update_hitpoints(int);
    void check_hitpoints();
    bool is_dead() { return game_over; }

    /* -------------- ACT -------------- */
    void set_stand_state();
    void move();
    void attack(std::vector<Projectile> &);
    void set_animation();
    /* -------------- *** -------------- */


  private:
  
    /* ----- states ----- */
    bool stand_animation = true;
    bool run_animation = false;
    bool attack_animation = false;
    bool jump_animation = false;
    bool is_attacking = false;
    bool can_attacking = true;
    bool game_over = false;

    /* ----- counters ----- */
    unsigned long long left_counter = 0;
    unsigned long long right_counter = 0;
    unsigned long long jump_counter = 0;
    unsigned long long fuel_counter = 0;
    unsigned long long ammo_counter = 0;
    unsigned long long attack_counter = 0;
    unsigned long long fall_counter = 0;

    /* ----- animation ----- */
    unsigned long long animation_counter = 0;

    short sprite_run_counter = 0;
    short sprite_jump_counter = 0;


    const unsigned char *spaceman_bits;

    /* ----- placement ----- */
    bool right_direction = true;

    int spaceman_x;
    int spaceman_y;

    /* ----- attributes ----- */
    short spaceman_fuel = 0;
    short spaceman_ammo = AMMO_LIMIT;
    unsigned short MAX_HITPOINTS = 3;
    unsigned short hitpoints = MAX_HITPOINTS;
    //unsigned short hitpoints = 1;

    unsigned short spaceman_ground;

    /* ----- inputs ----- */
    bool left_move;
    bool right_move;
    bool attack_action;
    bool jump_action;

};