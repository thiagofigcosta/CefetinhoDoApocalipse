#ifndef BLOCKS_HPP
#define BLOCKS_HPP
#include "Util.hpp"
#include "GL.hpp"
#include "Map.hpp"
class Blocks {
public:
    Blocks(int type,nTPoint pos,nTPoint size);
    Blocks(const Blocks& orig);
    virtual ~Blocks();
    static GLuint getTextureByIndex();
    void draw();
    void move(string dir,float steeps);
    float moveSpeed;
private:
    nTPoint pos;
    nTPoint size;
    int type;
    GLuint tex;
};

#endif /* BLOCKS_HPP */

