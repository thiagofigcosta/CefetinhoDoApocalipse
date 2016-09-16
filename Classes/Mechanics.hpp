#ifndef MECHANICS_H
#define MECHANICS_H
#include "Util.hpp"
#include "GL.hpp"
#include "Map.hpp"
//#include "Player.hpp" //TODO:(thiago*)descomentar
//#include "Enemy.hpp"
    
class Mechanics {
public:
    Mechanics();
    Mechanics(const Mechanics& orig);
    virtual ~Mechanics();
    virtual void applyGravity();//testar
    virtual void applyForce();
    virtual bool checkNormalForce(nTPoint pos_,nTPoint size_);//testar
    static float getGravity();
    void move(string dir,float steeps);
    static vector<void*> players;
    static vector<void*> enemys;
private:
    static float gravity;
protected://virtual????
    float vSpeed;
    float hSpeed;
    nTPoint size;
    nTPoint pos;
};

#endif /* MECHANICS_H */
