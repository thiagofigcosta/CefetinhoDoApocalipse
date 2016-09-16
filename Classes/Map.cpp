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

void Map::changeCurrentMap(int **map,int rows,int columns){
    //TODO: converte o mapa[][] em vector<vector<int>>mapa
}

void Map::drawMap(){
    //TODO: desenha o mapa na cena
}

void Map::deleteAllBlocks(){
    //TODO:destruir todos os blocos criados;
}

int Map::checkCollisionWithMap(nTPoint pos,nTPoint size){
    //TODO:verifica colisao com o mapa, retorna 0 se nao houver colissao
    //caso haja colisao retorna 1 se for com o chao, 4 se for no lado direito, 3 se for no lado esquerdo e 2 se for em cima
}

void Map::updateBlockPos(){
    //TODO:percorre os blocos dinamicos e atualiza a posicao deles
}