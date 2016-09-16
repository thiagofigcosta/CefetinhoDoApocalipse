#include "Map.hpp"

Map::Map() {
}

Map::Map(const Map& orig) {
}

Map::~Map() {
}

vector<vector<int> > Map::currentMap;
vector<void*> Map::staticBlocks;
vector<void*> Map::dynamicBlocks;
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
    dynamicBlocks.clear();
    staticBlocks.clear();
}

int Map::checkCollision(nTPoint pos,nTPoint size){
    //TODO:verifica colisao com o mapa, retorna 0 se nao houver colissao
    //caso haja colisao retorna 1 se for com o chao, 4 se for no lado direito, 3 se for no lado esquerdo e 2 se for em cima
}

void Map::setBlockPos(){
    deleteAllBlocks();
    Blocks *bl;
    for(int i=0;i<currentMap.size();i++){
        for(int j=0;j<currentMap[0].size();j++){
            bl=new Blocks(currentMap[i][j],Util::nTPointSet(Blocks::defaultBlockSize.x*(j+(1/2))+Blocks::defaultBlockSize.x/2,Blocks::defaultBlockSize.y*(i+(1/2))+Blocks::defaultBlockSize.y/2,Blocks::defaultBlockSize.z),Blocks::defaultBlockSize);
            if(Blocks::checkIfBlocksIsDynamic(currentMap[i][j])){
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