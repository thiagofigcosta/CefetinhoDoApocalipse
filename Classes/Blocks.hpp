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
    GLuint getTextureByIndex();
    void draw();
    void move(int dir,float steeps);
    float moveSpeed;
    static nTPoint defaultBlockSize;
    static bool checkIfBlocksIsDynamic(int id);
    static bool checkIfBlocksIsMassive(int id);
private:
    friend class Map;
    nTPoint size;
    nTPoint pos;
    int type;
    GLuint tex;
};

#endif /* BLOCKS_HPP */

