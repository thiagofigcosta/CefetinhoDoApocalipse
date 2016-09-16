#ifndef PLAYER_H
#define PLAYER_H
#include "Util.hpp"
#include "Entity.hpp"


class Player:public Entity {
public:
    Player(float life,int sword,int specialPower,nTPoint spawn,nTPoint size,vector<vector<GLuint> > animations,bool isHuman);
    Player(const Player& orig);
    virtual ~Player();
    static int lives;
    void stateControl();
    void makeInvencible(float time);
    void atack(int type);
    void spawn(nTPoint spawn,float life);
    void especificDraw();
    static int ranged;
    static int melee;
    static int meleeProjectile;
    int atackDirection;
    int atacking;
    bool spacePressed;
    int sword;
    bool canWalk;
    bool haveBulletSword;
    bool haveBulletSpec;
    bool itsInTheWater;
    bool canTp;
    static float imunityTime;
private:
    friend class Map;
    nTPoint swordPos;
    nTPoint swordSize;
    nTRectangle swordCollision;   
    int specialPower;
    static float swordBaseDamage;
    friend ostream& operator<<(ostream &strm, const Player &player);
};

#endif /* PLAYER_H */
