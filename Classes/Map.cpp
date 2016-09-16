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
vector<vector<nTReferences> >Map::blockReference;
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
    //caso haja colisao retorna 1 se for com o chao, 4 se for no lado direito, 3 se for no lado esquerdo e 2 se for em cima
    bool c1, c2, c3, c4;
    c1=c2=c3=c4=false;
    int j_sup,j_inf, i_sup, i_inf, i, j;
    nTRectangle tmp, tmp2;
    mapCollision adc;
    vector <nTPoint> vertexs;
    vector <mapCollision> result;
    adc.collision.firstObj=adc.collision.secondObj=adc.blockRef=0;
    result.push_back(adc);

    tmp=Util::getCollisionRectangle(pos,size);
    vertexs=Util::getRetangleVertexs(tmp);

    i_inf=floor(vertexs[0].x/Blocks::defaultBlockSize.x);
    i_sup=floor(vertexs[1].x/Blocks::defaultBlockSize.x);
    j_sup=floor(vertexs[2].y/Blocks::defaultBlockSize.y);
    j_inf=floor(vertexs[1].y/Blocks::defaultBlockSize.y);
    cout<<"x = "<<i_inf<<" x = "<<i_sup<<"\n"<<"y = "<<j_inf<<" y = "<<j_sup<<endl;
    //cout<<"currentMap.size() = "<<currentMap.size()<<" currentMap[0].size() = "<<currentMap[0].size()<<"\n";
    if(i_inf!=i_sup || j_sup!=j_inf){ // percorre todos os blocos com possível choque
      for(i=i_sup, j=j_sup; j!=j_inf; j--){
        if(j>=0 && j<currentMap.size() && i>=0 && i<currentMap[0].size()){
          if(Blocks::checkIfBlocksIsMassive(blockReference[j][i].type)){
            adc.collision=Mechanics::getCollision(tmp,(blockReference[j][i]).rectangle);
            adc.blockRef=getBlockReference((blockReference[j][i]).centro);
            if(result[0].collision.firstObj==0)
              result.clear();
            if(adc.collision.firstObj!=0 && adc.collision.secondObj!=0)
              result.push_back(adc);
            }
            //cout<<"Primeiro\n";
      }
      }
      for( ; i!=i_inf; i--){
        if(j>=0 && j<currentMap.size() && i>=0 && i<currentMap[0].size()){
          if(Blocks::checkIfBlocksIsMassive(blockReference[j][i].type)){
            adc.collision=Mechanics::getCollision(tmp,(blockReference[j][i]).rectangle);
            adc.blockRef=getBlockReference((blockReference[j][i]).centro);
            if(result[0].collision.firstObj==0)
              result.clear();
            if(adc.collision.firstObj!=0 && adc.collision.secondObj!=0)
              result.push_back(adc);
            }
      }
      }
      for( ; j!=j_sup; j++){
        if(j>=0 && j<currentMap.size() && i>=0 && i<currentMap[0].size()){
          if(Blocks::checkIfBlocksIsMassive(blockReference[j][i].type)){
            adc.collision=Mechanics::getCollision(tmp,(blockReference[j][i]).rectangle);
            adc.blockRef=getBlockReference((blockReference[j][i]).centro);
            if(result[0].collision.firstObj==0)
              result.clear();
            if(adc.collision.firstObj!=0 && adc.collision.secondObj!=0)
              result.push_back(adc);
            }
        }
      }
      for( ; i!=i_sup; i++){
        if(j>=0 && j<currentMap.size() && i>=0 && i<currentMap[0].size()){
        if(Blocks::checkIfBlocksIsMassive(blockReference[j][i].type)){
          adc.collision=Mechanics::getCollision(tmp,(blockReference[j][i]).rectangle);
          adc.blockRef=getBlockReference((blockReference[j][i]).centro);
          if(result[0].collision.firstObj==0)
            result.clear();
          if(adc.collision.firstObj!=0 && adc.collision.secondObj!=0)
            result.push_back(adc);
          }
        }
      }
    }
    for(int i=0; i<result.size(); i++){
      cout<<"firstObj = "<< result[i].collision.firstObj<<" secondObj = "<< result[i].collision.secondObj<<" blockRef = "<< result[i].blockRef<<endl;
    }
    cout<<"end\n";
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
    nTReferences teste;
    vector<nTReferences> v1;
    vector<vector<nTReferences> > matrixAux;
    matrixAux.clear();
    //cout<<"linhas = "<<currentMap.size()<<" colunas = "<<currentMap[0].size()<<"\n";
    for(int i=0;i<currentMap.size();i++){
        for(int j=0;j<currentMap[0].size();j++){
            bl=new Blocks(currentMap[i][j],Util::nTPointSet(Blocks::defaultBlockSize.x*(j+(1/2))+Blocks::defaultBlockSize.x/2,Blocks::defaultBlockSize.y*(i+(1/2))+Blocks::defaultBlockSize.y/2,Blocks::defaultBlockSize.z),Blocks::defaultBlockSize);
            if(Blocks::checkIfBlocksIsDynamic(currentMap[i][j])){
                if(currentMap[i][j]==1000){
                    player->spawn(bl->pos,5);//TODO:colocar default life aqui
                }else if(currentMap[i][j]>=2000&&currentMap[i][j]<=3000){
                    en=new Enemy(currentMap[i][j]-2000,5,bl->pos,Util::nTPointSet(16,48,0),Entity::getAnimationVector(enemyAnim[0],enemyAnimSize[0]),0);//TODO:definir vida do inimgo,tamanho
                    enemies.push_back(en);
                }else if(currentMap[i][j]>5000){
                    //TODO:spawn de boss
                }else{
                    dynamicBlocks.push_back(bl);
                }
            }else if(currentMap[i][j]!=0){
                staticBlocks.push_back(bl);
            }
            //                    teste.setMatrix(bl->pos, currentMap[i][j],Util::nTPointSet(i*32,j*32,0),Util::nTPointSet((i+1)*32,(j+1)*32,0));//i por j
        teste.setMatrix(bl->pos, currentMap[i][j],Util::nTPointSet(j*32,i*32,0),Util::nTPointSet((j+1)*32,(i+1)*32,0));//i por j
        v1.push_back(teste);
        }
        matrixAux.push_back(v1);
        v1.clear();
    }
    blockReference=matrixAux;
}

void Map::createDynamicGLlist(){
    glNewList(dynamicGLlist,GL_COMPILE);
    Blocks* bl;
    GL::drawTexture(Util::nTRectangleSet(Scenes::camera.x.movedCam,Scenes::camera.y.movedCam,GL::defaultSize.x+Scenes::camera.x.movedCam,GL::defaultSize.y+Scenes::camera.y.movedCam,-0.9,-0.9),Util::nTColorSet(1,1,1,1),background,1);
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
    bl=(Blocks*)staticBlocks[i];
    if(bl->pos.x==pos.x && bl->pos.y==pos.y)
      return i+staticBlocks.size();
  }
}