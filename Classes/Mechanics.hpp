#ifndef MECHANICS_H
#define MECHANICS_H
#include "Util.hpp"
#include "GL.hpp"
#include "Map.hpp"

class Mechanics {
public:
    Mechanics();
    Mechanics(const Mechanics& orig);
    virtual ~Mechanics();
    virtual void applyGravity();
    virtual void applyForce();
    virtual bool checkNormalForce(nTPoint pos_,nTPoint size_);
    static float getGravity();
    void move(int dir,float steeps);
    static vector<void*> players;
    static vector<void*> enemys;
    float vSpeed;
    float hSpeed;
    nTPoint size;
    nTPoint pos;
private:
    static float gravity;
protected:

};

#endif /* MECHANICS_H */
