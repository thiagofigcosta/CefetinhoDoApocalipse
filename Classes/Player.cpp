#include "Player.hpp"

Player::Player(float life,int sword,int specialPower,nTPoint spawn,nTPoint size,vector<vector<GLuint> >* animations,bool isHuman) {
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
    this->damageState=false;
    this->sword=sword;
    this->specialPower=specialPower;
    this->atackDirection=Util::right;
    this->orientation=Util::right;
    this->GLlist=glGenLists(1);

    Mechanics::players.push_back(this);
    Entity::players.push_back(this);

    self.push_back(this);
    this->id=self.size()-1;
};

Player::Player(const Player& orig) {
}

Player::~Player() {
    self.erase(self.begin()+this->id);

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
float Player::imunityTime=500;
vector<void*>Player::self;
int Player::ranged=64651;
int Player::melee=-165165;

ostream& operator<<(ostream &strm, const Player &player){
    Player *pl=(Player*)&player;
    if(Util::DEBUG)
        return strm <<"Player:["<<"Speed("<<"vSpeed:"<<pl->vSpeed<<" hSpeed:"<<pl->hSpeed<<"),"<<"]\n";
    return strm;
}

void playerChangeDamageState(int id){
    Player *pl;
    pl=(Player*)Player::self[id];
    pl->damageState=false;
}


void Player::makeInvencible(float time){
    damageState=true;
    glutTimerFunc(time,playerChangeDamageState,id);
}

void Player::applyDamage(float damage){
    if(damageState)
        return;
    life-=damage;
    if(life<0){
        //TODO: fazer player morrer
    }
    makeInvencible(Player::imunityTime);
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
void Player::draw(nTColor color){
    glNewList(GLlist,GL_COMPILE_AND_EXECUTE);
    GL::drawTexture(Util::getCollisionRectangle(pos,size),color,currentTex,orientation);
    glEndList();
}