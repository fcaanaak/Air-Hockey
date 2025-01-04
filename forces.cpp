#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include <Windows.h>
#include <string>
#include <cstdlib>

#include "Player.h"
#include "Vector2.h"
#include "Puck.h"

#define WINDOWX 800
#define WINDOWY 800
#define FRICTION 0.07
#define BOT_SPEED 15


/*

    TODO: MAKE CODE MORE MODULAR
    ADD UPDATE FUNCTION TO PLAYER CLASS
    MOVE BOT BEHAVIOR EITHER INTO PLAYER CLASS OR JUST MAKE A BOT CLASS
    ADD A FUNCTION TO THE PUCK CLASS THAT WILL DECREASE ITS SPEED DUE TO FRICTION(COPY WHATS INSIDE OF THE UPDAATE FUNCTION IN THIS FILE)

    CONTINUE MOVING CODE FROM THE UPDATE FUNCTION INTO THE AirHockey CLASS


*/
float start_time = 0;

float end_time;

bool activate = true;

float global_time = 0;


class AirHockey{

private:
    Player player;
    Player bot;



    void draw(){

        drawBackground();

        player.draw();
        bot.draw();


    }

    void drawBackground(){
        setcolor(12);

        // Draw the lil ice hockey rink lines
        circle(WINDOWX/2.0,WINDOWY/2.0, 90);


        line(0,WINDOWY/2.0,WINDOWX/2.0 - 90,WINDOWY/2.0);

        line(WINDOWX/2.0 + 90,WINDOWY/2.0,WINDOWX,WINDOWY/2.0);

        settextstyle(COMPLEX_FONT, HORIZ_DIR, 0);
        setusercharsize(2,1,2,1);


        outtextxy(WINDOWX - textwidth(bot.getScore()), WINDOWY/2.0 - textheight(bot.getScore()), bot.getScore());
        outtextxy(WINDOWX - textwidth(player.getScore()), WINDOWY/2.0, player.getScore());

        // draw the goals
        setfillstyle(EMPTY_FILL,0);
        sector(WINDOWX/2.0, WINDOWY, 0, 180, WINDOWX/4.0, 2*player.getRadius());// players goal
        sector(WINDOWX/2.0, 0, 180, 360, WINDOWX/4.0, 2*bot.getRadius());// enemies goal

        setcolor(0);
    }

    void movePlayer(int x, int y){

        player.getCurrentPos().setX(x);

        if (y > WINDOWY/2.0){
            player.getCurrentPos().setY(y);
        }


    }

public:

    static float c_to_scrn(float point){
        return point + WINDOWX/2.0;
    }

    void update(){
        draw();


    }

    AirHockey() : bot(60, 6, 20, true), player(60, 6, 20, false) {



    }


};

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




void drawBackground(){

    setcolor(12);

    // Draw the lil ice hockey rink lines
    circle(WINDOWX/2.0,WINDOWY/2.0, 90);


    line(0,WINDOWY/2.0,WINDOWX/2.0 - 90,WINDOWY/2.0);

    line(WINDOWX/2.0 + 90,WINDOWY/2.0,WINDOWX,WINDOWY/2.0);

    settextstyle(COMPLEX_FONT, HORIZ_DIR, 0);
    setusercharsize(2,1,2,1);
    outtextxy(WINDOWX - textwidth("2"), WINDOWY/2.0 - textheight("2"), "2");
    outtextxy(WINDOWX - textwidth("3"), WINDOWY/2.0, "3");

    // draw the goals
    setfillstyle(EMPTY_FILL,0);
    sector(WINDOWX/2.0, WINDOWY, 0, 180, WINDOWX/4.0, 120);// players goal
    sector(WINDOWX/2.0, 0, 180, 360, WINDOWX/4.0, 120);// enemies goal

    setcolor(0);
}



// UPDATE FUNCTION
void update(Puck &puck,Player &player,Player &bot){


    drawBackground();

    // Draw the circle
    circle(c_to_scrn(puck.getCurrentPos().getX()),c_to_scrn(puck.getCurrentPos().getY()),puck.getRadius());


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
    puck.getVelocity().setX(puck.getVelocity().getX() + puck.getAcceleration().getX());
    puck.getVelocity().setY(puck.getVelocity().getY() - puck.getAcceleration().getY());

    // Add velocity to position
    puck.getCurrentPos().setX( puck.getCurrentPos().getX() + puck.getVelocity().getX() );
    puck.getCurrentPos().setY( puck.getCurrentPos().getY() - puck.getVelocity().getY() );


    // Moving the bot
    bot.getCurrentPos().incrementX(bot.getVelocity().getX());
    bot.getCurrentPos().incrementY(bot.getVelocity().getY());

    // WORK ON THIS, BOT MOVEMENT LOGIC

    // If the puck is to the right of the bot, move right
    if (puck.getCurrentPos().getX() > bot.getCurrentPos().getX() + bot.getRadius() - WINDOWX/2.0){
        bot.getVelocity().setX(BOT_SPEED);
    }

    // If the puck is to the left of the bot, move right
    else if (puck.getCurrentPos().getX() < bot.getCurrentPos().getX()-bot.getRadius() - WINDOWX/2.0){
        bot.getVelocity().setX(-BOT_SPEED);
    }

    // If the puck is above the center of the screen, move down
    if (puck.getCurrentPos().getY() < 0){
        bot.getVelocity().setY(BOT_SPEED);
    }

    // If the puck is on the players side of the screen, retreat back
    else if (puck.getCurrentPos().getY() > 0 && bot.getCurrentPos().getY() > bot.getRadius()){
        bot.getVelocity().setY(-BOT_SPEED);
    }



    else{bot.getVelocity().setY(0);}

    if (puck.getCurrentPos().getY() < bot.getCurrentPos().getY()-WINDOWY/2.0){
        bot.getVelocity().setY(-BOT_SPEED);
    }

    /*
    player_hit_detect(player,puck,false);
    player_hit_detect(bot,puck,true);
    */
    player.checkCollision(puck);
    bot.checkCollision(puck);


    if (global_time >= start_time + 100){
        puck.getAcceleration().setY(0);
        puck.getAcceleration().setX(0);
    }


    /*
    * Puck boundary behavior
    */

    // If the puck is too far right
    if (( c_to_scrn(puck.getCurrentPos().getX() + puck.getRadius())  >= WINDOWX)){
        puck.getCurrentPos().setX(WINDOWX - puck.getRadius()- WINDOWX/2);

        puck.getVelocity().setX( -puck.getVelocity().getX() );
    }

    // If the puck is too farleft
    if (c_to_scrn(puck.getCurrentPos().getX() - puck.getRadius()) <= 0){


        puck.getCurrentPos().setX(puck.getRadius() - 400);
        puck.getVelocity().setX(-puck.getVelocity().getX());

    }

    // If the puck is too far up
    if (c_to_scrn(puck.getCurrentPos().getY() + puck.getRadius())  >= WINDOWY) {

        puck.getCurrentPos().setY(WINDOWY - c_to_scrn(puck.getRadius()));
        puck.getVelocity().setY( -puck.getVelocity().getY() );
        //puck.getCurrentPos().getY() = WINDOWY - puck.getRadius()- WINDOWY/2;

    }

    // If the puck is too far down
    if (c_to_scrn(puck.getCurrentPos().getY() - puck.getRadius()) <= 0){

        puck.getCurrentPos().setY(puck.getRadius()-400);
        puck.getVelocity().setY(-puck.getVelocity().getY());

    }


    // Frame delay for animation
    delay(100/6);
    global_time += 100/6.0;


    player.getLastPos().setX(player.getCurrentPos().getX());
    player.getLastPos().setY(player.getCurrentPos().getY());

    if (abs(puck.getVelocity().getX()) > 0){
        puck.getVelocity().incrementX(-(puck.getVelocity().getX() * FRICTION));
    }

    if (abs(puck.getVelocity().getY()) > 0){

        puck.getVelocity().incrementY(-(puck.getVelocity().getY() * FRICTION));
    }

    // Clear screen
    clearviewport();
}


int main(){

    int gd = DETECT, gm;

    initwindow(WINDOWX,WINDOWY);

    setbkcolor(11);

    Puck test(30,50,0);

    Player player(60,6,20,false);

    Player bot(60,6,20,true);
    bot.getCurrentPos().setX(WINDOWX/2.0);
    bot.getCurrentPos().setY(bot.getRadius());

    while (true){
        update(test,player,bot);
    }

    // Closing shit
    getch();
    closegraph();

    return 0;



}
