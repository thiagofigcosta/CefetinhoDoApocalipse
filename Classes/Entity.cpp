#include "Entity.hpp"
#include "Player.hpp"
#include "Blocks.hpp"

Entity::Entity() {
};

Entity::Entity(const Entity& orig) {
}

Entity::~Entity() {
}

float Entity::SpritesPerSecond=1;
float Entity::jumpSpeed=-25;
float Entity::walkSpeed=5;
float Entity::runAceleration=10;
float Entity::maxRunSpeed=30;
float Entity::imunityTime=0;
vector<void*>Entity::self;
vector<bool>Entity::selfIsPlayer;
vector<void*> Entity::players;
vector<void*> Entity::enemys;

void Entity::stateControl(){
    if(life<=0){
        currentState=7;
    }else{
        nextState=0;
        if(hSpeed==walkSpeed)
            nextState=1;
        if(hSpeed>walkSpeed)
            nextState=2;
        if(hSpeed!=0)
            nextState=3;
        if(damageState)
            nextState=6;
    }
}

float Entity::getSpriteMs(){
    return 1/SpritesPerSecond;
}

void Entity::execAnimation(){//base nao chama essa funcao
    if(GL::isPaused)
        return;
    if(GL::framesInGame*GL::getMs()>=Entity::getSpriteMs()){
        if(GL::framesInGame>=100000000000)
            GL::framesInGame=0;
        Player* pl;
        Enemy* en;
        if(currentIndex>=animations[currentState].size()-1){
            currentIndex=0;
            switch(currentState){
                case 6: damageState=false; break;
                case 7: 
                    if(selfIsPlayer[id]){
                        //TODO:player morrer
                    }else{
                        en=(Enemy*)self[id];
                        delete en;
                    }
                break;
            }
            if(nextState>=0){
                currentState=nextState;
                nextState=-1;
            }
        }
        currentTex=animations[currentState][currentIndex];
        currentIndex++;
    }
}

vector<vector<GLuint> >  Entity::getAnimationVector(vector<string> animations, vector<int>size){
    vector<vector<GLuint> > anim;
    for(int i=0;i<animations.size();i++){
        anim.push_back(GL::getTexturesByName(animations[i],size[i]));
    }
    return anim;
}
void Entity::applyDamage(float damage){
    if(damageState)
        return;
    life-=damage;
    if(life<0){
        //TODO: fazer player morrer
    }
    makeInvencible(imunityTime);
}

void Entity::draw(nTColor color){
    if(GL::isPaused)
        return;
    stateControl();
    glNewList(GLlist,GL_COMPILE_AND_EXECUTE);
    GL::drawTexture(Util::getCollisionRectangle(pos,size),color,currentTex,orientation);
    glEndList();
}

void Entity::makeInvencible(float time){
    damageState=true;
}

void Entity::jump(){
    if(canJump){//TODO:na agua pode pular infinitamente
        hSpeed+=jumpSpeed;
        canJump=false;
    }    
}
void Entity::walk(int dir){
    if(dir==Util::left){
        hSpeed=-walkSpeed;
        orientation=-1;
    }else if(dir==Util::right){
        hSpeed=walkSpeed;
        orientation=1;
    }
}
void Entity::run(int dir){
    if(ABS(hSpeed)<walkSpeed)
        walk(dir);
    if(ABS(hSpeed)<maxRunSpeed){
        if(dir==Util::left){
            hSpeed-=runAceleration/GL::getFPS();
        }else if(dir==Util::right){
            hSpeed+=runAceleration/GL::getFPS();
        }
    }
}

void Entity::setAnimations(vector<vector<GLuint> > animations){
    this->animations=animations;
}