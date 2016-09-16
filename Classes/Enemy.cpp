#include "Enemy.hpp"

Enemy::Enemy(int enemyType,float life,nTPoint spawn,nTPoint size,vector<vector<GLuint> > animations,bool isHuman) {
    this->pos=spawn;
    this->size=size;
    this->animations=animations;
    this->vSpeed=0;
    this->hSpeed=0;
    this->currentState=0;
    this->currentIndex=0;
    this->nextState=-1;
    this->life=life;
    this->defaultOrientation=1;
    this->isHuman=isHuman;
    this->type=enemyType;
    this->GLlist=glGenLists(1);
    this->canJump=true;
    this->reducing=false;
    
    Mechanics::enemys.push_back(this);
    Entity::enemys.push_back(this);
    self.push_back(this);
    selfIsPlayer.push_back(false);
    this->id=self.size()-1;
};

Enemy::Enemy(const Enemy& orig) {
}

Enemy::~Enemy() {
    Player* pl;
    Enemy* en;
    for(int i=id+1;i<self.size();i++){
        if(selfIsPlayer[i]){
            pl=(Player*)self[i];
            pl->id--;
        }else{
            en=(Enemy*)self[i];
            en->id--;
        }
    }
    self.erase(self.begin()+this->id);
    selfIsPlayer.erase(selfIsPlayer.begin()+this->id);
    
    for(int i=0;i<Entity::enemys.size();i++){
        if(Entity::enemys[i]==this){
            Entity::enemys.erase(Entity::enemys.begin()+i);
            break;
        }
    }
    for(int i=0;i<Mechanics::enemys.size();i++){
        if(Mechanics::enemys[i]==this){
            Mechanics::enemys.erase(Mechanics::enemys.begin()+i);
            break;
        }
    }
}

float Enemy::imunityTime=0;

void Enemy::stateControl(){
    Entity::stateControl();
    execAnimation();
}

void Enemy::behave(){
    Enemy *en;
    for(int i=0;i<Entity::enemys.size();i++){
        en=(Enemy*)Entity::enemys[i];
        en->draw(GL::getColorByName("black"));
    }
}