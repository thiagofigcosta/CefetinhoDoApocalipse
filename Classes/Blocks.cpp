#include "Blocks.hpp"

Blocks::Blocks(int type,nTPoint pos,nTPoint size) {
    this->type=type;
    this->pos=pos;
    this->size=size;
    if(type>250&&type<=300)
        moveSpeed=10*((type-250)*0.6);
    if(type>200&&type<=250)
        moveSpeed=10*((type-200)*0.6);
    
}

Blocks::Blocks(const Blocks& orig) {
}

Blocks::~Blocks() {
}

nTPoint Blocks::defaultBlockSize=Util::nTPointSet(32,32,0);

GLuint Blocks::getTextureByIndex(){
    //TODO: verifica GL::textures pela textura certa do bloco
    return 0;
}

void Blocks::draw(){
    GL::drawTexture(Util::getCollisionRectangle(pos,size),Util::nTColorSet(1,1,1,1),tex,1);
}

void Blocks::move(int dir,float steeps){
    if(dir==Util::left||dir==Util::right){
      nTPoint tmp;
      tmp.setPoint(pos.x+steeps,pos.y,pos.z);
      if(Map::checkCollision(tmp,size)<3)
        pos=tmp;
      else
          moveSpeed*=-1;
    }else if(dir==Util::up){
      nTPoint tmp;
      tmp.setPoint(pos.x,pos.y-steeps,pos.z);
      if(Map::checkCollision(tmp,size)!=2)
        pos=tmp;
      else
          moveSpeed*=-1;
    }else if(dir==Util::down){
      nTPoint tmp;
      tmp.setPoint(pos.x,pos.y+steeps,pos.z);
      if(Map::checkCollision(tmp,size)!=1)
        pos=tmp;
      else
          moveSpeed*=-1;
    }
}
