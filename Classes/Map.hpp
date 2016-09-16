#ifndef MAP_HPP
#define MAP_HPP
#include "Util.hpp"
#include "GL.hpp"

class Map {
public:
    Map();
    Map(const Map& orig);
    virtual ~Map();
    static void changeCurrentMap(nTMap map); 
    static vector<vector<int> > currentMap;
    static vector<mapCollision> checkCollision(nTPoint pos,nTPoint size);
    static void draw();
    static void deleteAllBlocks();
    static void setBlockPos();
    static void refresh();
    static void createDynamicGLlist();
    static void createStaticGLlist();
    static int getBlockReference(nTPoint pos);
    static nTPoint size;
private:
    friend class GL;
    static vector<void*> staticBlocks;
    static vector<void*> dynamicBlocks;
    static vector<void*> enemies;
    static int dynamicGLlist;
    static int staticGLlist;
    static GLuint background;
    static vector<vector<nTReferences> > blockReference;
};

#endif /* MAP_HPP */

