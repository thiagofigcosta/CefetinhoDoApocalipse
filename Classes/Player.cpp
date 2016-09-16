#include "Player.hpp"
#include "GL.hpp"
#include "Mechanics.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "../Libs/Globals.h"
#include "Blocks.hpp"

Player::Player(float life,nTPoint spawn,nTPoint size,vector<vector<GLuint> > animations,bool isHuman) {
    this->pos=spawn;
    this->size=size;
    this->animations=animations;
    this->vSpeed=0;
    this->hSpeed=0;
    this->currentState=0;
    this->currentIndex=0;
    this->nextState=-1;
    if(life>3)
        life=3;
    this->life=life;
    this->defaultOrientation=1;
    this->isHuman=isHuman;
    this->damageState=false;
    this->sword=(int)life-1;
    this->atackDirection=Util::right;
    this->orientation=Util::right;
    this->GLlist=glGenLists(1);
    this->canJump=true;
    this->isVisible=true;
    this->swordPos=spawn;
    this->atacking=false;
    this->haveBulletSword=0;
    this->haveBulletSpec=0;
    this->canWalk=1;
    this->swordSize=Util::nTPointSet(30,8,1);
    this->canTp=false;

    Mechanics::players.push_back(this);
    Entity::players.push_back(this);
    self.push_back(this);
    selfIsPlayer.push_back(true);
    this->id=self.size()-1;
};

Player::Player(const Player& orig) {
}

Player::~Player() {
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

    for(int i=0;i<Mechanics::players.size();i++){
        if(Mechanics::players[i]==this){
            Mechanics::players.erase(Mechanics::players.begin()+i);
            break;
        }
    }
    for(int i=0;i<Entity::players.size();i++){
        if(Entity::players[i]==this){
            Entity::players.erase(Entity::players.begin()+i);
            break;
        }
    }
}

int Player::lives=3;
int Player::ranged=64651;
int Player::meleeProjectile=16165;
int Player::melee=165165;
float Player::imunityTime=500;
float Player::swordBaseDamage=2;
int Player::checkpoint=0;
int Player::stage=0;
int Player::defaultLife=3;
float Player::coeficiente=0;
float Player::globalCoeficiente=0;
int Player::enemysKilled=0;
int Player::powerUpsActiveted=0;


ostream& operator<<(ostream &strm, const Player &player){
    Player *pl=(Player*)&player;
    if(Util::DEBUG)
        return strm <<"Player:["<<"Pos("<<"x:"<<pl->pos.x<<" y:"<<pl->pos.y<<"),"<<"Speed("<<"hSpeed:"<<pl->hSpeed<<" vSpeed:"<<pl->vSpeed<<"),"<<"]\n";
    return strm;
}

void playerChangeDamageState(int id){
    Player *pl;
    try{
        pl=(Player*)Player::self[id];
        pl->damageState=false;
    }catch(const std::exception& e){
        cout<<"pCDS-catch error: "<<e.what()<<endl;
    }
}

void Player::stateControl(){
    Entity::stateControl();
    if(nextState!=6&&nextState!=7){
       //TODO:ataques  
    } 
    Blocks *bl;
    vector <mapCollision> var;
    bool condition=false;
      nTPoint tmp;
      var=Map::checkCollision(pos,size);
      for(int i=0; i<var.size(); i++){
        if(var[i].blockRef>Map::staticBlocks.size()){
            bl=(Blocks*) Map::dynamicBlocks[var[i].blockRef-Map::staticBlocks.size()];
            if(var[i].collision.firstObj){
                if(bl->type>=376&&bl->type<=400)
                      condition=true;
                if(bl->type==377||bl->type==379)
                    life=0;
                if(bl->type==255)
                    applyDamage(1);
                if(bl->type<0&&canTp){
                    Blocks* tp;
                    for(int j=0;j<Map::dynamicBlocks.size();j++){
                       tp=(Blocks*)Map::dynamicBlocks[j];
                       if(tp->type==bl->type&&bl!=tp)
                           player->pos=tp->pos;
                           player->pos.y-=Blocks::defaultBlockSize.y*1.4;
                           player->pos.z=0.9;
                           Scenes::lookAt(player->pos);
                    }
                }
            }
        }
      }
      itsInTheWater=condition;
//    if(fmod(GL::framesInGame,GL::getFPS())==0)
//        cout<<*player;
    execAnimation();
}

void Player::makeInvencible(float time){
    sword=life-1;
    damageState=true;
    glutTimerFunc(time,playerChangeDamageState,id);
}

void Player::spawn(nTPoint spawn,float life){
    if(life>3)
        life=3;
    this->pos=spawn;
    this->vSpeed=0;
    this->hSpeed=0;
    this->currentState=0;
    this->nextState=-1;
    this->life=life;
    this->sword=(int)life-1;
    this->defaultOrientation=1;
    this->damageState=false;
    this->atackDirection=Util::right;
    this->orientation=Util::right;
    this->isVisible=true;
    this->reducing=false;
    this->swordPos=spawn;
    this->atacking=false;
    this->haveBulletSword=0;
    this->haveBulletSpec=0;
    this->canWalk=1;
    this->canTp=false;
    enemysKilled=0;
    powerUpsActiveted=0;
}

void Player::especificDraw(){
    Player::refreshCoeficiente();
    char buffer[5];
    snprintf(buffer,5,"%d",sword);
    string sID(buffer);
    if(atacking){
        atack(atacking);
        if(atackDirection==Util::up||atackDirection==Util::down)
            GL::drawTexture(swordCollision,GL::getColorByName("white"),GL::getTextureByName("Sword"+sID),2);
        else
            GL::drawTexture(swordCollision,GL::getColorByName("white"),GL::getTextureByName("Sword"+sID),1);
    }
}


void Player::atack(int type){ 
    if(type==Player::melee){
            atacking=true;
            canJump=false;
            canWalk=false;
            swordPos.setPoint(pos.x+10*orientation,pos.y,1);
            swordCollision=Util::getCollisionRectangle(swordPos,swordSize);
            int angle;
            if(atackDirection==Util::right)
                angle=0;
            else if(atackDirection==Util::up){
                angle=1;
            }else if(atackDirection==Util::left){
                angle=2;
            }else if(atackDirection==Util::down){
                angle=3;
            }
            swordCollision.p0=GL::rotatePoint(swordCollision.p0,player->pos,90*angle);
            swordCollision.p1=GL::rotatePoint(swordCollision.p1,player->pos,90*angle); 
            swordCollision.p0.z=1;
            swordCollision.p1.z=1;
            Enemy *en;
            for(int i=0;i<Entity::enemys.size();i++){
                en=(Enemy*)Entity::enemys[i];
                if(Mechanics::getCollision(swordCollision,Util::getCollisionRectangle(en->pos,en->size)).firstObj)
                    en->applyDamage((type+1)*swordBaseDamage);
            }
            //colissao
            objCollision col;

            for(int i=0;i<Entity::enemys.size();i++){
                en=(Enemy*)enemys[i];
                col=Mechanics::getCollision(swordCollision,Util::getCollisionRectangle(en->pos,en->size));
                if(col.firstObj){
                    en->applyDamage(swordBaseDamage*(sword+1));//TODO:fazer player subir
                    if(en->life<=0)
                        enemysKilled++;
                }
            }
    }else if(type==Player::ranged){
        float cof;
        if(Player::globalCoeficiente==0)
            cof=Player::coeficiente;
        else
            cof=Player::globalCoeficiente;
        Bullet *bu;
        nTPoint tmp=swordSize;
        tmp.x*=orientation;
        if(!haveBulletSpec&&cof>=75){
            if(cof>=85){
                bu=new Bullet(2,orientation*Bullet::baseSpeed,pos,tmp);
            }else{
                bu=new Bullet(3,orientation*Bullet::baseSpeed,pos,tmp);
            }
            haveBulletSpec=true;
            atacking=false;
        }
    }else if(type==Player::meleeProjectile){
        if(sword>1&&!haveBulletSword){
            Bullet *bu;
            nTPoint tmp=swordSize;
            tmp.x*=orientation;
            bu=new Bullet(1,orientation*Bullet::baseSpeed,pos,tmp);
            haveBulletSword=true;
        }
        canWalk=true;
        atacking=false;       
    }
}

void Player::refreshCoeficiente(){
    coeficiente=0;
    coeficiente+=100*Player::enemysKilled/Map::nOfEnemys*3;
    coeficiente+=100*Player::powerUpsActiveted/Map::totalPowerUps*1;
    coeficiente+=0.1*Map::expetedTime/GL::getGameMs()*2;
    coeficiente/=6;
    
}
void Player::refreshGlobalcoeficiente(){
    refreshCoeficiente();
    globalCoeficiente+=coeficiente;
    globalCoeficiente/=2;
    coeficiente=0;
}
