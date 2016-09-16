#include "Map.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "../Libs/Globals.h"

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
int Map::currentBackground;

void Map::changeCurrentMap(nTMap map){
    currentMap.clear();
    currentMap=map.map;
    currentBackground=map.backgroundId;
    setBlockPos();
    createStaticGLlist();
    createDynamicGLlist();
}

void Map::draw(){
    GL::setColorByName("black");
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

int Map::checkCollision(nTPoint pos,nTPoint size){
    //TODO:verifica colisao com o mapa, retorna 0 se nao houver colissao
    //caso haja colisao retorna 1 se for com o chao, 4 se for no lado direito, 3 se for no lado esquerdo e 2 se for em cima
}

void Map::refresh(){
    if(GL::isPaused)
        return;
    Blocks *bl;
    for(int i=0;i<dynamicBlocks.size();i++){
        bl=(Blocks*)dynamicBlocks[i];
        if(bl->type>250&&bl->type<=300)
            bl->move(Util::up,bl->moveSpeed*1/GL::getFPS());
        if(bl->type>200&&bl->type<=250)
            bl->move(Util::left,bl->moveSpeed*1/GL::getFPS());
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
                    player->spawn(bl->pos,5);//TODO:colocar default life aqui
                }else if(currentMap[i][j]>=2000&&currentMap[i][j]<=3000){
                    en=new Enemy(currentMap[i][j]-2000,5,bl->pos,Util::nTPointSet(16,48,0),NULL,0);//TODO:definir vida do inimgo,tamanho
                    enemies.push_back(en);
                }else if(currentMap[i][j]>5000){
                    //TODO:spawn de boss
                }else
                dynamicBlocks.push_back(bl);
            }else if(currentMap[i][j]!=0){
                staticBlocks.push_back(bl);
            }
        }
    }
}

void Map::createDynamicGLlist(){
    glNewList(dynamicGLlist,GL_COMPILE);
    Blocks* bl;
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