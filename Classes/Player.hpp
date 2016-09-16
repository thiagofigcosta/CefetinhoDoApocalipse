#ifndef PLAYER_H
#define PLAYER_H
#include "Util.hpp"
#include "Entity.hpp"


class Player:public Entity {
public:
    Player(float life,nTPoint spawn,nTPoint size,vector<vector<GLuint> > animations,bool isHuman);
    Player(const Player& orig);
    virtual ~Player();
    static int lives;
    static int checkpoint;
    static int stage;
    static float coeficiente;
    static float globalCoeficiente;
    void stateControl();
    void makeInvencible(float time);
    void atack(int type);
    void spawn(nTPoint spawn,float life);
    void especificDraw();
    static void refreshCoeficiente();
    static void refreshGlobalcoeficiente();
    static int ranged;
    static int melee;
    static int meleeProjectile;
    static int defaultLife;
    static int enemysKilled;
    static int powerUpsActiveted;
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
    static float swordBaseDamage;
    friend ostream& operator<<(ostream &strm, const Player &player);
};

#endif /* PLAYER_H */
