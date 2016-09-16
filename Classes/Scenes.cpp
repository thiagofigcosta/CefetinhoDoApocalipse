#include "Scenes.hpp"


Scenes::Scenes() {
}

Scenes::Scenes(const Scenes& orig) {
}

Scenes::~Scenes() {
}

int Scenes::current=-565;
const int Scenes::mapEdit=98746;
const int Scenes::menu=-565;
const int Scenes::game=6516;
const int Scenes::credits=12;
const int Scenes::splash=300;
const int Scenes::options=91;
bool Scenes::menuCalled=false;
bool Scenes::gameCalled=false;
bool Scenes::mapEditCalled=false;
bool Scenes::splashCalled=false;
bool Scenes::optionsCalled=false;
bool Scenes::creditsCalled=false;

bool Scenes::freeCam=false;
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
    splashCalled=false;
    optionsCalled=false;
    creditsCalled=false;
    
    GL::framesInGame=0;
    putCameraOnOrigin();
    for(int i=0;i<except.size();i++)
        switch(except[i]){
            case game: gameCalled=true; break;
            case Scenes::mapEdit: mapEditCalled=true; break;
            case menu: menuCalled=true; break;
            case splash:  splashCalled=true;break;
            case options: optionsCalled=true;break;
            case credits: creditsCalled=true;break;
        }
}
void Scenes::drawGame(){
    if(!gameCalled){//acontece na primeira vez      
        Map::changeCurrentMap(maps[0]);
        setAllCalledFalseExcept(getUnityVector(game));//fala que ja chamou essa cena
        zero->refresh(Tutorials::initHelp,GLUT_KEY_UP);
        GL::isPaused=false;
    }
    if(player->hSpeed>Entity::walkSpeed)
        Scenes::camera.moveSpeed=ABS(player->hSpeed/GL::getFPS());
    else
        Scenes::camera.moveSpeed=ABS(Entity::walkSpeed/GL::getFPS());
    if((player->pos.x>GL::currentSize.x/2*1.11+Scenes::camera.x.movedCam))
        Scenes::camera.x.movingCam=1;
    else if((player->pos.x<GL::currentSize.x/2*0.99+Scenes::camera.x.movedCam)&&(Scenes::camera.x.movedCam>1.11))
        Scenes::camera.x.movingCam=-1;
    else
        Scenes::camera.x.movingCam=0;
    
    if(Map::currentMap.size()>23&&player->pos.y<Map::size.y*1.2){
         if((player->pos.y>GL::currentSize.y/1.5*1.11+Scenes::camera.y.movedCam))
            Scenes::camera.y.movingCam=1;
        else if((player->pos.y<GL::currentSize.y/2*0.99+Scenes::camera.y.movedCam)&&(Scenes::camera.y.movedCam>1.11))
            Scenes::camera.y.movingCam=-1;
        else
            Scenes::camera.y.movingCam=0;
    }else if(!Scenes::freeCam)
            Scenes::camera.y.movingCam=0;
    
    
    gluLookAt(camera.moveSpeed*camera.x.movingCam,camera.moveSpeed*camera.y.movingCam,0,camera.moveSpeed*camera.x.movingCam,camera.moveSpeed*camera.y.movingCam,-1,0,1,0);
    if(camera.x.movingCam)
        camera.x.movedCam+=camera.moveSpeed*camera.x.movingCam;
    if(camera.y.movingCam)
        camera.y.movedCam+=camera.moveSpeed*camera.y.movingCam;
    world->applyGravity();
    world->applyForce();
    Map::refresh();
    Map::draw();
    Enemy::behave();
    zero->draw();
    player->draw(Util::nTColorSet(1,1,1,1));
    if(GL::isPaused)GL::drawPause();
}

void Scenes::drawMapEdit(){
    if(!mapEditCalled){//acontece na primeira vez
        setAllCalledFalseExcept(getUnityVector(Scenes::mapEdit));//fala que ja chamou essa cena
        mapEdit::reset();
        Scenes::camera.moveSpeed=10;
    }    
    if(mapEdit::size.x==0){
        if(fmod(GL::framesInGame,GL::getFPS()/3)==0)
        if(mapEdit::blankField=="")
            mapEdit::blankField="_";
        else
            mapEdit::blankField="";
        
        if(mapEdit::isCreating==0){
            GL::setFontByIndex(0);
            GL::drawText(Util::nTPointSet(100,50,1),"Digite a patir de onde voce ira editar o mapa",GL::getColorByName("violet"));
            if(GL::buttonBehave(Util::nTRectangleSet(100,300,200,200,0,0),GL::getColorByName("mouseSelected"),GL::getTextureByName("Pedra"),NULL,NULL,NULL,NULL))
                mapEdit::isCreating=-1;
            if(GL::buttonBehave(Util::nTRectangleSet(400,300,500,200,0,0),GL::getColorByName("mouseSelected"),GL::getTextureByName("Gelo"),NULL,NULL,NULL,NULL))
                mapEdit::isCreating=1;
            if(GL::buttonBehave(Util::nTRectangleSet(300,500,400,400,0,0),GL::getColorByName("mouseSelected"),GL::getTextureByName("Gelo"),NULL,NULL,NULL,NULL))
                current=menu;
        }else if(mapEdit::isCreating==1){
            mapEdit::askForSize();
            if(GL::buttonBehave(Util::nTRectangleSet(400,500,500,400,0,0),GL::getColorByName("mouseSelected"),GL::getTextureByName("Gelo"),NULL,NULL,NULL,NULL))
                mapEdit::isCreating=0;
        }else if(mapEdit::isCreating==-1){
            mapEdit::askForLoad();
            if(GL::buttonBehave(Util::nTRectangleSet(400,500,500,400,0,0),GL::getColorByName("mouseSelected"),GL::getTextureByName("Gelo"),NULL,NULL,NULL,NULL))
                mapEdit::isCreating=0;
        }
    }else{
        gluLookAt(camera.moveSpeed*camera.x.movingCam,camera.moveSpeed*camera.y.movingCam,0,camera.moveSpeed*camera.x.movingCam,camera.moveSpeed*camera.y.movingCam,-1,0,1,0);
        if(camera.x.movingCam)
            camera.x.movedCam+=camera.moveSpeed*camera.x.movingCam;
        if(camera.y.movingCam)
            camera.y.movedCam+=camera.moveSpeed*camera.y.movingCam;
        mapEdit::draw();
    }
}

void Scenes::drawMenu(){
    if(!menuCalled){//acontece na primeira vez
        setAllCalledFalseExcept(getUnityVector(menu));//fala que ja chamou essa cena
    }
    // bool GL::buttonBehave(nTRectangle collision,nTColor pressedColor,GLuint tex,void(*clickFunction)(int,int),void(*releaseFunction)(int,int)){
    // nTRectangle Util::nTRectangleSet(float x0,float y0,float x1,float y1,float z0,float z1){
    GL::drawTexture(Util::nTRectangleSet(0,GL::defaultSize.y,GL::defaultSize.x,0,-0.9,-0.9),Util::nTColorSet(0.4,0.4,0.4,1),GL::getTextureByName("background0"),1);
    if(GL::buttonBehave(Util::nTRectangleSet(350,362+10,450,330,0.4,0.4),Util::nTColorSet(0.4,0.4,0.4,1),GL::getTextureByName("playIcon"),NULL,NULL,NULL,NULL))
      Scenes::current=game;
    if(GL::buttonBehave(Util::nTRectangleSet(250,404+10,550,372,0.4,0.4),Util::nTColorSet(0.4,0.4,0.4,1),GL::getTextureByName("mapEditIcon"),NULL,NULL,NULL,NULL))
      Scenes::current=mapEdit;
    if(GL::buttonBehave(Util::nTRectangleSet(340,446+10,460,414,0.4,0.4),Util::nTColorSet(0.4,0.4,0.4,1),GL::getTextureByName("optionsIcon"),NULL,NULL,NULL,NULL))
      Scenes::current=menu;
    if(GL::buttonBehave(Util::nTRectangleSet(360,488+10,440,456,0.4,0.4),Util::nTColorSet(0.4,0.4,0.4,1),GL::getTextureByName("quitIcon"),NULL,NULL,NULL,NULL))
      exit(0);
      if(GL::buttonBehave(Util::nTRectangleSet(57,557+23,2*57+23,500,0.4,0.4),Util::nTColorSet(0.4,0.4,0.4,1),GL::getTextureByName("cefetLogo"),NULL,NULL,NULL,NULL))
        Scenes::current=menu;
        if(GL::buttonBehave(Util::nTRectangleSet(3*57+190,557+23,4*57+23+190,500,0.4,0.4),Util::nTColorSet(0.4,0.4,0.4,1),GL::getTextureByName("decomLogo"),NULL,NULL,NULL,NULL))
          Scenes::current=menu;
          if(GL::buttonBehave(Util::nTRectangleSet(5*57+400,557+23,6*57+23+400,500,0.4,0.4),Util::nTColorSet(0.4,0.4,0.4,1),GL::getTextureByName("theCOM"),NULL,NULL,NULL,NULL))
            Scenes::current=menu;
    // void GL::drawTexture(nTRectangle pos,nTColor color,GLuint tex,int Orientation){
    // GL::drawTexture(Util::nTRectangleSet(0,315,400,465,0.4,0.4),GL::getColorByName("white"),GL::getTextureByName("decomCelebrations"),1);
    GL::drawTexture(Util::nTRectangleSet(100,300,700,0,0.4,0.4),GL::getColorByName("white"),GL::getTextureByName("legendsLogo"),1);
}

void Scenes::drawOptions(){

}

void Scenes::drawCredits(){

}

void Scenes::drawSplash(){

}

bool Scenes::isInTheScreen(nTRectangle collision){
    bool out=false;
    nTPoint offSet;
    offSet.setPoint(GL::defaultSize.x*0.2,GL::defaultSize.y*0.3,0);
    if(camera.x.movedCam-offSet.x<=collision.p0.x&&collision.p0.x<GL::defaultSize.x+camera.x.movedCam+offSet.x)
        if(camera.y.movedCam-offSet.y<=collision.p0.y&&collision.p0.y<GL::defaultSize.y+camera.y.movedCam+offSet.y)
            out=true;
    if(camera.x.movedCam-offSet.x<=collision.p1.x&&collision.p1.x<GL::defaultSize.x+camera.x.movedCam+offSet.x)
        if(camera.y.movedCam-offSet.y<=collision.p0.y&&collision.p0.y<GL::defaultSize.y+camera.y.movedCam+offSet.y)
            out=true;
    if(camera.x.movedCam-offSet.x<=collision.p1.x&&collision.p1.x<GL::defaultSize.x+camera.x.movedCam+offSet.x)
        if(camera.y.movedCam-offSet.y<=collision.p1.y&&collision.p1.y<GL::defaultSize.y+camera.y.movedCam+offSet.y)
            out=true;
    if(camera.x.movedCam-offSet.x<=collision.p0.x&&collision.p0.x<GL::defaultSize.x+camera.x.movedCam+offSet.x)
        if(camera.y.movedCam-offSet.y<=collision.p1.y&&collision.p1.y<GL::defaultSize.y+camera.y.movedCam+offSet.y)
            out=true;
    return out;
}