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
    this->swordSize=Util::nTPointSet(30,12,1);
    this->canTp=false;
    this->superMan=false;
    this->god=false;

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
    if(GL::getGameMs()>=timeToVunerability){
        damageState=false;
        superMan=false;
    }
    Entity::stateControl();
    if(nextState!=6&&nextState!=7&&currentState!=6&&currentState!=7&&atacking){
        if(atacking==Player::melee){
            if(vSpeed!=0){//air
                if(atackDirection==Util::down)
                    currentState=9;
                else if(atackDirection==Util::up)
                    currentState=11;
                else
                    currentState=10;
            }else{//ground
                if(atackDirection==Util::up)
                    currentState=13;
                else
                    currentState=12;
            }
            nextState=-1;
            currentIndex=0;
        }else{
            if(!haveBulletSpec)currentIndex=0;
            if(vSpeed!=0){//air
                if(atackDirection==Util::down)
                    currentState=14;
                else if(atackDirection==Util::up)
                    currentState=16;
                else
                    currentState=15;
            }else{//ground
                if(atackDirection==Util::up)
                    currentState=18;
                else
                    currentState=17;
            }
            nextState=-1;
        }
    } 
    if(atacking) atack(atacking);
    Blocks *bl;
    vector <mapCollision> var;
    bool condition=false;
    nTPoint point;
    point=pos;
    point.y=pos.y+2;
      var=Map::checkCollision(point,size);
      for(int i=0; i<var.size(); i++){
        if(var[i].blockRef>=Map::staticBlocks.size()&&var[i].blockRef>0){
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
                       if(tp->type==bl->type&&bl!=tp){
                         canTp=false;
                           player->pos=tp->pos;
                           if(tp->type>-200)
                                player->pos.y-=Blocks::defaultBlockSize.y*1.4;
                           else
                               player->pos.y-=15;
                           player->pos.z=0.9;
                           if(Map::currentMap.size()>23)Scenes::lookAt(player->pos);
                         }
                    }
                }
            }
        }
      }
      itsInTheWater=condition;
    execAnimation();
}

void Player::makeInvencible(float time){
    sword=life-1;
    superMan=true;
    //glutTimerFunc(time,playerChangeDamageState,id);
    timeToVunerability=GL::getGameMs()+time;
}

void Player::spawn(nTPoint spawn,float life){
    if(life>3)
        life=3;
    if(life<1)
        life=1;
    this->pos=spawn;
    this->vSpeed=0;
    this->hSpeed=0;
    this->currentState=8;
    this->nextState=0;
    this->life=life;
    this->sword=(int)life-1;
    this->defaultOrientation=1;
    this->damageState=false;
    this->superMan=false;
    this->atackDirection=Util::right;
    this->orientation=1;
    this->isVisible=true;
    this->reducing=false;
    this->swordPos=spawn;
    this->atacking=false;
    this->haveBulletSword=0;
    this->haveBulletSpec=0;
    this->canWalk=1;
    this->god=false;
    this->canTp=false;
    enemysKilled=0;
    powerUpsActiveted=0;
}

void Player::especificDraw(){
    if(god){
        life=5;
        if(lives<3)
            lives=3;
        superMan=true;
    }
    Player::refreshCoeficiente();
    char buffer[5];
    snprintf(buffer,5,"%d",sword);
    string sID(buffer);
    if(atacking){
        swordCollision.p0.z=1;
        swordCollision.p1.z=1;
        if(atackDirection==Util::up||atackDirection==Util::down)
            GL::drawTexture(swordCollision,GL::getColorByName("white"),GL::getTextureByName("Sword"+sID),2);
        else
            GL::drawTexture(swordCollision,GL::getColorByName("white"),GL::getTextureByName("Sword"+sID),1);
    }
}


void Player::atack(int type){
    if(type==Player::ranged){
        float cof;
        if(Player::globalCoeficiente==0)
            cof=Player::coeficiente;
        else
            cof=Player::globalCoeficiente;
        Bullet *bu;
        nTPoint tmp=swordSize;
        tmp.x*=orientation;
        if(!haveBulletSpec&&(cof>=75||Scenes::freeGameMode)){
            if(cof>=85||Scenes::freeGameMode){
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
        swordCollision=Util::getCollisionRectangle(Util::nTPointSet(0,0,0),swordSize);
    }else if(type==Player::melee){//                             
            int angle;
            if(orientation>0)
                swordPos.setPoint(pos.x+20,pos.y,1);
            else
                swordPos.setPoint(pos.x+(swordSize.x-10),pos.y,1);
            if(atackDirection==Util::right){
                angle=0;
            }else if(atackDirection==Util::up){
                angle=3;
                swordPos.setPoint(pos.x,pos.y,1);
            }else if(atackDirection==Util::left){
                angle=2;
            }else if(atackDirection==Util::down){
                if(canJump&&!itsInTheWater){
                    atacking=false;
                    return;
                }
                angle=1;
                swordPos.setPoint(pos.x,pos.y,1);
            }
            canJump=false;
            canWalk=false; 
            swordCollision=Util::getCollisionRectangle(swordPos,swordSize);
            swordCollision.p0=GL::rotatePoint(swordCollision.p0,player->pos,90*angle);
            swordCollision.p1=GL::rotatePoint(swordCollision.p1,player->pos,90*angle); 
            swordCollision.p0.z=1;
            swordCollision.p1.z=1;
            if(atackDirection==Util::up){
                swordCollision.p0.y-=swordSize.y*3;
                swordCollision.p1.y-=swordSize.y*3;
            }else if(atackDirection==Util::down){
                swordCollision.p0.y+=swordSize.y*3;
                swordCollision.p1.y+=swordSize.y*3;
            }
            Enemy *en;
            objCollision col;
            for(int i=0;i<Entity::enemys.size();i++){
                en=(Enemy*)enemys[i];
                col=Mechanics::getCollision(swordCollision,Util::getCollisionRectangle(en->pos,en->size));
                if(col.firstObj){
                    en->applyDamage(swordBaseDamage*(sword+1));
                    if(atackDirection==Util::down)
                        player->vSpeed=-Entity::jumpSpeed/2.3;
                    else if(atackDirection==Util::right)
                        player->move(Util::left,-Entity::walkSpeed*2/GL::getFPS());
                    else if(atackDirection==Util::left)
                        player->move(Util::left,Entity::walkSpeed*2/GL::getFPS());
           
                }
            }
    }
}

void Player::refreshCoeficiente(){
    coeficiente=0;
    if(Map::nOfEnemys)
        coeficiente+=100*Player::enemysKilled/Map::nOfEnemys*3;
    if(Map::totalPowerUps)
        coeficiente+=100*Player::powerUpsActiveted/Map::totalPowerUps*1;
    if(GL::getGameMs())
        coeficiente+=0.1*Map::expetedTime/GL::getGameMs()*2;
    coeficiente/=6;
    
}
void Player::refreshGlobalcoeficiente(){
    refreshCoeficiente();
    globalCoeficiente+=coeficiente;
    globalCoeficiente/=2;
    coeficiente=0;
}
