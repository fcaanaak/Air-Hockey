#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Vector2.h"

struct Player{

    Vector2 last_pos;
    Vector2 current_pos;

    float radius = 60;
    Vector2 velocity;

    float mass = 6;

    float speed = 20;

    bool is_bot = false;

    Vector2 stored_velocity;
};


#endif // PLAYER_H_INCLUDED
