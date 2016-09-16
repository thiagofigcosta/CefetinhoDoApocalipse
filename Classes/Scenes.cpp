#include "Scenes.hpp"


Scenes::Scenes() {
}

Scenes::Scenes(const Scenes& orig) {
}

Scenes::~Scenes() {
}

int Scenes::current=6516;
const int Scenes::game=6516;
bool Scenes::gameCalled=false;
Camera Scenes::camera;

vector<int> Scenes::getUnityVector(int value){
    vector<int> out;
    out.push_back(value);
    return out;
}

void Scenes::setAllCalledFalseExcept(vector<int> except){
    gameCalled=false;
    for(int i=0;i<except.size();i++)
        switch(except[i]){
            case game: gameCalled=true; break;
        }
}
void Scenes::drawGame(){
    GL::framesInGame++;
    if(!gameCalled){//acontece na primeira vez
        GL::framesInGame=0;
        Map::changeCurrentMap(maps[0]);
        setAllCalledFalseExcept(getUnityVector(game));//fala que ja chamou essa cena
    }
    gluLookAt(camera.moveSpeed*camera.x.movingCam,camera.moveSpeed*camera.y.movingCam,0,camera.moveSpeed*camera.x.movingCam,camera.moveSpeed*camera.y.movingCam,-1,0,1,0);
    if(camera.x.movingCam)
        camera.x.movedCam+=camera.moveSpeed*camera.x.movingCam;
    if(camera.y.movingCam)
        camera.y.movedCam+=camera.moveSpeed*camera.y.movingCam;
    world->applyGravity();
    world->applyForce();
    Map::refresh();
    Map::draw();
    player->draw(Util::nTColorSet(1,1,1,1));
}