#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include <Windows.h>

#include "Player.h"
#include "Vector2.h"
#include "Puck.h"

#define WINDOWX 800
#define WINDOWY 1000
#define FRICTION 0.07
#define BOT_SPEED 20


float start_time = 0;

float end_time;

bool activate = true;

float global_time = 0;



/*
TO DO

    Add goals, first draw them
    then add regions that will track
    to see if the puck has past them



*/


// Useful function which will convert
// all numbers passed in to screen coordinates
// allows us to specify all postion coordinates
// as cartesian vectors
float c_to_scrn(float point){

    return point + WINDOWX/2.0;

}



float dist_x;
float dist_y;


float speed_mod = 1;



// A function for hit detection for player objects (aka player and the bot)
void player_hit_detect(Player &player, Puck &puck, bool isbot){

    // Always track the distance between the player and the puck
    dist_x = (player.getCurrentPos().getX()-WINDOWX/2.0) - puck.position.getX();
    dist_y = (player.getCurrentPos().getY()-WINDOWX/2.0) - puck.position.getY();

    if (isbot){speed_mod = 0.2;}
    else{speed_mod = 1;}

    // If the puck has entered the region of the player and we havent already collided
    if (sqrt( pow(dist_x,2) + pow(dist_y,2) ) <= (player.getRadius() + puck.radius)){


        // Note the current time
        start_time = global_time;

        Vector2 distance(dist_x,dist_y);


        // Convert the distances into vector components
        /*
        distance.x = dist_x;
        distance.y = dist_y;
        */


        // Get the unit vector pointing in the direction of the players center to
        // the pucks center
        Vector2 direction(distance.xDirection(), distance.yDirection());// probably redefine this outside the function first




        // If the puck is to the left of the player upon collision
        if (dist_x > 0){

            puck.position.setX(puck.position.getX() - puck.radius*(puck.velocity.norm()/player.getSpeed()) );

            if (abs(player.getVelocity().getX()) == 0){

                puck.velocity.setX(-direction.getX()*abs(puck.velocity.getX()));
            }

            else{

                puck.velocity.setX(-direction.getX()*abs(puck.velocity.getX()));

                puck.velocity.setX(-direction.getX() * player.getSpeed()*abs(player.getVelocity().getX()*speed_mod));
            }


        }

        // If the puck is to the right of thce player upon collision
        else if (dist_x < 0){

            // First move the puck away from the player as if it was being pushed
            // Note the amount it gets pushed is a percentage of the radius
            // which depends on the velocity its travelling at. This makes it
            // so the puck doesnt teleport upon collision when its moving slowly

            puck.position.setX(puck.position.getX() + puck.radius*(puck.velocity.norm()/player.getSpeed()));

            // If the player isnt moving in the x direction
            if (abs(player.getVelocity().getX()) == 0){

                // Simply change the direction of the puck if it hits
                // the player while they are stationary
                puck.velocity.setX(-direction.getX()*abs(puck.velocity.getX()));
            }

            // If the player hits the puck at all, apply the players
            // velocity to the puck
            else{puck.velocity.setX(-direction.getX() * player.getSpeed()*abs(player.getVelocity().getX()*speed_mod));}


        }

        // If the puck is above the player upon collision
        if (dist_y > 0){

            puck.position.setY(puck.position.getY() - puck.radius*(puck.velocity.norm()/player.getSpeed()));

            if (abs(player.getVelocity().getY()) == 0){

                puck.velocity.setY(direction.getY()*abs(puck.velocity.getY()));
            }

            else{

                puck.velocity.setY(direction.getY() * player.getSpeed()*abs(player.getVelocity().getY()*speed_mod));
            }


        }

        // If the puck is below the player upon collision
        else if (dist_y < 0){


            puck.position.setY(puck.position.getY() + puck.radius*(puck.velocity.norm()/player.getSpeed()));

            if (abs(player.getVelocity().getY()) == 0){


                puck.velocity.setY(direction.getY()*abs(puck.velocity.getY()));
            }

            else{
                puck.velocity.setY(direction.getY() * player.getSpeed()*abs(player.getVelocity().getY()*speed_mod));
            }

        }

       // start_time = global_time;

    }

}


void drawBackground(){
    setcolor(12);

    // Draw the lil ice hockey rink lines
    circle(WINDOWX/2.0,WINDOWY/2.0, 90);


    line(0,WINDOWY/2.0,WINDOWX/2.0 - 90,WINDOWY/2.0);

    line(WINDOWX/2.0 + 90,WINDOWY/2.0,WINDOWX,WINDOWY/2.0);

    setcolor(0);
}

// UPDATE FUNCTION
void update(Puck &puck,Player &player,Player &bot){


    drawBackground();

    // Draw the circle
    circle(c_to_scrn(puck.position.getX()),c_to_scrn(puck.position.getY()),puck.radius);


    // Shit to do with the player puck hitting thing
    player.getCurrentPos().setX(mousex());


    // Stop the player from moving their mouse to the
    // other half of the screen (not their side >:( )
    if (mousey() > WINDOWY/2.0){
      player.getCurrentPos().setY(mousey());
    }


    setcolor(0);

    // Draw the player and bot
    player.draw();
    bot.draw();

    setcolor(15);

    // Position vector for the players current location

    player.getVelocity().setX( (player.getCurrentPos().getX() - player.getLastPos().getX())/(100/6.0) );
    player.getVelocity().setY( (player.getCurrentPos().getY() - player.getLastPos().getY())/(100/6.0) );



    bot.getStoredVelocity().setX( (bot.getCurrentPos().getX() - bot.getLastPos().getX()) / (100/6.0) );
    bot.getStoredVelocity().setY( (bot.getCurrentPos().getY() - bot.getLastPos().getY()) / (100/6.0) );



    // Add acceleration to velocity
    puck.velocity.setX(puck.velocity.getX() + puck.acceleration.getX());
    puck.velocity.setY(puck.velocity.getY() - puck.acceleration.getY());

    // Add velocity to position
    puck.position.setX( puck.position.getX() + puck.velocity.getX() );
    puck.position.setY( puck.position.getY() - puck.velocity.getY() );


    // Moving the bot
    bot.getCurrentPos().incrementX(bot.getVelocity().getX());
    bot.getCurrentPos().incrementY(bot.getVelocity().getY());

    // WORK ON THIS, BOT MOVEMENT LOGIC

    // If the puck is to the right of the bot, move right
    if (puck.position.getX() > bot.getCurrentPos().getX() + bot.getRadius() - WINDOWX/2.0){
        bot.getVelocity().setX(BOT_SPEED);
    }

    // If the puck is to the left of the bot, move right
    else if (puck.position.getX() < bot.getCurrentPos().getX()-bot.getRadius() - WINDOWX/2.0){
        bot.getVelocity().setX(-BOT_SPEED);
    }

    // If the puck is above the center of the screen, move down
    if (puck.position.getY() < 0){
        bot.getVelocity().setY(BOT_SPEED);
    }

    // If the puck is on the players side of the screen, retreat back
    else if (puck.position.getY() > 0 && bot.getCurrentPos().getY() > bot.getRadius()){
        bot.getVelocity().setY(-BOT_SPEED);
    }



    else{bot.getVelocity().setY(0);}

    if (puck.position.getY() < bot.getCurrentPos().getY()-WINDOWY/2.0){
        bot.getVelocity().setY(-BOT_SPEED);
    }


    player_hit_detect(player,puck,false);
    player_hit_detect(bot,puck,true);




    if (global_time >= start_time + 100){
        puck.acceleration.setY(0);
        puck.acceleration.setX(0);
    }


    /*
    * Puck boundary behavior
    */

    // If the puck is too far right
    if (( c_to_scrn(puck.position.getX() + puck.radius)  >= WINDOWX)){
        puck.position.setX(WINDOWX - puck.radius- WINDOWX/2);

        puck.velocity.setX( -puck.velocity.getX() );
    }

    // If the puck is too farleft
    if (c_to_scrn(puck.position.getX() - puck.radius) <= 0){


        puck.position.setX(puck.radius - 400);
        puck.velocity.setX(-puck.velocity.getX());

    }

    // If the puck is too far up
    if (c_to_scrn(puck.position.getY() + puck.radius)  >= WINDOWY) {

        puck.position.setY(WINDOWY - c_to_scrn(puck.radius));
        puck.velocity.setY( -puck.velocity.getY() );
        //puck.position.getY() = WINDOWY - puck.radius- WINDOWY/2;

    }

    // If the puck is too far down
    if (c_to_scrn(puck.position.getY() - puck.radius) <= 0){

        puck.position.setY(puck.radius-400);
        puck.velocity.setY(-puck.velocity.getY());

    }


    // Frame delay for animation
    delay(100/6);
    global_time += 100/6.0;


    player.getLastPos().setX(player.getCurrentPos().getX());
    player.getLastPos().setY(player.getCurrentPos().getY());

    if (abs(puck.velocity.getX()) > 0){
        puck.velocity.incrementX(-(puck.velocity.getX() * FRICTION));
    }

    if (abs(puck.velocity.getY()) > 0){

        puck.velocity.incrementY(-(puck.velocity.getY() * FRICTION));
    }

    // Clear screen
    clearviewport();
}


int main(){

    int gd = DETECT, gm;

    initwindow(WINDOWX,WINDOWY);

    setbkcolor(11);

    Puck test;
    test.position.setX(0);
    test.position.setY(200);
    test.velocity.setX(0);
    test.velocity.setY(0);
    test.acceleration.setX(0);
    test.acceleration.setY(0);

    Player user(60,6,20,false);

    Player bot(60,6,20,true);
    bot.getCurrentPos().setX(WINDOWX/2.0);
    bot.getCurrentPos().setY(bot.getRadius());



    while (true){
        update(test,user,bot);
    }

    // Closing shit
    getch();
    closegraph();

    return 0;



}
