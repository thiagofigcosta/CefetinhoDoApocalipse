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
int Player::melee=-165165;
float Player::imunityTime=500;


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
    
    if(fmod(GL::framesInGame,GL::getFPS())==0)
        cout<<*player;
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
}


void Player::atack(int type){
    switch(type){
        default:
            //TODO:ataque normal do player, verificar direcao do ataque
        break;

        case 1:
            //TODO:ataque especial
        break;
    }
}
