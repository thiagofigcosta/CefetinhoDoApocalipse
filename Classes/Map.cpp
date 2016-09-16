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
int Map::dynamicGLlist=glGenLists(1);
int Map::staticGLlist=glGenLists(1);

void Map::changeCurrentMap(int **map,int rows,int columns){
    currentMap.clear();
    vector<int> tmp;
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            tmp.push_back(map[i][j]);
        }
        currentMap.push_back(tmp);
        tmp.clear();
    }
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
        for(int j=0;j<currentMap[i].size();j++){
            bl=new Blocks(currentMap[i][j],Util::nTPointSet(Blocks::defaultBlockSize.x*(i+(1/2)),Blocks::defaultBlockSize.y*(j+(1/2)),Blocks::defaultBlockSize.z),Blocks::defaultBlockSize);
            if(currentMap[i][j]>200&&currentMap[i][j]<=300){
                dynamicBlocks.push_back(bl);
            }else{
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