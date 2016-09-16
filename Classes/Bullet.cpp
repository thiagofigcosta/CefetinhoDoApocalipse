#include "Bullet.hpp"

Bullet::Bullet(int type,float moveSpeed,nTPoint pos,nTPoint size) {
    this->size=size;
    this->pos=pos;
    this->hSpeed=moveSpeed;
    this->type=type;
    this->self.push_back(this);
    this->spriteIndex=0;
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

void Bullet::behave(){
    if(GL::isPaused)
        return;
    Bullet *bu; 
    for(int i=0;i<self.size();i++){
        bu=(Bullet*)self[i];
        if(bu->hSpeed!=0){
            bu->move(Util::left,bu->hSpeed/GL::getFPS());
        }
       //bu->checkCollisionWithEntity(player->pos,player->size);//TODO::descomentar, é colissao com player ou inimigos depenedendo do tipo
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
      else
        hSpeed*=-1;

    }
}

void Bullet::checkCollisionWithEntity(nTPoint pos,nTPoint size){
    //TODO:aplicar powerup (passa a posicao do player pra funcao)) e deleta obj
    //TODO:fazer espada se mover aq
}

void Bullet::draw(){
    if(GL::isPaused)
        return;
    glNewList(GLlist,GL_COMPILE_AND_EXECUTE);
    GL::drawTexture(Util::getCollisionRectangle(pos,size),GL::getColorByName("white"),tex,1);
    glEndList();
}