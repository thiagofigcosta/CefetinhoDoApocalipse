#include "Globals.h"
vector<int**> MapMapas;
vector<int> MapRows;
vector<int> MapColunms;

Player *player=new Player(5,2,2,Util::nTPointSet(50,30,0),Util::nTPointSet(20,60,0),NULL,1);
Mechanics *world=new Mechanics();

nTColor clearColor;
vector<GLenum> enables;

AL *al=new AL(1,1);