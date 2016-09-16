#ifndef PLAYER_H
#define PLAYER_H

#include "Util.hpp"
#include "GL.hpp"
#include "Mechanics.hpp"
#include "Entity.hpp"

class Player:public Mechanics,public Entity {
public:
    Player(float life,int sword,int specialPower,nTPoint spawn,nTPoint size,vector<vector<GLuint> >* animations,bool isHuman);
    Player(const Player& orig);
    virtual ~Player();
    static int lives;
    void applyDamage(float damage);
    static vector<void*>self;
    bool damageState;
    void makeInvencible(float time);
    void atack(int type);
    void draw(nTColor color);
    void spawn(nTPoint spawn,float life);
    static int ranged;
    static int melee;
    int atackDirection;
private:
    int GLlist;
    unsigned int id;
    int sword;
    int specialPower;
    static float imunityTime;
    friend ostream& operator<<(ostream &strm, const Player &player);
};

#endif /* PLAYER_H */
