#include "Mechanics.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

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
    }
}

void Mechanics::applyForce(){
    if(GL::isPaused)
        return;
    Player *pl;
    for(int i=0;i<players.size();i++){
        pl=(Player*)players[i];
        if(pl->hSpeed!=0){
            pl->move(Util::left,hSpeed*1/GL::getFPS());
        }
        if(pl->vSpeed<0){
            pl->move(Util::down,vSpeed*1/GL::getFPS());
        }else if(pl->vSpeed>0){
            pl->move(Util::up,vSpeed*1/GL::getFPS());
        }
    }
    Enemy *en;
    for(int i=0;i<enemys.size();i++){
        en=(Enemy*)enemys[i];
        if(en->hSpeed!=0){
            en->move(Util::left,hSpeed*1/GL::getFPS());
        }
        if(en->vSpeed<0){
            en->move(Util::down,vSpeed*1/GL::getFPS());
        }else if(en->vSpeed>0){
            en->move(Util::up,vSpeed*1/GL::getFPS());
        }
    }
}

void Mechanics::move(int dir,float steeps){
    //TODO:se o bloco for liquido ou dano fazer algo
    //TODO:se o bloco for de power up liberar o powerup
    if(dir==Util::left||dir==Util::right){
      nTPoint tmp;
      tmp.setPoint(pos.x+steeps,pos.y,pos.z);
      if(Map::checkCollision(tmp,size)<3)
        pos=tmp;
    }else if(dir==Util::up){
      nTPoint tmp;
      tmp.setPoint(pos.x,pos.y-steeps,pos.z);
      if(Map::checkCollision(tmp,size)!=2)
        pos=tmp;
    }else if(dir==Util::down){
      nTPoint tmp;
      tmp.setPoint(pos.x,pos.y+steeps,pos.z);
      if(Map::checkCollision(tmp,size)!=1)
        pos=tmp;
    }
}

bool Mechanics::checkNormalForce(nTPoint pos_,nTPoint size_){
    switch(Map::checkCollision(pos_,size_)){
        case 1: return true;
        default: return false;
    }
}

float Mechanics::getGravity(){
    return gravity;
}
