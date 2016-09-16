#ifndef SCENES_HPP
#define SCENES_HPP
#include "Util.hpp"
#include "Mechanics.hpp"
#include "Tutorials.hpp"
#include "mapEdit.hpp"
#include "Enemy.hpp"
#include "../Libs/Globals.h"

typedef struct ScenesCAM{
    typedef struct scenesP{    
    short int movingCam;
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
    static const int splash;
    static const int credits;
    static const int pregame;
    static const int options;
    static void drawGame();
    static void drawMapEdit();
    static void drawMenu();
    static void drawSplash();
    static void drawOptions();
    static void drawCredits();
    static void putCameraOnOrigin();
    static void lookAt(nTPoint pos);
    static bool isInTheScreen(nTRectangle collision);
    static Camera camera;
    static bool freeCam;
private:
    friend class Map;
    static bool gameCalled;
    static bool menuCalled;
    static bool optionsCalled;
    static bool splashCalled;
    static bool creditsCalled;
    static bool mapEditCalled;   
    static void setAllCalledFalseExcept(vector<int> except);
    static vector<int> getUnityVector(int value);
};

#endif /* SCENES_HPP */

