#include "Entity.hpp"

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
vector<void*> Entity::players;
vector<void*> Entity::enemys;

void Entity::stateControl(){
    //TODO:controlar o estado da entidade
    //talvez sobrescrever essa funcao em uma classe filha
}

float Entity::getSpriteMs(){
    return 1/SpritesPerSecond;
}

void Entity::execAnimation(){
    if(GL::isPaused)
        return;
    //TODO:atualizar sprite glutTimerFunc(getSpriteMs); para chamar a funcao de tempo em tempo
    //provavelmente o gluttimerfunc tera q ficar no main e chamar uma funcao q n pertenca a uma classe
}