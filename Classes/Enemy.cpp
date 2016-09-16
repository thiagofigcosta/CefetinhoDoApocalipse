#include "Enemy.hpp"

Enemy::Enemy(int enemyType,float life,nTPoint spawn,nTPoint size,vector<vector<GLuint> >* animations,bool isHuman) {
    this->pos=spawn;
    this->size=size;
    this->animations=animations;
    this->vSpeed=0;
    this->hSpeed=0;
    this->currentState=0;
    this->nextState=-1;
    this->life=life;
    this->defaultOrientation=1;
    this->isHuman=isHuman;
    this->type=enemyType;
    
    Mechanics::enemys.push_back(this);
};

Enemy::Enemy(const Enemy& orig) {
}

Enemy::~Enemy() {
    for(int i=0;i<Mechanics::enemys.size();i++){
        if(Mechanics::enemys[i]==this){
            Mechanics::enemys.erase(Mechanics::enemys.begin()+i);
            break;
        }
    }
}

