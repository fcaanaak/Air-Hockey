#ifndef PUCK_H_INCLUDED
#define PUCK_H_INCLUDED

#include "Vector2.h"

// Object that can move on screen
struct Puck{

    // mass in kg
    float mass = 50;

    float radius = 30;

    float speed = 0;

    Vector2 position;

    Vector2 velocity;

    Vector2 acceleration;


};

#endif // PUCK_H_INCLUDED
