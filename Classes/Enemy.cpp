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
    this->GLlist=glGenLists(1);
    
    Mechanics::enemys.push_back(this);
    Entity::enemys.push_back(this);
};

Enemy::Enemy(const Enemy& orig) {
}

Enemy::~Enemy() {
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

void Enemy::draw(nTColor color){
    glNewList(GLlist,GL_COMPILE_AND_EXECUTE);
    GL::drawTexture(Util::getCollisionRectangle(pos,size),color,currentTex,orientation);
    glEndList();
}