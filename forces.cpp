#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include <Windows.h>

#include "Vector2.h"
#define WINDOWX 800
#define WINDOWY 1000


float start_time = 0;

float end_time;

bool activate = true;

float global_time = 0;
float posy;


/*
TO DO

    Add goals, first draw them
    then add regions that will track
    to see if the puck has past them



*/



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




// Useful function which will convert
// all numbers passed in to screen coordinates
// allows us to specify all postion coordinates
// as cartesian vectors
float c_to_scrn(float point){

    return point + WINDOWX/2.0;

}

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


float dist_x;
float dist_y;
Vector2 distance;

float speed_mod = 1;

bool collided = false;

// A function for hit detection for player objects (aka player and the bot)
void player_hit_detect(Player &player, Puck &puck, bool isbot){
    // Always track the distance between the player and the puck
    dist_x = (player.current_pos.x-400) - puck.position.x;
    dist_y = (player.current_pos.y-400) - puck.position.y;



    if (isbot){speed_mod = 0.2;}
    else{speed_mod = 1;}

    // If we have the puck has entered the region of the player and we havent already collided
    if (sqrt( pow(dist_x,2) + pow(dist_y,2) ) <= (player.radius + puck.radius) && !collided){


        // Note the current time
        start_time = global_time;

        collided = true; // note that we have now collided

        // Convert the distances into vector components
        distance.x = dist_x;
        distance.y = dist_y;


        Vector2 direction;// probably redefine this outside the function first

        // Get the unit vector pointing in the direction of the players center to
        // the pucks center
        direction.x = distance.unit_x();
        direction.y = distance.unit_y();

        // If the puck is to the left of the player upon collision
        if (dist_x > 0){
            puck.position.x -= puck.radius*(puck.velocity.norm()/player.speed);

            if (abs(player.velocity.x) == 0){

                puck.velocity.x = -direction.x*abs(puck.velocity.x) ;
            }

            else{
                puck.velocity.x = -direction.x * player.speed*abs(player.velocity.x*speed_mod);
            }


        }

        // If the puck is to the left of the player upon collision
        else if (dist_x < 0){

            // First move the puck away from the player as if it was being pushed
            // Note the amount it gets pushed is a percentage of the radius
            // which depends on the velocity its travelling at. This makes it
            // so the puck doesnt teleport upon collision when its moving slowly
            puck.position.x  += puck.radius*(puck.velocity.norm()/player.speed);

            // If the player isnt moving in the x direction
            if (abs(player.velocity.x) == 0){

                // Simply change the direction of the puck if it hits
                // the player while they are stationary
                puck.velocity.x = -direction.x*abs(puck.velocity.x);
            }

            // If the player hits the puck at all, apply the players
            // velocity to the puck
            else{puck.velocity.x = -direction.x * player.speed*abs(player.velocity.x*speed_mod);}


        }

        // If the puck is above the player upon collision
        if (dist_y > 0){
            puck.position.y -= puck.radius*(puck.velocity.norm()/player.speed);

            if (abs(player.velocity.y) == 0){
                puck.velocity.y = direction.y*abs(puck.velocity.y);
            }

            else{
                puck.velocity.y = direction.y * player.speed*abs(player.velocity.y*speed_mod);
            }


        }

        // If the puck is below the player upon collision
        else if (dist_y < 0){
            puck.position.y += puck.radius*(puck.velocity.norm()/player.speed);

            if (abs(player.velocity.y) == 0){
                puck.velocity.y = direction.y*abs(puck.velocity.y);
            }

            else{
                puck.velocity.y = direction.y * player.speed*abs(player.velocity.y*speed_mod);
            }

        }

        start_time = global_time;

    }

}


// UPDATE FUNCTION
void update(Puck &puck,Player &player,Player &bot){

    setcolor(12);

    // Draw the lil ice hockey rink lines
    circle(WINDOWX/2.0,WINDOWY/2.0,puck.radius*3);


    line(0,WINDOWY/2.0,WINDOWX/2.0 - puck.radius*3,WINDOWY/2.0);

    line(WINDOWX/2.0 + puck.radius*3,WINDOWY/2.0,WINDOWX,WINDOWY/2.0);



    setcolor(0);

    // Draw the circle
    circle(c_to_scrn(puck.position.x),c_to_scrn(puck.position.y),puck.radius);


    // Shit to do with the player puck hitting thing
    player.current_pos.x = mousex();



    // Stop the player from moving their mouse to the
    // other half of the screen (not their side >:( )
    if (mousey() > WINDOWY/2.0){
      player.current_pos.y = mousey();
    }


    setcolor(0);

    // Draw the player
    circle(player.current_pos.x,player.current_pos.y,player.radius);
    circle(bot.current_pos.x,bot.current_pos.y,bot.radius);


    setcolor(15);

    // Position vector for the players current location
    player.velocity.x = (player.current_pos.x - player.last_pos.x)/(100/6.0);
    player.velocity.y = (player.current_pos.y - player.last_pos.y)/(100/6.0);

    bot.stored_velocity.x = (bot.current_pos.x - bot.last_pos.x)/(100/6.0);
    bot.stored_velocity.y = (bot.current_pos.y - bot.last_pos.y)/(100/6.0);


    // Add acceleration to velocity
    puck.velocity.x += puck.acceleration.x;
    puck.velocity.y -= puck.acceleration.y;

    // Add velocity to position
    puck.position.x+= puck.velocity.x;
    puck.position.y+= -puck.velocity.y;

    // Moving the bot
    bot.current_pos.x += bot.velocity.x;
    bot.current_pos.y += bot.velocity.y;

    // WORK ON THIS, BOT MOVEMENT LOGIC

    // If the puck is to the right of the bot, move right
    if (puck.position.x > bot.current_pos.x+bot.radius - WINDOWX/2.0){
        bot.velocity.x = 15;
    }

    // If the puck is to the left of the bot, move right
    else if (puck.position.x < bot.current_pos.x-bot.radius - WINDOWX/2.0){
        bot.velocity.x = -15;
    }

    // If the puck is above the center of the screen, move down
    if (puck.position.y < 0){
        bot.velocity.y = 15;
    }

    // If the puck is on the players side of the screen, retreat back
    else if (puck.position.y > 0 && bot.current_pos.y > bot.radius){
        bot.velocity.y = -15;
    }



    else{bot.velocity.y = 0;}

    if (puck.position.y < bot.current_pos.y-WINDOWY/2.0){
        bot.velocity.y = -15;
    }


    player_hit_detect(player,puck,false);
    player_hit_detect(bot,puck,true);


    if (collided){
        if (global_time >= start_time + 100){
            collided = false;
        }
    }



    if (global_time >= start_time + 100){
        puck.acceleration.x = 0;
        puck.acceleration.y = 0;
    }


    /*
    * Puck boundary behavior
    */

    // If the puck is too far right
    if (( c_to_scrn(puck.position.x + puck.radius)  >= WINDOWX)){
        puck.position.x = WINDOWX - puck.radius- WINDOWX/2;
        puck.velocity.x *= -1;
    }

    // If the puck is too farleft
    if (c_to_scrn(puck.position.x- puck.radius)  <= 0){

        puck.position.x = puck.radius-400;
        puck.velocity.x *= -1;
    }

    // If the puck is too far up
    if (c_to_scrn(puck.position.y+ puck.radius)  >= WINDOWY){
        puck.position.y =WINDOWY - c_to_scrn(puck.radius);
        puck.velocity.y *= -1;
        //puck.position.y = WINDOWY - puck.radius- WINDOWY/2;

    }

    // If the puck is too far down
    if (c_to_scrn(puck.position.y - puck.radius)  <= 0){
        puck.position.y = puck.radius-400;
        puck.velocity.y *= -1;

    }




    // Frame delay for animation
    delay(100/6);
    global_time += 100/6.0;


    player.last_pos.x = player.current_pos.x;
    player.last_pos.y = player.current_pos.y;

    if (abs(puck.velocity.x) > 0){
        puck.velocity.x -= puck.velocity.x * 0.05;
    }

    if (abs(puck.velocity.y) > 0){
        puck.velocity.y -= puck.velocity.y * 0.05;
    }

    // Clear screen
    clearviewport();
}


int main(){

    int gd = DETECT, gm;

    initwindow(WINDOWX,WINDOWY);

    setbkcolor(11);

    Puck test;
    test.position.x = 0;
    test.position.y = +200;
    test.velocity.x = 0;
    test.velocity.y = 0;
    test.acceleration.x = 0;
    test.acceleration.y = 0;

    Player p_obj;
    p_obj.current_pos.x = 0;
    p_obj.current_pos.y= 0;


    Player bot_obj;
    bot_obj.current_pos.x = WINDOWX/2.0;
    bot_obj.current_pos.y = bot_obj.radius;
    bot_obj.velocity.x = 0;
    bot_obj.velocity.y = 0;


    while (true){
        update(test,p_obj,bot_obj);
    }

    // Closing shit
    getch();
    closegraph();

    return 0;



}
