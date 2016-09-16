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
    this->swordSize=Util::nTPointSet(20,6,1);

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
    
    if(fmod(GL::framesInGame,GL::getFPS())==0)
        cout<<*player;
    swordPos=pos;
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
    this->swordPos.z=1;
}


void Player::atack(int type){
    canJump=false;  
    nTRectangle swordCollision;
    switch(type){
        default:
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
            GL::drawRectangle(swordCollision,GL::getColorByName("red"));
            cout<<"atack[p0(x:"<<swordCollision.p0.x<<" y:"<<swordCollision.p0.y<<") p1(x:"<<swordCollision.p1.x<<" y:"<<swordCollision.p1.y<<")]\n";
            Enemy *en;
            for(int i=0;i<Entity::enemys.size();i++){
                en=(Enemy*)Entity::enemys[i];
                if(Mechanics::getCollision(swordCollision,Util::getCollisionRectangle(en->pos,en->size)).firstObj)
                    en->applyDamage((type+1)*swordBaseDamage);
            }
            //TODO:ataque normal do player, verificar direcao do ataque
            //desenhar a espada normal e girar com o eixo no player para mover automaitcamente para o local certo
            //usar GL::rotatePoint
            //TODO: espada é um bullet
            break;

        case 1:
            //TODO:ataque especial
            //TODO:ataque é um bullet
        break;
        
        case 2:
            //TODO:espada voando quando solta o botao e espada é forte
            //TODO:ataque é um bullet
        break;
    }
}
