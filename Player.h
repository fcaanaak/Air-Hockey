#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Vector2.h"
#include "Puck.h"
#include <graphics.h>
#include <string>
#include "CircularEntity.h"

#define WINDOWX 800

class Player: public CircularEntity{

private:

    int score;
    bool isBot;
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


    Vector2 &getLastPos(){
        return lastPos;
    }

    Vector2 &getStoredVelocity(){
        return storedVelocity;
    }


    char* getScore(){

        return std::to_string(score).data();
    }

    void incrementScore(){
        score++;
    }

    bool checkIsBot(){
        return isBot;
    }



    void movementUpdate(){
        if (!isBot){
            getVelocity().setX( (getCurrentPos().getX() - getLastPos().getX()) / (Data::fps) );
            getVelocity().setY( (getCurrentPos().getY() - getLastPos().getY()) / (Data::fps) );

        }
    }

    void update(){
        movementUpdate();

    }


    void checkCollision(Puck &puck){
        float speedMod;

        if (isBot){speedMod = 0.2;}
        else {speedMod = 1;}

        // get a vector that is the distanceToPuck to the puck
        Vector2 distanceToPuck(
              (getCurrentPos().getX()-WINDOWX/2.0) - puck.getCurrentPos().getX(),
              (getCurrentPos().getY()-WINDOWX/2.0) - puck.getCurrentPos().getY()

        );

        if (distanceToPuck.norm() <= getRadius() + puck.getRadius()){

            Vector2 direction = distanceToPuck.getUnitVector();

            if (direction.getX() > 0){

            puck.getCurrentPos().setX(puck.getCurrentPos().getX() - puck.getRadius()*(puck.getVelocity().norm()/getSpeed()) );

            if (abs(getVelocity().getX()) == 0){

                puck.getVelocity().setX(-direction.getX()*abs(puck.getVelocity().getX()));
            }

            else{

                puck.getVelocity().setX(-direction.getX()*abs(puck.getVelocity().getX()));

                puck.getVelocity().setX(-direction.getX() * getSpeed()*abs(getVelocity().getX()*speedMod));
            }


        }

        // If the puck is to the right of thce player upon collision
        else if (distanceToPuck.getX() < 0){

            // First move the puck away from the player as if it was being pushed
            // Note the amount it gets pushed is a percentage of the radius
            // which depends on the velocity its travelling at. This makes it
            // so the puck doesnt teleport upon collision when its moving slowly

            puck.getCurrentPos().setX(puck.getCurrentPos().getX() + puck.getRadius()*(puck.getVelocity().norm()/getSpeed()));

            // If the player isnt moving in the x direction
            if (abs(getVelocity().getX()) == 0){

                // Simply change the direction of the puck if it hits
                // the player while they are stationary
                puck.getVelocity().setX(-direction.getX()*abs(puck.getVelocity().getX()));
            }

            // If the player hits the puck at all, apply the players
            // velocity to the puck
            else{puck.getVelocity().setX(-direction.getX() * getSpeed()*abs(getVelocity().getX()*speedMod));}


        }

        // If the puck is above the player upon collision
        if (distanceToPuck.getY() > 0){

            puck.getCurrentPos().setY(puck.getCurrentPos().getY() - puck.getRadius()*(puck.getVelocity().norm()/getSpeed()));

            if (abs(getVelocity().getY()) == 0){

                puck.getVelocity().setY(direction.getY()*abs(puck.getVelocity().getY()));
            }

            else{

                puck.getVelocity().setY(direction.getY() * getSpeed()*abs(getVelocity().getY()*speedMod));
            }


        }

        // If the puck is below the player upon collision
        else if (distanceToPuck.getY() < 0){


            puck.getCurrentPos().setY(puck.getCurrentPos().getY() + puck.getRadius()*(puck.getVelocity().norm()/getSpeed()));

            if (abs(getVelocity().getY()) == 0){


                puck.getVelocity().setY(direction.getY()*abs(puck.getVelocity().getY()));
            }

            else{
                puck.getVelocity().setY(direction.getY() * getSpeed()*abs(getVelocity().getY()*speedMod));
            }

        }

    }
}


};

#endif // PLAYER_H_INCLUDED
