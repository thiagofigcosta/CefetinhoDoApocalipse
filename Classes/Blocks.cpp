#include "Blocks.hpp"

Blocks::Blocks(int type,nTPoint pos,nTPoint size) {
    this->type=type;
    this->pos=pos;
    this->size=size;
    moveSpeed=10;//TODO:talvez variar a velocidade de acordo com id do Bloco
}

Blocks::Blocks(const Blocks& orig) {
}

Blocks::~Blocks() {
}

GLuint Blocks::getTextureByIndex(){
    //TODO: verifica GL::textures pela textura certa do bloco
    return 0;
}

void Blocks::draw(){
    //TODO:funcao que desenha o bloco de acordo com posicao e textura
}

void Blocks::move(string dir,float steeps){
    //TODO:inverter moveSpeed caso tenha alguma colisao
    if(dir=="left"||dir=="right"){
      nTPoint tmp;
      tmp.setPoint(pos.x+steeps,pos.y,pos.z);
      if(Map::checkCollisionWithMap(tmp,size)<3)
        pos=tmp;
    }else if(dir=="up"){
      nTPoint tmp;
      tmp.setPoint(pos.x,pos.y-steeps,pos.z);
      if(Map::checkCollisionWithMap(tmp,size)!=2)
        pos=tmp;
    }else if(dir=="down"){
      nTPoint tmp;
      tmp.setPoint(pos.x,pos.y+steeps,pos.z);
      if(Map::checkCollisionWithMap(tmp,size)!=1)
        pos=tmp;
    }
}
