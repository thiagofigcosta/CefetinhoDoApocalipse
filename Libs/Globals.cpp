#include "Globals.h"
vector<nTMap> maps;

Mechanics *world=new Mechanics();
Player *player;

nTColor clearColor;

vector<vector<string> >playerAnim;
vector<vector<int> >playerAnimSize;
vector<vector<string> >enemyAnim;
vector<vector<int> >enemyAnimSize;

AL *al;

int languageIdx=0;