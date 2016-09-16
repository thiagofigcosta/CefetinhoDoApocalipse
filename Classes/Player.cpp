#include "Player.hpp"
#include "GL.hpp"
#include "Mechanics.hpp"
#include "Enemy.hpp"
#include "../Libs/Globals.h"

Player::Player(float life,int sword,int specialPower,nTPoint spawn,nTPoint size,vector<vector<GLuint> > animations,bool isHuman) {
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
    this->damageState=false;
    this->sword=sword;
    this->specialPower=specialPower;
    this->atackDirection=Util::right;
    this->orientation=Util::right;
    this->GLlist=glGenLists(1);
    this->canJump=true;
    this->isVisible=true;
    this->swordPos=spawn;
    this->atacking=false;
    this->swordSize=Util::nTPointSet(30,8,1);

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

int Player::lives;
int Player::ranged=64651;
int Player::meleeProjectile=16165;
int Player::melee=165165;
float Player::imunityTime=500;
float Player::swordBaseDamage=2;


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
//    if(fmod(GL::framesInGame,GL::getFPS())==0)
//        cout<<*player;
    execAnimation();
}

void Player::makeInvencible(float time){
    damageState=true;
    glutTimerFunc(time,playerChangeDamageState,id);
}

void Player::spawn(nTPoint spawn,float life){
    this->pos=spawn;
    this->vSpeed=0;
    this->hSpeed=0;
    this->currentState=0;
    this->nextState=-1;
    this->life=life;
    this->defaultOrientation=1;
    this->damageState=false;
    this->atackDirection=Util::right;
    this->orientation=Util::right;
    this->isVisible=true;
    this->reducing=false;
    this->swordPos=spawn;
}

void Player::especificDraw(){
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
    canJump=false;  
    atacking=true;
    if(type==Player::melee){
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
                }
            }
    }else if(type==Player::ranged){
            //TODO:ataque especial
            //TODO:ataque é um bullet
    }else if(type==Player::meleeProjectile){
        if(sword>1){
            //TODO:espada voando bullet
        }
        atacking=false;
        
    }
    
}
