#include "Enemy.hpp"
#include "Bullet.hpp"
#include "../Libs/Globals.h"

Enemy::Enemy(int enemyType,float life,nTPoint spawn,nTPoint size,vector<vector<GLuint> > animations,bool isHuman) {
    this->life=0;
    this->pos=spawn;
    this->size=size;
    this->animations=animations;
    this->vSpeed=0;
    if(enemyType<100)
        this->hSpeed=Entity::walkSpeed;
    else 
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
    this->isVisible=true;
    this->damageState=false;
    
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
        if(i<selfIsPlayer.size())
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

float Enemy::imunityTime=2;

void Enemy::stateControl(){
    Entity::stateControl();
    execAnimation();
    if(GL::framesInGame>=timeToVunerability)
        damageState=false;
}

void Enemy::behave(){
    if(GL::isPaused||Tutorials::isPaused)
        return;
    Enemy *en;
    for(int i=0;i<Entity::enemys.size();i++){
        en=(Enemy*)Entity::enemys[i];
        if(en->type<100){
            if(en->hSpeed>0)
                en->orientation=1;
            else
                en->orientation=-1;
        }else{
            if(player->pos.x>=en->pos.x)
                en->orientation=1;
            else
                en->orientation=-1;
            if(round(fmod(GL::getGameMs(),2300)==0)){
                Bullet *bu=new Bullet(0,Bullet::baseSpeed*en->orientation,Util::nTPointSet(en->pos.x,player->pos.y,1),Util::nTPointSet(40,20,1));
            }
        }
        objCollision var=Mechanics::getCollision(Util::getCollisionRectangle(en->pos,en->size),Util::getCollisionRectangle(player->pos,player->size));
        if(var.firstObj)
            player->applyDamage(1);
        if(en->isVisible)
            en->draw(GL::getColorByName("black"));
    }
}

void Enemy::makeInvencible(float time){
    damageState=true;
    timeToVunerability=GL::framesInGame+imunityTime*GL::getFPS();
}