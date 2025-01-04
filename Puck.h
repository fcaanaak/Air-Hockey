#ifndef PUCK_H_INCLUDED
#define PUCK_H_INCLUDED

#include "Vector2.h"
#include "CircularEntity.h"

// Object that can move on screen


class Puck: public CircularEntity{

public:
    Puck(float _radius, float _mass, float _speed){
        mass = _mass;
        radius = _radius;
        speed = _speed;
    }

};


#endif // PUCK_H_INCLUDED
