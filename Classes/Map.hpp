#ifndef MAP_HPP
#define MAP_HPP
#include "Util.hpp"
#include "Blocks.hpp"

class Map {
public:
    Map();
    Map(const Map& orig);
    virtual ~Map();
    static void changeCurrentMap(nTMap map); 
    static vector<vector<int> > currentMap;
    static int currentBackground;
    static int checkCollision(nTPoint pos,nTPoint size);
    static void draw();
    static void deleteAllBlocks();
    static void setBlockPos();
    static void refresh();
    static void createDynamicGLlist();
    static void createStaticGLlist();
    
private:
    friend class GL;
    static vector<void*> staticBlocks;
    static vector<void*> dynamicBlocks;
    static vector<void*> enemies;
    static int dynamicGLlist;
    static int staticGLlist;
};

#endif /* MAP_HPP */

