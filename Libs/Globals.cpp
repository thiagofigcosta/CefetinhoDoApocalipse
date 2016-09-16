#include "Globals.h"
vector<nTMap> maps;

Mechanics *world=new Mechanics();
Player *player;

nTColor clearColor;
vector<GLenum> enables;

AL *al;

int languageIdx=0;