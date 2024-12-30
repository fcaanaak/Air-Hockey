#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Vector2.h"
#include <graphics.h>

class Player{

private:
    float mass;
    float speed;
    bool isBot;
    float radius;

    Vector2 velocity;
    Vector2 acceleration;
    Vector2 currentPos;
    Vector2 storedVelocity;
    Vector2 lastPos;



public:
    Player(float _radius, float _mass, float _speed, bool _isBot){
        mass = _mass;
        radius = _radius;
        speed = _speed;
        isBot = _isBot;

    }

    Vector2& getCurrentPos(){
        return currentPos;
    }

    Vector2 &getVelocity(){
        return velocity;
    }

    Vector2 &getAcceleration(){
        return acceleration;
    }

    Vector2 &getLastPos(){
        return lastPos;
    }

    Vector2 &getStoredVelocity(){
        return storedVelocity;
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

    bool checkIsBot(){
        return isBot;
    }

    void draw(){
        circle(getCurrentPos().getX(),getCurrentPos().getY(),getRadius());
    }


};




#endif // PLAYER_H_INCLUDED
