#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Vector2.h"
#include "Puck.h"
#include <graphics.h>
#include <string>
#include <cstdlib>

#define WINDOWX 800

class Player{

private:
    float mass;
    float speed;
    bool isBot;
    float radius;
    int score;

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
        score = 0;

    }

    Vector2 &getCurrentPos(){
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

    char* getScore(){
        return itoa(score, NULL, 10);
    }

    void incrementScore(){
        score++;
    }

    bool checkIsBot(){
        return isBot;
    }

    void draw(){
        circle(getCurrentPos().getX(),getCurrentPos().getY(),getRadius());
    }

    void checkCollision(Puck &puck){
        float speedMod;

        if (isBot){speedMod = 0.2;}
        else {speedMod = 1;}

        // get a vector that is the distanceToPuck to the puck
        Vector2 distanceToPuck(
              (getCurrentPos().getX()-WINDOWX/2.0) - puck.position.getX(),
              (getCurrentPos().getY()-WINDOWX/2.0) - puck.position.getY()

        );

        if (distanceToPuck.norm() <= getRadius() + puck.radius){

            Vector2 direction = distanceToPuck.getUnitVector();

            if (direction.getX() > 0){

            puck.position.setX(puck.position.getX() - puck.radius*(puck.velocity.norm()/getSpeed()) );

            if (abs(getVelocity().getX()) == 0){

                puck.velocity.setX(-direction.getX()*abs(puck.velocity.getX()));
            }

            else{

                puck.velocity.setX(-direction.getX()*abs(puck.velocity.getX()));

                puck.velocity.setX(-direction.getX() * getSpeed()*abs(getVelocity().getX()*speedMod));
            }


        }

        // If the puck is to the right of thce player upon collision
        else if (distanceToPuck.getX() < 0){

            // First move the puck away from the player as if it was being pushed
            // Note the amount it gets pushed is a percentage of the radius
            // which depends on the velocity its travelling at. This makes it
            // so the puck doesnt teleport upon collision when its moving slowly

            puck.position.setX(puck.position.getX() + puck.radius*(puck.velocity.norm()/getSpeed()));

            // If the player isnt moving in the x direction
            if (abs(getVelocity().getX()) == 0){

                // Simply change the direction of the puck if it hits
                // the player while they are stationary
                puck.velocity.setX(-direction.getX()*abs(puck.velocity.getX()));
            }

            // If the player hits the puck at all, apply the players
            // velocity to the puck
            else{puck.velocity.setX(-direction.getX() * getSpeed()*abs(getVelocity().getX()*speedMod));}


        }

        // If the puck is above the player upon collision
        if (distanceToPuck.getY() > 0){

            puck.position.setY(puck.position.getY() - puck.radius*(puck.velocity.norm()/getSpeed()));

            if (abs(getVelocity().getY()) == 0){

                puck.velocity.setY(direction.getY()*abs(puck.velocity.getY()));
            }

            else{

                puck.velocity.setY(direction.getY() * getSpeed()*abs(getVelocity().getY()*speedMod));
            }


        }

        // If the puck is below the player upon collision
        else if (distanceToPuck.getY() < 0){


            puck.position.setY(puck.position.getY() + puck.radius*(puck.velocity.norm()/getSpeed()));

            if (abs(getVelocity().getY()) == 0){


                puck.velocity.setY(direction.getY()*abs(puck.velocity.getY()));
            }

            else{
                puck.velocity.setY(direction.getY() * getSpeed()*abs(getVelocity().getY()*speedMod));
            }

        }

    }
}






};




#endif // PLAYER_H_INCLUDED
