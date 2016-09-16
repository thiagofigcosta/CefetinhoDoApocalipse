#include "Mechanics.hpp"

Mechanics::Mechanics(){
};

Mechanics::Mechanics(const Mechanics& orig) {
}

Mechanics::~Mechanics() {
}

float Mechanics::gravity=-10;
vector<void*> Mechanics::players;
vector<void*> Mechanics::enemys;

void Mechanics::applyGravity(){
    if(GL::isPaused)
        return;
    /*//TODO:(thiago*)descomentar
    Player *pl;
    for(int i=0;i<players.size();i++){
        pl=(Player*)players[i];
        if(!checkNormalForce(pl->pos,pl->size)){
            pl->vSpeed+=gravity*(1/GL::getFPS());
        }else if((pl->vSpeed<0&&gravity<0)||(pl->vSpeed>0&&gravity>0)){
            pl->vSpeed=0;
        }
    }
    Enemy *en;
    for(int i=0;i<enemys.size();i++){
        en=(Enemy*)enemys[i];
        if(!checkNormalForce(en->pos,en->size)){
            en->vSpeed+=gravity*(1/GL::getFPS());
        }else if((en->vSpeed<0&&gravity<0)||(en->vSpeed>0&&gravity>0)){
            en->vSpeed=0;
        }
    }*/
}

void Mechanics::applyForce(){
    if(GL::isPaused)
        return;
    /*//TODO:(thiago*)descomentar
    Player *pl;
    for(int i=0;i<players.size();i++){
        pl=(Player*)players[i];
        if(pl->hSpeed!=0){
            pl->move("left",hSpeed*1/GL::getFPS());
        }
        if(pl->vSpeed<0){
            pl->move("down",vSpeed*1/GL::getFPS());
        }else if(pl->vSpeed>0){
            pl->move("up",vSpeed*1/GL::getFPS());
        }
    }
    Enemy *en;
    for(int i=0;i<enemys.size();i++){
        en=(Enemy*)enemys[i];
        if(en->hSpeed!=0){
            en->move("left",hSpeed*1/GL::getFPS());
        }
        if(en->vSpeed<0){
            en->move("down",vSpeed*1/GL::getFPS());
        }else if(en->vSpeed>0){
            en->move("up",vSpeed*1/GL::getFPS());
        }
    }*/
}

void Mechanics::move(string dir,float steeps){
    //TODO:se o bloco for liquido ou dano fazer algo
    //TODO:se o bloco for de power up liberar o powerup
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

bool Mechanics::checkNormalForce(nTPoint pos_,nTPoint size_){
    switch(Map::checkCollisionWithMap(pos_,size_)){
        case 1: return true;
        default: return false;
    }
}

float Mechanics::getGravity(){
    return gravity;
}