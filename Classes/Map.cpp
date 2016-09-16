#include "Map.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "../Libs/Globals.h"
#include "Scenes.hpp"
#include "Blocks.hpp"
#include "Tutorials.hpp"

Map::Map() {
}

Map::Map(const Map& orig) {
}

Map::~Map() {
}

vector<vector<int> > Map::currentMap;
vector<void*> Map::staticBlocks;
vector<void*> Map::dynamicBlocks;
vector<void*> Map::enemies;
int Map::dynamicGLlist;
int Map::staticGLlist;
GLuint Map::background;
nTPoint Map::size;

void Map::changeCurrentMap(nTMap map){
    size.setPoint((map.map[0].size()-2)*Blocks::defaultBlockSize.x,(map.map.size()-2)*Blocks::defaultBlockSize.y,0);
    char buffer[5];
    snprintf(buffer,5,"%d",map.backgroundId);
    string mapID(buffer);
    currentMap.clear();
    currentMap=map.map;
    background=GL::getTextureByName("background"+mapID);
    setBlockPos();
    createStaticGLlist();
    createDynamicGLlist();
}

void Map::draw(){
    glCallList(dynamicGLlist);  
    glCallList(staticGLlist);
}

void Map::deleteAllBlocks(){
    for(int i=0;i<dynamicBlocks.size();i++)
        delete dynamicBlocks[i];
    for(int i=0;i<staticBlocks.size();i++)
        delete staticBlocks[i];
    for(int i=0;i<enemies.size();i++)
        delete enemies[i];
    dynamicBlocks.clear();
    staticBlocks.clear();
    enemies.clear();
}

vector <mapCollision> Map::checkCollision(nTPoint pos,nTPoint size){
    int x32=Blocks::defaultBlockSize.x,x16=x32/2;
    int y32=Blocks::defaultBlockSize.y,y16=y32/2;
    bool c1, c2, c3, c4;
    c1=c2=c3=c4=false;
    int j_sup,j_inf, i_sup, i_inf, i, j;
    nTRectangle tmp, rec;
    nTPoint point, pointPrincipal;
    mapCollision adc;
    vector <nTPoint> vertexs;
    vector <mapCollision> result;
    adc.collision.firstObj=adc.collision.secondObj=adc.blockRef=0;
    result.push_back(adc);
    tmp=Util::getCollisionRectangle(pos,size);
    vertexs=Util::getRetangleVertexs(tmp);
    pos.x=floor(pos.x);
    pos.y=floor(pos.y);
    i_inf=floor(vertexs[0].x/Blocks::defaultBlockSize.x);
    i_sup=floor(vertexs[1].x/Blocks::defaultBlockSize.x);
    j_inf=ceil(vertexs[2].y/Blocks::defaultBlockSize.y);
    j_sup=ceil(vertexs[1].y/Blocks::defaultBlockSize.y);
    pointPrincipal.setPoint(i_inf*y32+y16,j_inf*x32+x16,0);
    if((i_inf>=0 && i_sup>=0 && j_inf>=0 && j_sup>=0) && (vertexs[0].x!=i_inf && vertexs[1].x!=i_sup && vertexs[0].y!=j_sup && vertexs[2].y!=j_inf) ){ // percorre todos os blocos com possível choque
      for(i=i_sup, j=j_inf; j!=j_sup; j++){
        if(j>=0 && j<currentMap.size() && i>=0 && i<currentMap[0].size()){
          point.setPoint(i*y32+y16,j*x32-x16,0);
          if(getBlockReference(point)!=getBlockReference(pos)){
          rec=Util::getCollisionRectangle(point,Blocks::defaultBlockSize);
          if(Blocks::checkIfBlocksIsMassive(getIdByPosition(point))){
            adc.collision=Mechanics::getCollision(tmp,rec);
            adc.blockRef=getBlockReference(point);
            if(result[0].collision.firstObj==0)
              result.clear();
            if(adc.collision.firstObj!=0 && adc.collision.secondObj!=0){
              result.push_back(adc);
            }
            }
          }
      }
      }
      for( i=i_sup, j=j_sup; i!=i_inf-1; i--){
        if(j>=0 && j<currentMap.size() && i>=0 && i<currentMap[0].size()){
          point.setPoint(i*y32+y16,j*x32-x16,0);
          if(getBlockReference(point)!=getBlockReference(pos)){
          rec=Util::getCollisionRectangle(point,Blocks::defaultBlockSize);
          if(Blocks::checkIfBlocksIsMassive(getIdByPosition(point))){
            adc.collision=Mechanics::getCollision(tmp,rec);
            adc.blockRef=getBlockReference(point);
            if(result[0].collision.firstObj==0)
              result.clear();
            if(adc.collision.firstObj!=0 && adc.collision.secondObj!=0){
              result.push_back(adc);
            }
            }
          }
      }
      }
      for( j=j_sup, i=i_inf+1; j!=j_inf; j--){
        if(j>=0 && j<currentMap.size() && i>=0 && i<currentMap[0].size()){
          point.setPoint(i*y32+y16,j*x32-x16,0);
          if(getBlockReference(point)!=getBlockReference(pos)){
          rec=Util::getCollisionRectangle(point,Blocks::defaultBlockSize);
          if(Blocks::checkIfBlocksIsMassive(getIdByPosition(point))){
            adc.collision=Mechanics::getCollision(tmp,rec);
            adc.blockRef=getBlockReference(point);
            if(result[0].collision.firstObj==0)
              result.clear();
            if(adc.collision.firstObj!=0 && adc.collision.secondObj!=0){
              result.push_back(adc);
            }
            }
          }
        }
      }
      for( i=i_inf-1, j=j_inf; i!=i_sup; i++){
        if(j>=0 && j<currentMap.size() && i>=0 && i<currentMap[0].size()){
          point.setPoint(i*y32+y16,j*x32-x16,0);
          if(getBlockReference(point)!=getBlockReference(pos)){
          rec=Util::getCollisionRectangle(point,Blocks::defaultBlockSize);
        if(Blocks::checkIfBlocksIsMassive(getIdByPosition(point))){
          adc.collision=Mechanics::getCollision(tmp,rec);
          adc.blockRef=getBlockReference(point);
          if(result[0].collision.firstObj==0)
            result.clear();
          if(adc.collision.firstObj!=0 && adc.collision.secondObj!=0){
            result.push_back(adc);
          }
        }
          }
        }
      }
    }
      return result;
}

void Map::refresh(){
    if(GL::isPaused||Tutorials::isPaused)
        return;
    Blocks *bl;
    for(int i=0;i<dynamicBlocks.size();i++){
        bl=(Blocks*)dynamicBlocks[i];
        if(bl->type>250&&bl->type<=300)
            bl->move(Util::up,bl->moveSpeed/GL::getFPS());
        if(bl->type>200&&bl->type<=250)
            bl->move(Util::left,bl->moveSpeed/GL::getFPS());
    }
    //TODO:outras alteracoes de mapa
    createDynamicGLlist();
}

void Map::setBlockPos(){
    deleteAllBlocks();
    Blocks *bl;
    Enemy *en;
    for(int i=0;i<currentMap.size();i++){
        for(int j=0;j<currentMap[0].size();j++){
            bl=new Blocks(currentMap[i][j],Util::nTPointSet(Blocks::defaultBlockSize.x*(j+(1/2))+Blocks::defaultBlockSize.x/2,Blocks::defaultBlockSize.y*(i+(1/2))+Blocks::defaultBlockSize.y/2,Blocks::defaultBlockSize.z),Blocks::defaultBlockSize);
            if(Blocks::checkIfBlocksIsDynamic(currentMap[i][j])){
                if(currentMap[i][j]==1000){
                    bl->pos.z=0.99;
                    player->spawn(bl->pos,5);//TODO:colocar default life aqui
                }else if(currentMap[i][j]>=2000&&currentMap[i][j]<=3000){
                    bl->pos.z=0.99;
                    en=new Enemy(currentMap[i][j]-2000,5,bl->pos,Util::nTPointSet(16,48,0),Entity::getAnimationVector(enemyAnim[0],enemyAnimSize[0]),0);//TODO:definir vida do inimgo,tamanho
                    enemies.push_back(en);
                }else if(currentMap[i][j]>5000){
                    //TODO:spawn de boss
                }else dynamicBlocks.push_back(bl);
            }else if(currentMap[i][j]!=0){
                staticBlocks.push_back(bl);
            }
        }
    }
}

void Map::createDynamicGLlist(){
    glNewList(dynamicGLlist,GL_COMPILE);
    Blocks* bl;
    GL::drawTexture(Util::nTRectangleSet(Scenes::camera.x.movedCam,GL::defaultSize.y+Scenes::camera.y.movedCam,GL::defaultSize.x+Scenes::camera.x.movedCam,Scenes::camera.y.movedCam,-0.9,-0.9),Util::nTColorSet(1,1,1,1),background,1);
    for(int i=0;i<dynamicBlocks.size();i++){
        bl=(Blocks*)dynamicBlocks[i];
        bl->draw();
    }
    glEndList();
}

void Map::createStaticGLlist(){
    glNewList(staticGLlist,GL_COMPILE);
    Blocks* bl;
    for(int i=0;i<staticBlocks.size();i++){
        bl=(Blocks*)staticBlocks[i];
        bl->draw();
    }
    glEndList();
}

int Map::getBlockReference(nTPoint pos){
  Blocks* bl;
  for(int i=0; i<staticBlocks.size(); i++){
    bl=(Blocks*)staticBlocks[i];
    if(bl->pos.x==pos.x && bl->pos.y==pos.y)
      return i;
  }
  for(int i=0; i<dynamicBlocks.size(); i++){
    bl=(Blocks*)dynamicBlocks[i];
    if(bl->pos.x==pos.x && bl->pos.y==pos.y)
      return i+staticBlocks.size();
  }
  return -1;
}

int Map::getIdByPosition(nTPoint pos){
  Blocks* bl;
  for(int i=0; i<staticBlocks.size(); i++){
    bl=(Blocks*)staticBlocks[i];
    if(bl->pos.x==pos.x && bl->pos.y==pos.y){
      return bl->type;
    }
  }
  for(int i=0; i<dynamicBlocks.size(); i++){
    bl=(Blocks*)dynamicBlocks[i];
    if(bl->pos.x==pos.x && bl->pos.y==pos.y){
      return bl->type;
    }
  }
  return 0;
}