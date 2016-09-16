#ifndef SCENES_HPP
#define SCENES_HPP
#include "Util.hpp"
#include "Mechanics.hpp"
#include "Tutorials.hpp"
#include "mapEdit.hpp"
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
    static const int menu;
    static const int mapEdit;
    static void drawGame();
    static void drawMapEdit();
    static void drawMenu();
    static void putCameraOnOrigin();
    static Camera camera;
    static bool freeCam;
private:
    static bool gameCalled;
    static bool menuCalled;
    static bool mapEditCalled;
    static void setAllCalledFalseExcept(vector<int> except);
    static vector<int> getUnityVector(int value);
};

#endif /* SCENES_HPP */

