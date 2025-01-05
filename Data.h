#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

class Data{


public:

    static const int windowWidth = 800;
    static const int windowHeight = 800;

    static constexpr float friction = 0.07;

    static const int botSpeed = 15;

    static constexpr float fps = 100/6; // 60 fps

    static float c_to_scrn(float point){
        return point + Data::windowWidth/2.0;
    }



};


#endif // DATA_H_INCLUDED
