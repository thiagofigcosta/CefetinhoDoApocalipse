#ifndef BULLET_HPP
#define BULLET_HPP
#include "Util.hpp"
#include "Mechanics.hpp"
#include "Entity.hpp"

class Bullet {
public:
    Bullet(int type,float moveSpeed,nTPoint pos,nTPoint size);
    Bullet(const Bullet& orig);
    virtual ~Bullet();
    static vector<void*> self;
    float hSpeed;
    nTPoint size;
    nTPoint pos;
    int type;
    int spriteIndex;
    GLuint tex;
    GLuint GLlist;
    static float baseDamage;
    static void behave();
    void draw();
    void checkCollisionWithEntity(nTPoint pos,nTPoint size);
    void move(int dir,float steeps);
private:

};

#endif /* BULLET_HPP */

