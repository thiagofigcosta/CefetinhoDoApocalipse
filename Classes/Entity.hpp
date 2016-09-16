#ifndef ENTITY_H
#define ENTITY_H
#include "Util.hpp"
#include "GL.hpp"
class Entity {
public:
    Entity();
    Entity(const Entity& orig);
    virtual ~Entity();
    virtual void stateControl();
    virtual void execAnimation();
    static float getSpriteMs();
    static float jumpSpeed;
    static float walkSpeed;
    static float runAceleration;
    static float maxRunSpeed;
    static vector<void*> players;
    static vector<void*> enemys;
    int orientation;
private:
    static float SpritesPerSecond;
protected:
    GLuint currentTex;
    int currentIndex;
    int currentState;
    int nextState;
    float life;
    bool defaultOrientation;
    bool isHuman;
    vector<vector<GLuint> > *animations;
};

#endif /* ENTITY_H */
