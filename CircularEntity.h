#ifndef CIRCULARENTITY_H_INCLUDED
#define CIRCULARENTITY_H_INCLUDED

#include "Vector2.h"
#include <graphics.h>

class CircularEntity{

protected:

    float mass;
    float radius;
    float speed;


    Vector2 velocity;
    Vector2 acceleration;
    Vector2 currentPos;



public:

    Vector2 &getCurrentPos(){
        return currentPos;
    }

    Vector2 &getVelocity(){
        return velocity;
    }

    Vector2 &getAcceleration(){
        return acceleration;
    }

    float getRadius(){
        return radius;
    }

    float getMass() {
        return mass;
    }

    float getSpeed(){
        return speed;
    }


    virtual void draw(){
        circle(getCurrentPos().getX(),getCurrentPos().getY(),getRadius());
    }





};

#endif // CIRCULARENTITY_H_INCLUDED
