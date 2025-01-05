#ifndef PUCK_H_INCLUDED
#define PUCK_H_INCLUDED

#include "Vector2.h"
#include "CircularEntity.h"
#include "Data.h"

// Object that can move on screen


class Puck: public CircularEntity{


private:

    void updateMovement(){
        getVelocity().setX(getVelocity().getX() + getAcceleration().getX());
        getVelocity().setY(getVelocity().getY() - getAcceleration().getY());

        // Add velocity to position
        getCurrentPos().setX(getCurrentPos().getX() + getVelocity().getX() );
        getCurrentPos().setY(getCurrentPos().getY() - getVelocity().getY() );

    }

    bool playerGoal;
    bool botGoal;

public:
    Puck(float _radius, float _mass, float _speed){
        mass = _mass;
        radius = _radius;
        speed = _speed;

        // nobody scores at the start of the game
        playerGoal = false;
        botGoal = false;



    }



    void draw() override {
        circle(Data::c_to_scrn(getCurrentPos().getX()), Data::c_to_scrn(getCurrentPos().getY()),getRadius());
    }

    bool goalCheck(){


        return abs( Data::c_to_scrn(getCurrentPos().getX()) - Data::windowWidth/2.0) <= Data::windowWidth/4.0;



    }

    void bound(){

        float puckRight = Data::c_to_scrn(getCurrentPos().getX() + getRadius());

        float puckLeft = Data::c_to_scrn(getCurrentPos().getX() - getRadius());

        float puckUp = Data::c_to_scrn(getCurrentPos().getY() - getRadius());
        float puckDown = Data::c_to_scrn(getCurrentPos().getY() + getRadius());


        // If the puck hits the right side of the screen, have it bounce back
        if ( puckRight  >= Data::windowWidth) {

            getCurrentPos().setX(Data::windowWidth - getRadius()- Data::windowWidth/2);// stop the puck from going out of bounds

            getVelocity().setX( -getVelocity().getX() );// invert its horizontal velocity
        }

        // If the puck is too far to the left, first stop it from going out of bounds
        // then set invert its horizontal velocity component
        if (puckLeft <= 0){


            getCurrentPos().setX(getRadius() - Data::windowWidth/2.0);
            getVelocity().setX(-getVelocity().getX());

        }

        // If the puck is too far down
        if (puckDown >= Data::windowHeight) {


            if (!goalCheck()){
                getCurrentPos().setY(Data::windowHeight - Data::c_to_scrn(getRadius()));
                getVelocity().setY( -getVelocity().getY() );

            } else {
                if (Data::c_to_scrn(getCurrentPos().getY()) >= Data::windowHeight + getRadius() ){
                    botGoal = true;

                }

            }



        }

        // If the puck is too far down
        if (puckUp <= 0){

            if (!goalCheck()){

                getCurrentPos().setY(getRadius()-Data::windowHeight/2.0);
                getVelocity().setY(-getVelocity().getY());

            } else {

                if (Data::c_to_scrn(getCurrentPos().getY()) >= Data::windowHeight + getRadius() ){
                    playerGoal = true;

                }

            }

        }
    }

    void update(){
        updateMovement();
        bound();
    }

};


#endif // PUCK_H_INCLUDED
