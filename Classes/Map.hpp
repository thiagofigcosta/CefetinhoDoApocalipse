#ifndef MAP_HPP
#define MAP_HPP
#include "Util.hpp"
#include "Blocks.hpp"
class Map {
public:
    Map();
    Map(const Map& orig);
    virtual ~Map();
    static void changeCurrentMap(int **map,int rows,int columns); 
    static vector<vector<int> > currentMap;
    static int checkCollision(nTPoint pos,nTPoint size);
    static void draw();
    static void deleteAllBlocks();
    static void setBlockPos();
    static void createDynamicGLlist();
    static void createStaticGLlist();
    
private:
    static vector<void*> staticBlocks;
    static vector<void*> dynamicBlocks;
    static int dynamicGLlist;
    static int staticGLlist;
};

#endif /* MAP_HPP */

