#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "Util.hpp";
#include "Mechanics.hpp"
#include "Entity.hpp"

class Enemy:public Mechanics,public Entity {
public:
    Enemy(int enemyType,float life,nTPoint spawn,nTPoint size,vector<vector<GLuint> >* animations,bool isHuman);
    Enemy(const Enemy& orig);
    virtual ~Enemy();
    void draw(nTColor color);
private:
    int type;
    int GLlist;
};

#endif /* ENEMY_HPP */

