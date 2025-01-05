#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include <Windows.h>
#include <string>
#include <cstdlib>

#include "Player.h"
#include "Vector2.h"
#include "Puck.h"
#include "Data.h"


/*

    TODO: MAKE CODE MORE MODULAR
    ADD UPDATE FUNCTION TO PLAYER CLASS
    MOVE BOT BEHAVIOR EITHER INTO PLAYER CLASS OR JUST MAKE A BOT CLASS
    ADD A FUNCTION TO THE PUCK CLASS THAT WILL DECREASE ITS SPEED DUE TO FRICTION(COPY WHATS INSIDE OF THE UPDAATE FUNCTION IN THIS FILE)

    FIX THE ERROR THAT MAKES THE BOT COLLECT THE PUCK BACK FROM ITS GOAL

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
        circle(Data::windowWidth/2.0,Data::windowHeight/2.0, 90);


        line(0,Data::windowHeight/2.0,Data::windowWidth/2.0 - 90,Data::windowHeight/2.0);

        line(Data::windowWidth/2.0 + 90,Data::windowHeight/2.0,Data::windowWidth,Data::windowHeight/2.0);

        settextstyle(COMPLEX_FONT, HORIZ_DIR, 0);
        setusercharsize(2,1,2,1);


        outtextxy(Data::windowWidth - textwidth(bot.getScore()), Data::windowHeight/2.0 - textheight(bot.getScore()), bot.getScore());
        outtextxy(Data::windowWidth - textwidth(player.getScore()), Data::windowHeight/2.0, player.getScore());

        // draw the goals
        setfillstyle(EMPTY_FILL,0);
        sector(Data::windowWidth/2.0, Data::windowHeight, 0, 180, Data::windowWidth/4.0, 2*player.getRadius());// players goal
        sector(Data::windowWidth/2.0, 0, 180, 360, Data::windowWidth/4.0, 2*bot.getRadius());// enemies goal

        setcolor(0);
    }

    void movePlayer(int x, int y){

        player.getCurrentPos().setX(x);

        if (y > Data::windowHeight/2.0){
            player.getCurrentPos().setY(y);
        }


    }

public:

    static float c_to_scrn(float point){
        return point + Data::windowWidth/2.0;
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

    return point + Data::windowWidth/2.0;

}




void drawBackground(){

    setcolor(12);

    // Draw the lil ice hockey rink lines
    circle(Data::windowWidth/2.0,Data::windowHeight/2.0, 90);


    line(0,Data::windowHeight/2.0,Data::windowWidth/2.0 - 90,Data::windowHeight/2.0);

    line(Data::windowWidth/2.0 + 90,Data::windowHeight/2.0,Data::windowWidth,Data::windowHeight/2.0);

    settextstyle(COMPLEX_FONT, HORIZ_DIR, 0);
    setusercharsize(2,1,2,1);
    outtextxy(Data::windowWidth - textwidth("2"), Data::windowHeight/2.0 - textheight("2"), "2");
    outtextxy(Data::windowWidth - textwidth("3"), Data::windowHeight/2.0, "3");

    // draw the goals
    setfillstyle(EMPTY_FILL,0);
    sector(Data::windowWidth/2.0, Data::windowHeight, 0, 180, Data::windowWidth/4.0, 120);// players goal
    sector(Data::windowWidth/2.0, 0, 180, 360, Data::windowWidth/4.0, 120);// enemies goal

    setcolor(0);
}



// UPDATE FUNCTION
void update(Puck &puck,Player &player,Player &bot){


    drawBackground();

    // Draw the circle
    //circle(c_to_scrn(puck.getCurrentPos().getX()),c_to_scrn(puck.getCurrentPos().getY()),puck.getRadius());
    puck.draw();


    // Shit to do with the player puck hitting thing
    player.getCurrentPos().setX(mousex());


    // Stop the player from moving their mouse to the
    // other half of the screen (not their side >:( )
    if (mousey() > Data::windowHeight/2.0){
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

    /*
    // Add acceleration to velocity
    puck.getVelocity().setX(puck.getVelocity().getX() + puck.getAcceleration().getX());
    puck.getVelocity().setY(puck.getVelocity().getY() - puck.getAcceleration().getY());

    // Add velocity to position
    puck.getCurrentPos().setX( puck.getCurrentPos().getX() + puck.getVelocity().getX() );
    puck.getCurrentPos().setY( puck.getCurrentPos().getY() - puck.getVelocity().getY() );
    */

    // Moving the bot
    bot.getCurrentPos().incrementX(bot.getVelocity().getX());
    bot.getCurrentPos().incrementY(bot.getVelocity().getY());

    // WORK ON THIS, BOT MOVEMENT LOGIC

    // If the puck is to the right of the bot, move right
    if (puck.getCurrentPos().getX() > bot.getCurrentPos().getX() + bot.getRadius() - Data::windowWidth/2.0){
        bot.getVelocity().setX(Data::botSpeed);
    }

    // If the puck is to the left of the bot, move right
    else if (puck.getCurrentPos().getX() < bot.getCurrentPos().getX()-bot.getRadius() - Data::windowWidth/2.0){
        bot.getVelocity().setX(-Data::botSpeed);
    }

    // If the puck is above the center of the screen, move down
    if (puck.getCurrentPos().getY() < 0){
        bot.getVelocity().setY(Data::botSpeed);
    }

    // If the puck is on the players side of the screen, retreat back
    else if (puck.getCurrentPos().getY() > 0 && bot.getCurrentPos().getY() > bot.getRadius()){
        bot.getVelocity().setY(-Data::botSpeed);
    }



    else{bot.getVelocity().setY(0);}

    if (puck.getCurrentPos().getY() < bot.getCurrentPos().getY()-Data::windowHeight/2.0){
        bot.getVelocity().setY(-Data::botSpeed);
    }

    /*
    player_hit_detect(player,puck,false);
    player_hit_detect(bot,puck,true);
    */
    player.checkCollision(puck);
    bot.checkCollision(puck);

    puck.update();


    // Frame delay for animation
    delay(100/6);
    global_time += 100/6.0;


    player.getLastPos().setX(player.getCurrentPos().getX());
    player.getLastPos().setY(player.getCurrentPos().getY());

    if (abs(puck.getVelocity().getX()) > 0){
        puck.getVelocity().incrementX(-(puck.getVelocity().getX() * Data::friction));
    }

    if (abs(puck.getVelocity().getY()) > 0){

        puck.getVelocity().incrementY(-(puck.getVelocity().getY() * Data::friction));
    }

    // Clear screen
    clearviewport();
}


int main(){

    int gd = DETECT, gm;

    initwindow(Data::windowWidth,Data::windowHeight);

    setbkcolor(11);

    Puck test(30,50,0);

    Player player(60,6,20,false);

    Player bot(60,6,20,true);
    bot.getCurrentPos().setX(Data::windowWidth/2.0);
    bot.getCurrentPos().setY(bot.getRadius());

    while (true){
        update(test,player,bot);
    }

    // Closing shit
    getch();
    closegraph();

    return 0;



}
