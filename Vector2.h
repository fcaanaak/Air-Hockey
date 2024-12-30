#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>

// A class to represent a 2 dimensional vector
class Vector2{

private:
    float x;
    float y;

public:

    Vector2(float _x, float _y){
        x = _x;
        y = _y;
    }

    Vector2(){
        x = 0;
        y = 0;
    }

    // returns the magnitude of the vector
    float norm(){
        return sqrt(x*x+y*y);
    }

    Vector2 getUnitVector(){

        Vector2 unitVector(x/norm(), y/norm());

        return unitVector;
    }

    // Return the unit x and y vectors

    // formally unit_x and unit_y
    float xDirection(){
        return x/abs(x);
    }

    float yDirection(){
        return y/abs(y);
    }

    float getAngle(){
        return atan2(y,x);
    }

    float getX(){
        return x;
    }

    float getY(){
        return y;
    }

    void setX(float xValue){
        x = xValue;
    }

    void setY(float yValue){
        y = yValue;
    }

    void incrementX(float xValue){
        x += xValue;
    }

    void incrementY(float yValue){
        y += yValue;
    }


};


#endif // VECTOR2_H_INCLUDED
