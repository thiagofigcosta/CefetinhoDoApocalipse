#include "Bullet.hpp"
#include "AL.hpp"
#include "Scenes.hpp"

Bullet::Bullet(int type,float moveSpeed,nTPoint pos,nTPoint size) {
    this->size=size;
    this->pos=pos;
    this->hSpeed=moveSpeed;
    this->type=type;
    this->self.push_back(this);
    this->spriteIndex=0;
    this->GLlist=glGenLists(1);
    if(type==0){
        tex=GL::getTextureByName("WinBullet");al->playSoundByName("blockShoot");
    }
    if(type==1)
        tex=GL::getTextureByName("SwordBullet0");
    if(type==2)
        tex=GL::getTextureByName("StrongAtk0");
    if(type==3)
        tex=GL::getTextureByName("WeakAtk0");
    //TODO:set texture
};

Bullet::Bullet(const Bullet& orig) {
}

Bullet::~Bullet() {
    for(int i=0;i<self.size();i++){
        if(self[i]==this){
            self.erase(self.begin()+i);
            break;
        }
    }
}

vector<void*> Bullet::self;
float Bullet::baseDamage=1;
float Bullet::baseSpeed=100;
float Bullet::timeToShoot=0.1;

void Bullet::behave(){
    if(GL::isPaused)
        return;
    Bullet *bu; 
    for(int i=0;i<self.size();i++){
        bu=(Bullet*)self[i];
        if(!Scenes::isInTheScreen(Util::getCollisionRectangle(bu->pos,bu->size))){
            if(bu->type==1)
                player->haveBulletSword=false;
            if(bu->type==2||bu->type==3)
                player->haveBulletSpec=false;
            delete bu;
        }
        if(bu->hSpeed!=0){
            bu->move(Util::left,bu->hSpeed/GL::getFPS());
        }  
        if(bu->type==0){//tiro de bloco
            bu->checkCollisionWithEntity(player->pos,player->size,true);
        }else if(bu->type==1){//espada
            if(round(fmod(GL::framesInGame*GL::getMs(),Entity::getSpriteMs()*3))==0){
                if(bu->tex==GL::getTextureByName("SwordBullet0"))
                    bu->tex=GL::getTextureByName("SwordBullet1");
                else
                    bu->tex=GL::getTextureByName("SwordBullet0");
            }
            bu->checkCollisionWithEntity(Util::nTPointSet(0,0,0),Util::nTPointSet(0,0,0),false);
        }else if(bu->type==2){//atk forte
            if(round(fmod(GL::framesInGame*GL::getMs(),Entity::getSpriteMs()))==0){
                bu->spriteIndex++;
                if(bu->spriteIndex==4)
                    bu->spriteIndex=0;
                char buffer[5];
                snprintf(buffer,5,"%d",bu->spriteIndex);
                string str(buffer);
                bu->tex=GL::getTextureByName("StrongAtk"+str);
            }
            bu->checkCollisionWithEntity(Util::nTPointSet(0,0,0),Util::nTPointSet(0,0,0),false);     
        }else if(bu->type==3){//atk fraco
            if(round(fmod(GL::framesInGame*GL::getMs(),Entity::getSpriteMs()))==0){
                bu->spriteIndex++;
                if(bu->spriteIndex==3)
                    bu->spriteIndex=0;
                char buffer[5];
                snprintf(buffer,5,"%d",bu->spriteIndex);
                string str(buffer);
                bu->tex=GL::getTextureByName("WeakAtk"+str);
            }
            bu->checkCollisionWithEntity(Util::nTPointSet(0,0,0),Util::nTPointSet(0,0,0),false);
        }
       bu->draw();
    }
}

void Bullet::move(int dir,float steeps){
    vector <mapCollision> var;
    bool condition=true;
    if(dir==Util::left||dir==Util::right){
      nTPoint tmp;
      tmp.setPoint(pos.x+steeps,pos.y,pos.z);
      var=Map::checkCollision(tmp,size);
      for(int i=0; i<var.size(); i++){
        if(var[i].collision.firstObj>=3)
          condition=false;
      }
      if(condition)
        pos.x+=steeps;
      else{
        if(type==1)
            player->haveBulletSword=false;
        if(type==2||type==3)
            player->haveBulletSpec=false;
        if(type>=0)
            delete this;
        hSpeed*=-1;
      }

    }
}

void Bullet::checkCollisionWithEntity(nTPoint pos,nTPoint size, bool withPlayer){
    objCollision var;
    if(withPlayer){
        var=Mechanics::getCollision(Util::getCollisionRectangle(this->pos,this->size),Util::getCollisionRectangle(pos,size));
        if(var.firstObj){
            player->applyDamage(1);
            delete this;
        }
    }else{
        Enemy *en;
        for(int i=0;i<Entity::enemys.size();i++){
            en=(Enemy*)Entity::enemys[i];
            var=Mechanics::getCollision(Util::getCollisionRectangle(this->pos,this->size),Util::getCollisionRectangle(en->pos,en->size));
            if(var.firstObj){       
                if(type==1)
                    player->haveBulletSword=false;
                if(type==2||type==3)
                    player->haveBulletSpec=false;
                en->applyDamage(player->sword);
                delete this;
            }
        }
    }
}

void Bullet::draw(){
    if(GL::isPaused)
        return;
    glNewList(GLlist,GL_COMPILE_AND_EXECUTE);
    pos.z=1;
    GL::drawTexture(Util::getCollisionRectangle(pos,size),GL::getColorByName("white"),tex,1);
    glEndList();
}