#ifndef VECTOR2_H_INCLUDED
#define VECTOR2_H_INCLUDED

// A class to represent a 2 dimensional vector
class Vector2{

    public:

    float innerVect[2];

    float x = innerVect[0];
    float y = innerVect[1];

    // returns the magnitude of the vector
    float norm(){
        return sqrt(x*x+y*y);
    }


    // Return the unit x and y vectors
    float unit_x(){
        return x/abs(x);
    }

    float unit_y(){
        return y/abs(y);
    }

};


#endif // VECTOR2_H_INCLUDED
