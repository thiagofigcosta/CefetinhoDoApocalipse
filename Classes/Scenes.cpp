#include "Scenes.hpp"


Scenes::Scenes() {
}

Scenes::Scenes(const Scenes& orig) {
}

Scenes::~Scenes() {
}

int Scenes::current=6516;
const int Scenes::mapEdit=98746;
const int Scenes::menu=-565;
const int Scenes::game=6516;
bool Scenes::menuCalled=false;
bool Scenes::gameCalled=false;
bool Scenes::mapEditCalled=false;
bool Scenes::freeCam=true;
Camera Scenes::camera;

vector<int> Scenes::getUnityVector(int value){
    vector<int> out;
    out.push_back(value);
    return out;
}

void Scenes::putCameraOnOrigin(){
    gluLookAt(camera.x.movedCam*-1,camera.y.movedCam*-1,0,camera.x.movedCam*-1,camera.y.movedCam*-1,-1,0,1,0);
    camera.x.movedCam=0;
    camera.y.movedCam=0;
    gluLookAt(0,0,0,0,0,-1,0,1,0);
}

void Scenes::setAllCalledFalseExcept(vector<int> except){
    gameCalled=false;
    mapEditCalled=false;
    menuCalled=false;
    
    GL::framesInGame=0;
    putCameraOnOrigin();
    for(int i=0;i<except.size();i++)
        switch(except[i]){
            case game: gameCalled=true; break;
            case mapEdit: mapEditCalled=true; break;
            case menu: menuCalled=true; break;
        }
}
void Scenes::drawGame(){
    GL::framesInGame++;
    if(!gameCalled){//acontece na primeira vez      
        Map::changeCurrentMap(maps[0]);
        setAllCalledFalseExcept(getUnityVector(game));//fala que ja chamou essa cena
        zero->refresh(Tutorials::initHelp,GLUT_KEY_UP);
    }
    Scenes::camera.moveSpeed=ABS(player->hSpeed);
    gluLookAt(camera.moveSpeed*camera.x.movingCam,camera.moveSpeed*camera.y.movingCam,0,camera.moveSpeed*camera.x.movingCam,camera.moveSpeed*camera.y.movingCam,-1,0,1,0);
    if(camera.x.movingCam)
        camera.x.movedCam+=camera.moveSpeed*camera.x.movingCam;
    if(camera.y.movingCam)
        camera.y.movedCam+=camera.moveSpeed*camera.y.movingCam;
    world->applyGravity();
    world->applyForce();
    Map::refresh();
    Map::draw();
    zero->draw();
    player->draw(Util::nTColorSet(1,1,1,1));
    if(GL::isPaused)GL::drawPause();
}

void Scenes::drawMapEdit(){
    GL::framesInGame++;
    if(!mapEditCalled){//acontece na primeira vez
        setAllCalledFalseExcept(getUnityVector(mapEdit));//fala que ja chamou essa cena
        mapEdit::reset();
    }
    Scenes::camera.moveSpeed=10;
    gluLookAt(camera.moveSpeed*camera.x.movingCam,camera.moveSpeed*camera.y.movingCam,0,camera.moveSpeed*camera.x.movingCam,camera.moveSpeed*camera.y.movingCam,-1,0,1,0);
    if(camera.x.movingCam)
        camera.x.movedCam+=camera.moveSpeed*camera.x.movingCam;
    if(camera.y.movingCam)
        camera.y.movedCam+=camera.moveSpeed*camera.y.movingCam;
    
    if(fmod(GL::framesInGame,GL::getFPS()/3)==0)
        if(mapEdit::blankField=="")
            mapEdit::blankField="_";
        else
            mapEdit::blankField="";
    if(mapEdit::size.x==0){
        mapEdit::askForSize();   
    }else{
        mapEdit::draw();
    }
}

void Scenes::drawMenu(){
    GL::framesInGame++;
    if(!menuCalled){//acontece na primeira vez
        setAllCalledFalseExcept(getUnityVector(menu));//fala que ja chamou essa cena
    }

}

