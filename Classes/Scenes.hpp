#ifndef SCENES_HPP
#define SCENES_HPP
#include "Util.hpp"
#include "Mechanics.hpp"
#include "../Libs/Globals.h"

typedef struct ScenesCAM{
    typedef struct scenesP{    
    int movingCam;
    float movedCam;
    }scenesPoint;
    scenesPoint x;
    scenesPoint y;
    float moveSpeed;
    
    void setCam(float moveSpeed_){
        x.movedCam=0;
        x.movingCam=0;
        y.movedCam=0;
        y.movingCam=0;
        moveSpeed=moveSpeed_;
    };
} Camera;

class Scenes {
public:
    Scenes();
    Scenes(const Scenes& orig);
    virtual ~Scenes();
    static int current;
    static const int game;
    static void drawGame();
    static Camera camera;
private:
    static bool gameCalled;
    static void setAllCaledFalseExcept(vector<int> except);
    static vector<int> getUnityVector(int value);
};

#endif /* SCENES_HPP */

