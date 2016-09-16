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
    static int checkCollisionWithMap(nTPoint pos,nTPoint size);
    static void drawMap();
    static void deleteAllBlocks();
    static void updateBlockPos();
private:
    static vector<void*> staticBlocks;
    static vector<void*> dynamicBlocks;
};

#endif /* MAP_HPP */

